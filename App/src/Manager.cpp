#include "stdafx.h"
#include "Manager.h"
#include "Common.h"
#include "GameScene.h"

/*	Start GameManager		********************************************************************************************************/

//const std::array<String, static_cast<EnumValue>(SortingBoxIdx::Count)> GameManager::SortingBoxesMarks = { U"●", U"▲", U"■" };

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
	m_isClassified = false;
	m_boxIdx = SortingBoxIdx::Count;
	m_stageLevel = StageLevel::Count;
}

void GameManager::reset()
{
	m_sortedShapePtr = nullptr;

	m_distance = Vec2().Zero();
	m_isClassified = false;
	m_boxIdx = SortingBoxIdx::Count;
	m_currentSortRule = SortRule::Count;
	m_stageLevel = StageLevel::Count;
}

void GameManager::retry()
{
	m_sortedShapePtr = nullptr;

	m_distance = Vec2().Zero();
	m_isPaused = false;
	m_isClassified = false;
	m_boxIdx = SortingBoxIdx::Count;
}

void GameManager::update()
{
	if (m_sortedShapePtr == nullptr) return;

	if (m_sortedShapePtr->isMouseOver() && not m_isPaused)
	{
		// カーソルを手の形にする.
		Cursor::RequestStyle(CursorStyle::Hand);

		if (MouseL.down())
		{
			// カーソルで掴んだ場所を記録する.
			m_distance = m_sortedShapePtr->center() - Cursor::Pos();
		}

		if (MouseL.pressed())
		{
			Vec2 pos = Cursor::Pos() + m_distance;
			m_sortedShapePtr->move(pos.clamped(SortedArea));
		}
	}

	// 分類箱の下側の図形との当たり判定で分類する.
	const EnumValue layerIdx = static_cast<EnumValue>(SortingBoxLayerIdx::Lowerside);

	// 分類処理.
	for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
	{
		if (m_sortedShapePtr == nullptr) break;

		if (m_sortedShapePtr->isIntersects(SortingBoxes[layerIdx][i]) && MouseL.up())
		{
			m_isClassified = true;
			m_boxIdx = static_cast<SortingBoxIdx>(i);
		}
	}
}

void GameManager::generateFigure()
{
	m_sortedShapePtr = m_figureGen.generate(m_stageLevel, m_currentSortRule, m_isChangedColor);
}

//void GameManager::draw() const
//{
//	//// 分別はこ下側.
//	//for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
//	//{
//	//	box_under(SortingBoxes[static_cast<EnumValue>(SortingBoxLayerIdx::Lowerside)][i], (m_isChangedColor) ? ScoreManager::SortingAnswers[i].colors.colorChanged : ScoreManager::SortingAnswers[i].colors.colorDefault);
//	//}
//
//	//// 動かす図形.
//	//if (m_sortedShapePtr != nullptr) m_sortedShapePtr->draw();
//
//	//// 分別はこ上側.
//	//for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
//	//{
//	//	const RectF box = SortingBoxes[static_cast<EnumValue>(SortingBoxLayerIdx::Upperside)][i];
//	//	box_over(
//	//		box,
//	//		(m_isChangedColor) ? ScoreManager::SortingAnswers[i].colors.colorChanged : ScoreManager::SortingAnswers[i].colors.colorDefault,
//	//		FontAsset(FontText),
//	//		SortingBoxesMarks[i]);
//
//	//	const String text = (m_isChangedColor) ? ScoreManager::SortingAnswers[i].texts.textChanged : ScoreManager::SortingAnswers[i].texts.textDefault;
//	//	FontAsset(FontText)(U"\n{}"_fmt(text)).drawAt(box.x + box.w / 2, box.y + box.h * 3 / 5, kuro);
//	//}
//}

void GameManager::setSortRule(const EnumValue nextStageIdx)
{
	if (static_cast<EnumValue>(m_stageLevel) != nextStageIdx) m_sortRuleGen.init(nextStageIdx + 1);

	m_stageLevel = static_cast<StageLevel>(nextStageIdx);

	GenValue idx = m_sortRuleGen.generate();
	m_currentSortRule = static_cast<SortRule>(idx);
}

