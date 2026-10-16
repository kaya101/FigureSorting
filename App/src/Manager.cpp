#include "stdafx.h"
#include "Manager.h"
#include "Common.h"

/*	Start ScoreManager		********************************************************************************************************/

const std::array<ScoreManager::AnswerData, static_cast<EnumValue>(SortingBoxIdx::Count)> ScoreManager::SortingAnswers = {
	// 左 に仕分けると正解になるデータ群.
	ScoreManager::AnswerData(SortingShapeType::Cricle, ScoreManager::AnswerData::Colors{ aka, red }, ScoreManager::AnswerData::Texts{ U"あか", U"まる" }),
	// 真ん中 に仕分けると正解になるデータ群.
	ScoreManager::AnswerData(SortingShapeType::Triangle, ScoreManager::AnswerData::Colors{ midori, yelow }, ScoreManager::AnswerData::Texts{ U"みどり", U"さんかく" }),
	// 右 に仕分けると正解になるデータ群.
	ScoreManager::AnswerData(SortingShapeType::Square, ScoreManager::AnswerData::Colors{ ao, blue }, ScoreManager::AnswerData::Texts{ U"あお", U"しかく" })
};

void ScoreManager::init()
{
	m_score = 0;
	m_classifyNum = 0;
	m_correctNum = 0;
	m_missNum = 0;
	m_comboNum = 0;
	m_newRecord = false;
	m_highScores = std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)>{ 0, 0, 0 };
}

void ScoreManager::classify(const EnumValue boxIdx)
{
	++m_classifyNum;	// 仕分けた回数の更新.

	switch (m_gameManager.currentSortRule())
	{
	case SortRule::ShapeRule:

		if (m_gameManager.sortedShapePtr()->type() == SortingAnswers[boxIdx].type)
		{
			correct(static_cast<EnumValue>(m_gameManager.stageLevel()));
		}
		else
		{
			miss(static_cast<EnumValue>(m_gameManager.stageLevel()));
		}

		break;

	case SortRule::ColorRule:

		if (m_gameManager.sortedShapePtr()->color() == SortingAnswers[boxIdx].colors.colorDefault
			|| (m_gameManager.isChangedColor() && m_gameManager.sortedShapePtr()->color() == SortingAnswers[boxIdx].colors.colorChanged))
		{
			correct(static_cast<EnumValue>(m_gameManager.stageLevel()));
		}
		else
		{
			miss(static_cast<EnumValue>(m_gameManager.stageLevel()));
		}
		break;

	case SortRule::TextRule:

		if (m_gameManager.sortedShapePtr()->text() == SortingAnswers[boxIdx].texts.textDefault
			|| (m_gameManager.isChangedColor() && m_gameManager.sortedShapePtr()->text() == SortingAnswers[boxIdx].texts.textChanged))
		{
			correct(static_cast<EnumValue>(m_gameManager.stageLevel()));
		}
		else
		{
			miss(static_cast<EnumValue>(m_gameManager.stageLevel()));
		}
		break;
	default:
		break;
	}
}

void ScoreManager::updateHighScores(const StageLevel level)
{
	const EnumValue idx = static_cast<EnumValue>(level);
	if (m_score > m_highScores[idx])
	{
		m_highScores[idx] = m_score;

		m_newRecord = true;
	}
}

void ScoreManager::draw() const {}

void ScoreManager::correct(const size_t stageIdx)
{
	// 加点する.
	sumScore(Scores[stageIdx][static_cast<EnumValue>(ScoreChange::Increase)]);

	// 正解の回数の記録.
	++m_correctNum;

	// 連続正解の回数を記録.
	++m_comboNum;

	// 正解エフェクトを出す.
	m_gameManager.setTF(TrueOrFalse::TrueSort);
}

void ScoreManager::miss(const size_t stageIdx)
{
	// 減点する.
	sumScore(Scores[stageIdx][static_cast<EnumValue>(ScoreChange::Decrease)]);

	// ミスした回数の記録.
	++m_missNum;

	// 連続正解の回数を 0 に戻す.
	m_comboNum = 0;

	// 間違えたエフェクトを出すへ.
	m_gameManager.setTF(TrueOrFalse::FalseSort);
}

/*	End ScoreManager		********************************************************************************************************/

/*	Start GameManager		********************************************************************************************************/

const std::array<String, static_cast<EnumValue>(SortingBoxIdx::Count)> GameManager::SortingBoxesMarks = { U"●", U"▲", U"■" };

void GameManager::init()
{
	m_sortedShapePtr = nullptr;

	m_sortRuleGen.init(FigureGenerator::N);

	m_figureGen.init();

	m_distance = Vec2().Zero();
	m_currentSortRule = SortRule::Count;
	m_isChangedColor = false;
	m_isSkippedExplain = false;
	m_canDisplayRule = false;
	m_isPaused = false;
	m_stageLevel = StageLevel::Count;
	m_tof = TrueOrFalse::WaitSort;
	m_currentFigureSwitch = FigureSwitch::MakeFigure;
}

void GameManager::update()
{
	// 分類箱の下側の図形との当たり判定で分類する.
	const EnumValue layerIdx = static_cast<EnumValue>(SortingBoxLayerIdx::Lowerside);

	// 分類処理.
	for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
	{
		if (m_sortedShapePtr == nullptr) break;

		if (m_sortedShapePtr->isIntersects(SortingBoxes[layerIdx][i]))
		{
			m_scoreManager.classify(i);

			// 新たに図形を作る.
			m_currentFigureSwitch = FigureSwitch::MakeFigure;

			// 正誤判定の動きの再始動.
			m_truefalse.restart();
		}
	}

	// 動かす図形.
	switch (m_currentFigureSwitch)
	{
	case FigureSwitch::Break: // 待機画面.
		break;

	case FigureSwitch::MakeFigure: // 図形生成.
	{
		m_sortedShapePtr = generateFigure();

		m_currentFigureSwitch = FigureSwitch::Release;

		break;
	}

	case FigureSwitch::Release: // 図形をつかんでないとき.

		if (m_sortedShapePtr->isMouseOver() && not m_isPaused)
		{
			// 手にする.
			Cursor::RequestStyle(CursorStyle::Hand);

			if (MouseL.pressed())
			{
				// カーソルと図形の中心座標の差をとる.
				/*m_distance_x = figure.center.x - Cursor::Pos().x;
				m_distance_y = figure.center.y - Cursor::Pos().y;*/
				m_distance = m_sortedShapePtr->center() - Cursor::Pos();

				m_currentFigureSwitch = FigureSwitch::Catch;
			}
		}

		break;

	case FigureSwitch::Catch: // 図形をつかんで運ぶとき.

		Cursor::RequestStyle(CursorStyle::Hand);

		// 図形を離したとき.
		if (MouseL.up())
		{
			//// 図形の中心座標を離した座標に更新.
			//figure.center.x = check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure);
			//figure.center.y = check_wally(wally, Cursor::Pos().y + m_distance_y, figure);
			//circle.center = figure.center;
			//triangle = { figure.center, culc_Length(triangle) };
			//rect.x = culc_lx(figure);
			//rect.y = culc_ly(figure);
			// 図形の中心座標を離した座標に更新.
			Vec2 pos = Cursor::Pos() + m_distance - (m_sortedShapePtr->size() / 2);
			//m_sortedShapePtr->move(checkWall(SortedArea, Cursor::Pos() + m_distance, *m_sortedShapePtr));
			m_sortedShapePtr->move(pos.clamped(SortedArea));

			m_currentFigureSwitch = FigureSwitch::Release;

			break;
		}
		break;
	default:
		break;
	}

	// 正誤判定.
	// 時間という概念？の取得.
	int32 t_tf = (m_truefalse.ms() / 30);
	switch (m_tof)
	{
	case TrueOrFalse::WaitSort: // 仕分け待ち.
		break;

	case TrueOrFalse::TrueSort: // 正解した時.

		// 正解したエフェクト.
		effect_TrueOrFalse(t_tf, m_scoreManager.comboNum(), kuro, FontAsset(FontText), 30);

		// 時間経過で消す.
		if (t_tf > 20)
		{
			m_truefalse.reset();
			m_tof = TrueOrFalse::WaitSort;
		}

		break;

	case TrueOrFalse::FalseSort: // 間違えたとき.

		// 間違えた時のエフェクト.
		effect_TrueOrFalse(t_tf, m_scoreManager.comboNum(), kuro, FontAsset(FontText), 30);

		if (t_tf > 20)
		{
			m_truefalse.reset();
			m_tof = TrueOrFalse::WaitSort;
		}

		break;

	default:
		break;
	}
}