/*	End GameManager			********************************************************************************************************/

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
	m_isCorrectSorted = false;
	m_highScores = std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)>{ 0, 0, 0 };
}

void ScoreManager::reset()
{
	m_score = 0;
	m_classifyNum = 0;
	m_correctNum = 0;
	m_missNum = 0;
	m_comboNum = 0;
	m_newRecord = false;
	m_isCorrectSorted = false;
	m_highScores = std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)>{ 0, 0, 0 };
}

void ScoreManager::retry()
{
	m_score = 0;
	m_classifyNum = 0;
	m_correctNum = 0;
	m_missNum = 0;
	m_comboNum = 0;
	m_newRecord = false;
	m_isCorrectSorted = false;
}

void ScoreManager::classify(const GameManager& gm)
{
	++m_classifyNum;	// 仕分けた回数の更新.

	const auto rule = gm.currentSortRule();
	const auto shapePtr = gm.sortedShapePtr();
	const auto idx = static_cast<EnumValue>(gm.boxIdx());
	const auto level = gm.stageLevel();

	if (rule == SortRule::ShapeRule)
	{
		if (shapePtr->type() == SortingAnswers[idx].type)
		{
			correct(level);
		}
		else
		{
			miss(level);
		}
	}
	else if (rule == SortRule::ColorRule)
	{
		if (shapePtr->color() == SortingAnswers[idx].colors.colorDefault || shapePtr->color() == SortingAnswers[idx].colors.colorChanged)
		{
			correct(level);
		}
		else
		{
			miss(level);
		}
	}
	else if (rule == SortRule::TextRule)
	{
		if (shapePtr->text() == SortingAnswers[idx].texts.textDefault || shapePtr->text() == SortingAnswers[idx].texts.textChanged)
		{
			correct(level);
		}
		else
		{
			miss(level);
		}
	}
	else
	{
		Print << U"classify: 未定義の仕分けルールで分類を試みました.";
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

void ScoreManager::correct(const StageLevel level)
{
	// 加点する.
	sumScore(Scores[static_cast<EnumValue>(level)][static_cast<EnumValue>(ScoreChange::Increase)]);

	++m_correctNum;

	++m_comboNum;

	m_isCorrectSorted = true;
}

void ScoreManager::miss(const StageLevel level)
{
	// 減点する.
	sumScore(Scores[static_cast<EnumValue>(level)][static_cast<EnumValue>(ScoreChange::Decrease)]);

	++m_missNum;

	m_comboNum = 0;

	m_isCorrectSorted = false;
}

/*	End ScoreManager		********************************************************************************************************/

/*	Start UIManager			********************************************************************************************************/

const std::array<String, static_cast<EnumValue>(SortingBoxIdx::Count)> UIManager::SortingBoxesMarks = { U"●", U"▲", U"■" };


void UIManager::init()
{
	m_drawTable[UILayer::SortRule] = [this]()
		{
			// ルール内容の表示.
			switch (m_gameManager.currentSortRule())
			{
			case SortRule::ShapeRule:

				FontAsset(U"FontText")(U"かたちで仕分け!!").drawAt(siwakesize, siwakerule, MainTextColor);

				break;

			case SortRule::ColorRule:

				FontAsset(U"FontText")(U"いろで仕分け!!").drawAt(siwakesize, siwakerule, MainTextColor);

				break;

			case SortRule::TextRule:

				//if (m_canDisplayRule) FontAsset(U"FontText")(U"もじで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
				FontAsset(U"FontText")(U"もじで仕分け!!").drawAt(siwakesize, siwakerule, MainTextColor);

				break;

			default:
				break;
			}
		};

	m_drawTable[UILayer::SortBoxesUpperside] = [this]()
		{
			for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
			{
				const auto idx = static_cast<SortingBoxIdx>(i);
				const RectF box = m_gameManager.SortingBoxes[static_cast<EnumValue>(SortingBoxLayerIdx::Upperside)][i];

				box.drawFrame(haba, MainTextColor).draw(color(idx));

				FontAsset(U"FontText")(U"{}"_fmt(SortingBoxesMarks[i])).drawAt(box.center(), MainTextColor);

				FontAsset(U"FontText")(U"\n{}"_fmt(text(idx))).drawAt(box.x + box.w / 2, box.y + box.h * 3 / 5, MainTextColor);
			}
		};

	m_drawTable[UILayer::SortBoxesLowerside] = [this]()
		{
			for (size_t i = 0; i < static_cast<EnumValue>(SortingBoxIdx::Count); ++i)
			{
				m_gameManager.SortingBoxes[static_cast<EnumValue>(SortingBoxLayerIdx::Lowerside)][i]
					.drawFrame(haba, MainTextColor)
					.draw(color(static_cast<SortingBoxIdx>(i)) * 0.8);
			}
		};

	m_drawTable[UILayer::SortedShape] = [this]()
		{
			if (m_gameManager.sortedShapePtr() != nullptr)
			{
				m_gameManager.sortedShapePtr()->draw();
			}
		};

	m_drawEasingTable[UILayer::ResultCurtain] = [this](const double t)
		{
			m_boxBounce_aud(t, makuSize, makuColor);
		};

	m_drawEasingTable[UILayer::ResultTexts] = [this](const double t)
		{
			// 結果.
			m_textBounce_aud(t, resultText, FontAsset(U"FontButton"), U"★RESULT★", 80);

			// 獲得スコア.
			m_textBounce_aud(t, yourscoreText, FontAsset(U"FontButton"), U"Your Score:{}"_fmt(m_scoreManager.score()), 36);

			// ハイスコア.
			m_textBounce_aud(t, highscoreText, FontAsset(U"FontButton"), U"High Score:{}"_fmt(m_scoreManager.highScores()[static_cast<EnumValue>(m_gameManager.stageLevel())]), 20);

			// 記録を更新したか.
			if (m_scoreManager.newRecord())
			{
				m_textBounce_aud(t, newrecordText, FontAsset(U"FontButton"), U"New Record!!", 20);
			}

			// 最大コンボ数.
			//m_textOutExpo_aap(t_rt01, sortedTextAppearPoint, sortedText, kuro, text, U"combo:{}"_fmt(comboNum), 30);
		};
}

void UIManager::reset()
{
}

void UIManager::retry()
{
}

void UIManager::draw(const UILayer layer) const
{
	const auto& it = m_drawTable.find(layer);
	if (it != m_drawTable.end()) it->second();
}

void UIManager::draw(const UILayer layer, const double t) const
{
	const auto& it = m_drawEasingTable.find(layer);
	if (it != m_drawEasingTable.end()) it->second(t);
}

void UIManager::drawPlayingScene() const
{
	// 仕分けルール.
	draw(UILayer::SortRule);

	// 分類箱の下側.
	draw(UILayer::SortBoxesLowerside);

	// 仕分け中の図形.
	draw(UILayer::SortedShape);

	// 分類箱の上側.
	draw(UILayer::SortBoxesUpperside);
}

const ColorF& UIManager::color(const SortingBoxIdx boxIdx) const
{
	if (boxIdx == SortingBoxIdx::Count) return Palette::White;

	const auto idx = static_cast<EnumValue>(boxIdx);

	if (m_gameManager.isChangedColor())
	{
		return ScoreManager::SortingAnswers[idx].colors.colorChanged;
	}

	return ScoreManager::SortingAnswers[idx].colors.colorDefault;
}

const String& UIManager::text(const SortingBoxIdx boxIdx) const
{
	if (boxIdx == SortingBoxIdx::Count) return U"text";

	const auto idx = static_cast<EnumValue>(boxIdx);

	if (m_gameManager.isChangedColor())
	{
		return ScoreManager::SortingAnswers[idx].texts.textChanged;
	}

	return ScoreManager::SortingAnswers[idx].texts.textDefault;
}

// ゲーム結果画面の幕が下りるやつ.
void UIManager::m_boxBounce_aud(const double t, const RectF& rect, const ColorF& colorf) const
{
	RectF{ rect.pos, rect.w, rect.h * easeOutBounce(t) }.draw(colorf);
}

void UIManager::m_textBounce_aud(const double t, const Vec2& vec2, const Font& font, const String& text, const uint8& size) const
{
	font(text).drawAt(size, vec2.x, vec2.y * easeOutBounce(t), kuro);
}

/*	End UIManager			********************************************************************************************************/