void GameManager::draw() const
{
	// 分別はこ下側.
	for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
	{
		box_under(SortingBoxes[static_cast<EnumValue>(SortingBoxLayerIdx::Lowerside)][i], (m_isChangedColor) ? m_scoreManager.SortingAnswers[i].colors.colorChanged : m_scoreManager.SortingAnswers[i].colors.colorDefault);
	}

	// 動かす図形.
	if (m_sortedShapePtr != nullptr) m_sortedShapePtr->draw();

	// 分別はこ上側.
	for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
	{
		const RectF box = SortingBoxes[static_cast<EnumValue>(SortingBoxLayerIdx::Upperside)][i];
		box_over(
			box,
			(m_isChangedColor) ? m_scoreManager.SortingAnswers[i].colors.colorChanged : m_scoreManager.SortingAnswers[i].colors.colorDefault,
			FontAsset(FontText),
			SortingBoxesMarks[i]);

		const String text = (m_isChangedColor) ? m_scoreManager.SortingAnswers[i].texts.textChanged : m_scoreManager.SortingAnswers[i].texts.textDefault;
		FontAsset(FontText)(U"\n{}"_fmt(text)).drawAt(box.x + box.w / 2, box.y + box.h * 3 / 5, kuro);
	}


	// ルール内容の表示.
	switch (m_currentSortRule)
	{
	case SortRule::ShapeRule:

		if (m_canDisplayRule) FontAsset(FontText)(U"かたちで仕分け!!").drawAt(siwakesize, siwakerule, kuro);

		break;

	case SortRule::ColorRule:

		if (m_canDisplayRule) FontAsset(FontText)(U"いろで仕分け!!").drawAt(siwakesize, siwakerule, kuro);

		break;

	case SortRule::TextRule:

		if (m_canDisplayRule) FontAsset(FontText)(U"もじで仕分け!!").drawAt(siwakesize, siwakerule, kuro);

		break;

	default:
		break;
	}
}

void GameManager::setSortRule(const EnumValue nextStageIdx)
{
	if (static_cast<EnumValue>(m_stageLevel) != nextStageIdx) m_sortRuleGen.init(nextStageIdx + 1);

	m_stageLevel = static_cast<StageLevel>(nextStageIdx);

	GenValue idx = m_sortRuleGen.generate();
	m_currentSortRule = static_cast<SortRule>(idx);
}

std::unique_ptr<SortedShapeBase> GameManager::generateFigure()
{
	return m_figureGen.generate(m_stageLevel, m_currentSortRule, m_isChangedColor);
}

void GameManager::effect_TrueOrFalse(double t, const uint8& comboNum, const ColorF& colorf, const Font& font, const uint8& textsize)
{
	const String combo3 = U"Perfect!!!";
	const String combo2 = U"Great!!";
	const String combo1 = U"Good!";
	const String combo0 = U"Miss";
	constexpr uint16 effect_X = 400;
	constexpr uint16 effect_Y = 570;
	if (comboNum >= 3) {
		font(combo3.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else if (comboNum == 2) {
		font(combo2.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else if (comboNum == 0) {
		font(combo0.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else {
		font(combo1.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
}

/*	End GameManager			********************************************************************************************************/
