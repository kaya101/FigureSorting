#include "stdafx.h"
#include "GameScene.h"

/*	Start Title Scene	********************************************************************************************************/

Title::Title(const InitData& init)
	: IScene{ init }
{
	FontAsset(FontTitle).preload(m_TitleName);

	Scene::SetBackground(bg_shiro);

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(hajimeru.center(), hajimeru.size, botan * 1.4, U"はじめる", FontButton,
			[&]()
			{
				getData().setCurrentScene(SceneSwitch::Stage);
				changeScene(SceneSwitch::Stage, 0.0);
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(yameru.center(), yameru.size, botan * 1.4, U"やめる", FontButton,
			[&]()
			{
				System::Exit();
			}
		)
	));
}

void Title::update()
{
	const double dt = Scene::DeltaTime();

	for (auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->update(dt);
	}
}

void Title::draw() const
{
	FontAsset(FontTitle)(m_TitleName).drawAt(400, 100, ColorF{ 0.2 });

	for (const auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->draw();
	}
}

void Title::drawFadeIn(double t) const
{
}

void Title::drawFadeOut(double t) const
{
}

/*	End Title Scene		********************************************************************************************************/

/*	Start Stage Scene	********************************************************************************************************/

Stage::Stage(const InitData& init)
	: IScene{ init }
{
	Scene::SetBackground(bg_shiro);

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(stage01botan.center(), stage01botan.size, botan * 1.4, U"これ!!", FontButton,
			[&]()
			{
				// ここのステージで使える素材の受け取り.
				if (getData().colorChange())
				{
					getData().setFcolor(colorchangecolor_Lv01);
				}
				else
				{
					getData().setFcolor(color_Lv01);
				}
				getData().setFtext(text_Lv01);
				getData().setStageNum(STAGE01);

				// 形でわける.
				getData().setScoreSwitch(ScoreSwitch::ShapeRule);
				getData().setCurrentScene(SceneSwitch::Letsplay);
				changeScene(SceneSwitch::Letsplay, 0.0);
			}
		)
	));
	
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(stage02botan.center(), stage02botan.size, botan * 1.4, U"これ!!", FontButton,
			[&]()
			{
				// ここのステージで使える素材の受け取り.
				if (getData().colorChange())
				{
					getData().setFcolor(colorchangecolor_Lv02);
				}
				else
				{
					getData().setFcolor(color_Lv02);
				}
				getData().setFtext(text_Lv02);
				getData().setStageNum(STAGE02);

				// ルール決め.
				if (randInt() % 2)
				{
					// 色でわける.
					getData().setScoreSwitch(ScoreSwitch::ColorRule);
					getData().setCurrentScene(SceneSwitch::Letsplay);
					changeScene(SceneSwitch::Letsplay, 0.0);
				}
				else
				{
					// 形でわける.
					getData().setScoreSwitch(ScoreSwitch::ShapeRule);
					getData().setCurrentScene(SceneSwitch::Letsplay);
					changeScene(SceneSwitch::Letsplay, 0.0);
				}
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(stageMAXbotan.center(), stageMAXbotan.size, botan * 1.4, U"これ!!", FontButton,
			[&]()
			{
				// ここのステージで使える素材の受け取り.
				getData().setStageNum(STAGEMAX);
				if (getData().colorChange())
				{
					getData().setFcolor(colorchangecolor_LvMAX);
					getData().setFtext(colorchangetext);
				}
				else
				{
					getData().setFcolor(color_LvMAX);
					getData().setFtext(text_LvMAX);
				}

				// ルール決め.
				uint8 ruleNum = randInt() % 3;
				if (ruleNum == 0)
				{
					// 文字でわける.
					getData().setScoreSwitch(ScoreSwitch::TextRule);
					getData().setCurrentScene(SceneSwitch::Letsplay);
					changeScene(SceneSwitch::Letsplay, 0.0);
				}
				else if (ruleNum == 1)
				{
					// 色でわける.
					getData().setScoreSwitch(ScoreSwitch::ColorRule);
					getData().setCurrentScene(SceneSwitch::Letsplay);
					changeScene(SceneSwitch::Letsplay, 0.0);
				}
				else
				{
					// 形でわける.
					getData().setScoreSwitch(ScoreSwitch::ShapeRule);
					getData().setCurrentScene(SceneSwitch::Letsplay);
					changeScene(SceneSwitch::Letsplay, 0.0);
				}
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(colorchangeBox.center(), colorchangeBox.size, bg_shiro, U"", FontButton,
			[&]()
			{
				switch (getData().currentColorMode())
				{
				case ColorSwitch::Saisyo: //はじめの色彩設定のまま.

					// on にする.
					getData().setColorChange(true);
					m_colorChangeMark = U"〆";
					getData().setColors(SortingColorsChanged);
					getData().setTexts(SortingTextsChanged);
					getData().setColorMode(ColorSwitch::ColorChange);

					break;

				case ColorSwitch::ColorChange: //色を変えたとき.

					// off にする.
					getData().setColorChange(false);
					m_colorChangeMark = U"";
					getData().setColors(SortingColorsDefault);
					getData().setTexts(SortingTextsDefault);
					getData().setColorMode(ColorSwitch::Saisyo);

					break;
				default:
					break;
				}
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(explainskipBox.center(), explainskipBox.size, bg_shiro, U"", FontButton,
			[&]()
			{
				switch (getData().currentExplainSkip())
				{
				case ExplainSkip::Saisyo: //説明し続ける場合.

					// スキップする.
					getData().setExplainSkip(true);
					m_explainSkipMark = U"〆";
					getData().setCountSwitch(CountSwitch::Start);
					getData().setExplainSkip(ExplainSkip::Skip);

					break;

				case ExplainSkip::Skip: //説明をスキップする場合.

					// スキップしない.
					getData().setExplainSkip(false);
					m_explainSkipMark = U"";
					getData().setCountSwitch(CountSwitch::ExplainRule);
					getData().setExplainSkip(ExplainSkip::Saisyo);

					break;
				default:
					break;
				}
			}
		)
	));
}

void Stage::update()
{
	const double dt = Scene::DeltaTime();

	for (auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->update(dt);
	}
}

void Stage::draw() const
{
	// ステージの説明背景.
	FontAsset(FontTitle)(m_StageName).draw(48, 50, 30, kuro);

	// 01.
	stage01textback.draw(haiiro);
	stage01textback.drawFrame(haba, kuro);
	FontAsset(FontTitle)(U"Lv.1").drawAt(stagetextSize, stage01text);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける"_fmt(getData().highScores()[STAGE01])).draw(stagetextsubSize, stage01textsub);

	// 02.
	stage02textback.draw(haiiro);
	stage02textback.drawFrame(haba, kuro);
	FontAsset(FontTitle)(U"Lv.2").drawAt(stagetextSize, stage02text);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける\n・色でわける"_fmt(getData().highScores()[STAGE02])).draw(stagetextsubSize, stage02textsub);

	// MAX.
	stageMAXtextback.draw(haiiro);
	stageMAXtextback.drawFrame(haba, kuro);
	FontAsset(FontTitle)(U"Lv.3").drawAt(stagetextSize, stageMAXtext);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける\n・色でわける\n・文字でわける"_fmt(getData().highScores()[STAGEMAX])).draw(stagetextsubSize, stageMAXtextsub);

	// 図形の見本.
	m_sampleCircle.drawFrame(haba, kuro).draw(getData().colors()[0]);
	m_sampleTriangle.drawFrame(haba, kuro).draw(getData().colors()[1]);
	m_sampleRect.drawFrame(haba, kuro).draw(getData().colors()[2]);

	// 色が見づらいかどうか.
	FontAsset(FontTitle)(U"色が見づらい場合:").drawAt(16, colorchangeText, kuro);

	// 今どっちに切り替えたかの印.
	FontAsset(FontTitle)(U"{}"_fmt(m_colorChangeMark)).drawAt(16, colorchangeBox.x + colorchangeBox.w / 2, colorchangeBox.y + colorchangeBox.h / 2, kuro);

	// 説明をスキップするかどうか.
	explainskipBox.drawFrame(haba, kuro);
	FontAsset(FontTitle)(U"説明を飛ばすとき:").drawAt(16, explainskipText, kuro);

	// 今どっちに切り替えたかの印.
	FontAsset(FontTitle)(U"{}"_fmt(m_explainSkipMark)).drawAt(16, explainskipBox.x + explainskipBox.w / 2, explainskipBox.y + explainskipBox.h / 2, kuro);

	// ボタンのレイヤーが一番上.
	for (const auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->draw();
	}
}

void Stage::drawFadeIn(double t) const
{
}

void Stage::drawFadeOut(double t) const
{
}

/*	End Stage Scene		********************************************************************************************************/

/*	Start LetsPlay Scene	********************************************************************************************************/

LetsPlay::LetsPlay(const InitData& init)
	: IScene{ init }
{
	Scene::SetBackground(bg_shiro);
	
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(explainNextButton.center(), explainNextButton.size, makuColor, U"→", FontButton,
			[&]()
			{
				getData().setCountSwitch(CountSwitch::ExplainSousa);
			}
		)
	));
	
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(explainOK.center(), explainOK.size, makuColor, U"OK", FontButton,
			[&]()
			{
				getData().setCountSwitch(CountSwitch::Start);
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(explainBackButton.center(), explainBackButton.size, makuColor, U"←", FontButton,
			[&]()
			{
				getData().setCountSwitch(CountSwitch::ExplainRule);
			}
		)
	));
	
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(startbotan.center(), startbotan.size, kuro, U"START", FontButton,
			[&]()
			{
				// 仕分けルールを表示する.
				getData().setRuleText(true);
				m_countdown.restart();
				m_playtime.reset();

				// 初期化.
				getData().initialize();

				getData().setCountSwitch(CountSwitch::Countdown);
			}
		)
	));
	
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(stopbotan.center(), stopbotan.size, murasaki, U"←", FontButton,
			[&]()
			{
				m_playtime.pause();
				m_countdown.pause();
				m_pause = true;
				getData().setPauseSwitch(PauseSwitch::PauseWindow);
			}
		)
	));
	
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(pauseRetire.center(), pauseRetire.size, daidai, U"ステージに戻る", FontButton,
			[&]()
			{
				getData().setCurrentScene(SceneSwitch::Stage);
				if (getData().explainSkip())
				{
					getData().setCountSwitch(CountSwitch::Start);
				}
				else
				{
					getData().setCountSwitch(CountSwitch::ExplainRule);
				}
				getData().setFigureSwitch(FigureSwitch::Break);
				getData().initialize();
				m_gt = 0;
				m_playtime.reset();
				m_countdown.reset();
				getData().setRuleText(false);
				m_pause = false;
				getData().setPauseSwitch(PauseSwitch::BackButton);
				changeScene(SceneSwitch::Stage, 0.0);
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(pauseContinue.center(), pauseContinue.size, daidai, U"つづける", FontButton,
			[&]()
			{
				m_playtime.resume();
				m_countdown.resume();
				m_pause = false;
				getData().setCurrentScene(SceneSwitch::Letsplay);
				getData().setPauseSwitch(PauseSwitch::BackButton);
				changeScene(SceneSwitch::Letsplay, 0.0);
			}
		)
	));

	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(stopbotan.center(), stopbotan.size, murasaki, U"←", FontButton,
			[&]()
			{
				m_playtime.resume();
				m_countdown.resume();
				m_pause = false;
				getData().setCurrentScene(SceneSwitch::Letsplay);
				getData().setPauseSwitch(PauseSwitch::BackButton);
				changeScene(SceneSwitch::Letsplay, 0.0);
			}
		)
	));
}

void LetsPlay::update()
{
	// 分別はこ下側.
	box_under(ubox_left, getData().Fcolor()[left]);
	box_under(ubox_mdle, getData().Fcolor()[mdle]);
	box_under(ubox_rght, getData().Fcolor()[rght]);

	// 正誤判定.
	// 時間という概念？の取得.
	int32 t_tf = (m_truefalse.ms() / 30);
	switch (m_tof) {
	case TrueOrFalse::WaitSort: // 仕分け待ち.
		break;

	case TrueOrFalse::TrueSort: // 正解した時.
	{
		// 正解したエフェクト.
		effect_TrueOrFalse(t_tf, getData().comboNum(), kuro, text, 30);

		// 時間経過で消す.
		if (t_tf > 20) {
			m_truefalse.reset();
			m_tof = TrueOrFalse::WaitSort;
		}
		break;
	}
	case TrueOrFalse::FalseSort: // 間違えたとき.
	{
		// 間違えた時のエフェクト.
		effect_TrueOrFalse(t_tf, getData().comboNum(), kuro, text, 30);
		if (t_tf > 20) {
			m_truefalse.reset();
			m_tof = TrueOrFalse::WaitSort;
		}
		break;
	}
	default:
		break;
	}

	// 動かす図形.
	switch (getData().currentFigureSwitch()) {
	case FigureSwitch::Break: // 待機画面.
		break;

	case FigureSwitch::MakeFigure: // 図形生成.
	{
		// 生成した回数の記録.
		getData().countClassifyNum();

		// 図形の出現座標と大きさの代入.
		figure.center = center;
		figure.size = size;
		figure.textSize = textSize;
		figure.textcolor = kuro;

		// 図形の色と文字を決める.
		decide_color(figure, getData().stageNum(), getData().colorChange());
		decide_text(figure, getData().stageNum(), getData().colorChange());

		// 図形の形を決める.
		uint8 shapeNum = randInt() % 3;
		if (shapeNum == 0)
		{
			// まる.
			circle = { figure.center, figure.size / 2 };

			// さんかく,しかくはなんもなし描画をする.
			triangle = { figure.center.x, figure.center.y, 0 };
			rect = { Arg::center(center_X, center_Y), 0 };
			getData().setFigureSwitch(FigureSwitch::Release);
			break;
		}
		else if (shapeNum == 1)
		{
			// さんかく.
			// ちょっと大きくする.
			figure.size *= 1.3;
			triangle = { center_X, center_Y, (double)figure.size };

			// まる,しかくはなんもなし描写をする.
			circle = { figure.center, 0 };
			rect = { Arg::center(center_X, center_Y), 0 };

			// さんかくの時だけ文字の大きさを小さくする.
			figure.textSize *= 0.8;
			getData().setFigureSwitch(FigureSwitch::Release);
			break;
		}
		else if (shapeNum == 2)
		{
			// しかく.
			rect = { Arg::center(center_X, center_Y), figure.size };

			// まる,さんかくはなんもなし描写をする.
			circle = { figure.center, 0 };
			triangle = { figure.center.x, figure.center.y, 0 };
			getData().setFigureSwitch(FigureSwitch::Release);
			break;
		}

		break;
	}


	case FigureSwitch::Release: // 図形をつかんでないとき.

		// 落とした場所に図形を描写する.
		circle.draw(figure.color);
		circle.drawFrame(haba, kuro);
		triangle.draw(figure.color);
		triangle.drawFrame(haba, kuro);
		rect.draw(figure.color);
		rect.drawFrame(haba, kuro);
		text(figure.text).drawAt(figure.textSize, figure.center, figure.textcolor);

		// 図形をつかんだとき.
		/*Print <<U"circle" << circle.mouseOver();
		Print << U"triangle" << triangle.mouseOver();
		Print << U"rectr" << rect.mouseOver();*/
		// triangle の一辺が 0 だと,当たり判定が常に true になるバグあり.
		if ((circle.mouseOver() || (triangle.mouseOver() && culc_Length(triangle) != 0) || rect.mouseOver()) && not m_pause)
		{
			// 手にする.
			Cursor::RequestStyle(CursorStyle::Hand);

			if (MouseL.pressed())
			{
				// カーソルと図形の中心座標の差をとる.
				m_distance_x = figure.center.x - Cursor::Pos().x;
				m_distance_y = figure.center.y - Cursor::Pos().y;

				getData().setFigureSwitch(FigureSwitch::Catch);
			}
		}

		break;

	case FigureSwitch::Catch: // 図形をつかんで運ぶとき.

		Cursor::RequestStyle(CursorStyle::Hand);

		// 移動させる.
		if (MouseL.pressed())
		{
			Circle{ check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure), circle.r }.draw(figure.color);
			Circle{ check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure), circle.r }.drawFrame(haba, kuro);
			Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + m_distance_y, figure), culc_Length(triangle) }.draw(figure.color);
			Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + m_distance_y, figure), culc_Length(triangle) }.drawFrame(haba, kuro);
			RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure)), rect.size }.draw(figure.color);
			RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure)), rect.size }.drawFrame(haba, kuro);
			text(figure.text).drawAt(figure.textSize, check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure), figure.textcolor);
		}

		// 図形を離したとき.
		if (MouseL.up())
		{
			// 図形を書いて穴埋め.
			Circle{ check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure), circle.r }.draw(figure.color);
			Circle{ check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure), circle.r }.drawFrame(haba, kuro);
			Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + m_distance_y, figure), culc_Length(triangle) }.draw(figure.color);
			Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + m_distance_y, figure), culc_Length(triangle) }.drawFrame(haba, kuro);
			RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure)), rect.size }.draw(figure.color);
			RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure)), rect.size }.drawFrame(haba, kuro);
			text(figure.text).drawAt(figure.textSize, check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure), check_wally(wally, Cursor::Pos().y + m_distance_y, figure), figure.textcolor);

			// 図形の中心座標を離した座標に更新.
			figure.center.x = check_wallx(wallx, Cursor::Pos().x + m_distance_x, figure);
			figure.center.y = check_wally(wally, Cursor::Pos().y + m_distance_y, figure);
			circle.center = figure.center;
			triangle = { figure.center, culc_Length(triangle) };
			rect.x = culc_lx(figure);
			rect.y = culc_ly(figure);
			getData().setFigureSwitch(FigureSwitch::Release);
			break;
		}
		break;
	default:
		break;
	}

	// 分別はこ上側.
	box_over(obox_left, getData().Fcolor()[left], text, U"●");
	text(U"\n{}"_fmt(getData().Ftext()[left])).drawAt(obox_left.x + obox_left.w / 2, obox_left.y + obox_left.h * 3 / 5, kuro);
	box_over(obox_mdle, getData().Fcolor()[mdle], text, U"▲");
	text(U"\n{}"_fmt(getData().Ftext()[mdle])).drawAt(obox_mdle.x + obox_mdle.w / 2, obox_mdle.y + obox_mdle.h * 3 / 5, kuro);
	box_over(obox_rght, getData().Fcolor()[rght], text, U"■");
	text(U"\n{}"_fmt(getData().Ftext()[rght])).drawAt(obox_rght.x + obox_rght.w / 2, obox_rght.y + obox_rght.h * 3 / 5, kuro);

	// 制限時間.
	m_gt = m_playtime.s();
	text(U"time(s):{}"_fmt(m_timelimit - m_gt)).draw(20, 60, kuro);

	// 時間切れになったとき.
	if (m_timelimit - m_gt <= 0)
	{
		m_playtime.reset();
		m_gt = 0;
		getData().setCurrentScene(SceneSwitch::Result);
		//m_resultwindow.restart();

		// ハイスコアを更新したかどうかの記録.
		if (getData().highScores()[getData().stageNum()] < getData().score())
		{
			getData().setHighScore(getData().stageNum(), getData().score());
			getData().setNewRecord(true);
		}

		// 得点がマイナスになっていた場合 0 にする.
		if (getData().score() < 0)
		{
			getData().addScore(-getData().score());
		}
		changeScene(SceneSwitch::Result, 0.0);
	}

	// スコア.
	switch (getData().currentScoreSwitch()) {
	case ScoreSwitch::ShapeRule: // 形で分ける.

		if (getData().ruleText())
		{
			text(U"かたちで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
		}

		// left は,まる.
		if (circle.intersects(ubox_left) || rect.intersects(ubox_left) || triangle.intersects(ubox_left))
		{
			if (circle.r != 0)
			{
				// 加点する.
				getData().addScore(Score[getData().stageNum()][plus]);

				// 正解の回数の記録.
				getData().countCorrectNum();

				// 連続正解の回数を記録.
				getData().countComboNum();

				// 正解エフェクトを出す.
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				// 減点する.
				getData().addScore(Score[getData().stageNum()][minus]);

				// ミスした回数の記録.
				getData().countMissNum();

				// 連続正解の回数を 0 に戻す.
				getData().resetComboNum();

				// 間違えたエフェクトを出すへ.
				m_tof = TrueOrFalse::FalseSort;
			}

			// 新たに図形を作る.
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		// mdle は,さんかく.
		if (circle.intersects(ubox_mdle) || rect.intersects(ubox_mdle) || triangle.intersects(ubox_mdle))
		{
			if (culc_Length(triangle) != 0)
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		// right は,しかく.
		if (circle.intersects(ubox_rght) || rect.intersects(ubox_rght) || triangle.intersects(ubox_rght))
		{
			if (rect.w != 0)
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		break;
	case ScoreSwitch::ColorRule: // 色で分ける.

		if (getData().ruleText())
		{
			text(U"いろで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
		}

		// left は,赤.
		if (circle.intersects(ubox_left) || rect.intersects(ubox_left) || triangle.intersects(ubox_left))
		{
			if (figure.color == aka || (getData().colorChange() && figure.color == red))
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		// mdle は,緑.
		if (circle.intersects(ubox_mdle) || rect.intersects(ubox_mdle) || triangle.intersects(ubox_mdle))
		{
			if (figure.color == midori || (getData().colorChange() && figure.color == yelow))
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}
		// right は,青.
		if (circle.intersects(ubox_rght) || rect.intersects(ubox_rght) || triangle.intersects(ubox_rght))
		{
			if (figure.color == ao || (getData().colorChange() && figure.color == blue))
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		break;

	case ScoreSwitch::TextRule: // 文字で分ける.

		if (getData().ruleText())
		{
			text(U"もじで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
		}

		// left は,"あか".
		if (circle.intersects(ubox_left) || rect.intersects(ubox_left) || triangle.intersects(ubox_left))
		{
			if (figure.text == U"あか" || (getData().colorChange() && figure.text == U"まる"))
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}
		// mdle は,"みどり".
		if (circle.intersects(ubox_mdle) || rect.intersects(ubox_mdle) || triangle.intersects(ubox_mdle))
		{
			if (figure.text == U"みどり" || (getData().colorChange() && figure.text == U"さんかく"))
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		// right は,"あお".
		if (circle.intersects(ubox_rght) || rect.intersects(ubox_rght) || triangle.intersects(ubox_rght))
		{
			if (figure.text == U"あお" || (getData().colorChange() && figure.text == U"しかく"))
			{
				getData().addScore(Score[getData().stageNum()][plus]);
				getData().countCorrectNum();
				getData().countComboNum();
				m_tof = TrueOrFalse::TrueSort;
			}
			else
			{
				getData().addScore(Score[getData().stageNum()][minus]);
				getData().countMissNum();
				getData().resetComboNum();
				m_tof = TrueOrFalse::FalseSort;
			}
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 正誤判定の動きの再始動.
			m_truefalse.restart();

			break;
		}

		break;

	default:
		break;
	}

	// 説明とカウントダウン画面.
	switch (getData().currentCountSwitch())
	{
	case CountSwitch::Break: // 待機画面.
		break;

	case CountSwitch::ExplainRule: // 仕分けルール説明.

		// ちょっと暗くする.
		makuSize.draw(makuColor);

		// 説明窓.
		explainWindow.draw(shiro);
		explainWindow.drawFrame(haba, kuro);
		text(U"-ルール説明-").draw(30, explainMain, kuro);
		text(U"「かたち」は\n図形の形").drawAt(26, explainSubShape, kuro);
		text(U"「いろ」は\n図形の色").drawAt(26, explainSubColor, kuro);
		text(U"「もじ」は\n図形の文字").drawAt(26, explainSubText, kuro);

		// 区切りの線.
		Line{ explainLineLeftBegin, explainLineLeftEnd }.draw(haba, kuro);
		Line{ explainLineRightBegin, explainLineRightEnd }.draw(haba, kuro);

		// 飾りの図形.
		explainShapeCircle.draw(getData().colors()[1]);
		explainShapeCircle.drawFrame(haba, kuro);
		explainShapeTriangle.draw(getData().colors()[1]);
		explainShapeTriangle.drawFrame(haba, kuro);
		explainShapeRect.draw(getData().colors()[1]);
		explainShapeRect.drawFrame(haba, kuro);

		explainColorCircle.draw(getData().colors()[0]);
		explainColorCircle.drawFrame(haba, kuro);
		explainColorTriangle.draw(getData().colors()[1]);
		explainColorTriangle.drawFrame(haba, kuro);
		explainColorRect.draw(getData().colors()[2]);
		explainColorRect.drawFrame(haba, kuro);

		text(getData().texts()[0]).draw(30, explainTextmaru, kuro);
		text(getData().texts()[1]).draw(30, explainTextsankaku, kuro);
		text(getData().texts()[2]).draw(30, explainTextshikaku, kuro);

		break;

	case CountSwitch::ExplainSousa: // 図形の動かし方の説明.

		// ちょっと暗くする.
		makuSize.draw(makuColor);

		// 説明窓.
		explainWindow.draw(shiro);
		explainWindow.drawFrame(haba, kuro);
		text(U"-操作方法-").draw(30, explainMain, kuro);
		text(U"左クリックでつかんで移動!!").drawAt(30, 400, 300, kuro);

		break;

	case CountSwitch::Start: // スタートボタンを押す.

		// ちょっと暗くする.
		makuSize.draw(makuColor);

		// START ボタンがクリックできることを分かりやすく.
		text(U"クリックしてスタート").drawAt(16, 400, 340, kuro);

		break;

	case CountSwitch::Countdown: // スタートのカウントダウン.
	{
		m_t_cd = m_countdown.sF();
		const double t_cdmaku = Min(m_countdown.sF() / 2, 1.0);

		// 開幕演出.
		m_boxOutQuad_adu(t_cdmaku, makuSize, makuColor);
		if (m_t_cd <= 1)
		{
			text(U"3").drawAt(countdownsize, countdownpoint, kuro);

			// ルールの読み忘れを無くす矢印.
			text(U"↑").drawAt(50, yondeyoLeft, kuro);
			text(U"↑").drawAt(50, yondeyoRight, kuro);
			break;
		}
		else if (1 < m_t_cd && m_t_cd <= 2)
		{
			text(U"2").drawAt(countdownsize, countdownpoint, kuro);
			break;
		}
		else if (2 < m_t_cd && m_t_cd <= 3)
		{
			text(U"1").drawAt(countdownsize, countdownpoint, kuro);

			// ルールの読み忘れを無くす矢印.
			text(U"↑").drawAt(50, yondeyoLeft, kuro);
			text(U"↑").drawAt(50, yondeyoRight, kuro);
			break;
		}
		else if (3 < m_t_cd && m_t_cd <= 4)
		{
			text(U"START!!").drawAt(countdownsize, countdownpoint, kuro);
		}
		if (4 < m_t_cd)
		{
			m_countdown.reset();
			m_t_cd = 0.0;
			getData().setCountSwitch(CountSwitch::Break);
			getData().setFigureSwitch(FigureSwitch::MakeFigure);

			// 制限時間の開始.
			m_playtime.restart();
			break;
		}
		break;
	}
	default:
		break;
	}

	// 中断するボタン.
	switch (getData().currentPauseSwitch())
	{
	case PauseSwitch::BackButton: // 一時停止ボタン.

		break;

	case PauseSwitch::PauseWindow: // 中断ボタンを押したとき.

		// 一時停止のウィンドウ.
		pauseWindow.draw(ColorF{ 0.7, 0.7, 0.7, 0.8 });
		pauseWindow.drawFrame(haba, kuro);
		text(U"--PAUSE--").drawAt(40, (pauseWindow.x + pauseWindow.w / 2), (pauseWindow.y + pauseWindow.h / 3), kuro);

		break;
	default:
		break;
	}
}

void LetsPlay::draw() const
{
	for (const auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->draw();
	}
}

void LetsPlay::drawFadeIn(double t) const
{
}

void LetsPlay::drawFadeOut(double t) const
{
}

/*	End LetsPlay Scene		********************************************************************************************************/

/*	Start Result Scene	********************************************************************************************************/

Result::Result(const InitData& init)
	: IScene{ init }
{
	Scene::SetBackground(bg_shiro);
	m_resultwindow.restart();

	// 0 番目.
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(hajimeru.center(), hajimeru.size, kiiro, U"もう一回", FontButton,
			[&]()
			{
				getData().setCurrentScene(SceneSwitch::Letsplay);

				if (getData().explainSkip())
				{
					getData().setCountSwitch(CountSwitch::Start);
				}
				else
				{
					getData().setCountSwitch(CountSwitch::ExplainRule);
				}
				getData().setFigureSwitch(FigureSwitch::Break);
				getData().initialize();
				getData().setRuleText(false);
				m_resultwindow.reset();
				/*m_resulttext01.reset();
				m_resulttext02.reset();
				m_resulttext03.reset();*/
				changeScene(SceneSwitch::Letsplay, 0.0);
			}
		),
		onemoreAppearPoint, 1s, [](double t)->double { return easeOutExpo(t); }
	));

	// 1 番目.
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(hajimeru.center(), hajimeru.size, kiiro, U"ステージへ", FontButton,
			[&]()
			{
				getData().setCurrentScene(SceneSwitch::Stage);

				if (getData().explainSkip())
				{
					getData().setCountSwitch(CountSwitch::Start);
				}
				else
				{
					getData().setCountSwitch(CountSwitch::ExplainRule);
				}
				getData().setFigureSwitch(FigureSwitch::Break);
				getData().initialize();
				getData().setRuleText(false);
				m_resultwindow.reset();
				/*m_resulttext01.reset();
				m_resulttext02.reset();
				m_resulttext03.reset();*/
				changeScene(SceneSwitch::Stage, 0.0);
			}
		),
		backstageAppearPoint, 1.1s, [](double t)->double { return easeOutExpo(t); }
	));

	// 2 番目.
	m_buttonPtrs.push_back(makeButton(
		ButtonCtx(hajimeru.center(), hajimeru.size, murasaki * 1.4, U"タイトルへ", FontButton,
			[&]()
			{
				getData().setCurrentScene(SceneSwitch::Title);

				if (getData().explainSkip())
				{
					getData().setCountSwitch(CountSwitch::Start);
				}
				else
				{
					getData().setCountSwitch(CountSwitch::ExplainRule);
				}
				getData().setFigureSwitch(FigureSwitch::Break);
				getData().initialize();
				getData().setRuleText(false);
				m_resultwindow.reset();
				/*m_resulttext01.reset();
				m_resulttext02.reset();
				m_resulttext03.reset();*/
				changeScene(SceneSwitch::Title, 0.0);
			}
		),
		backtitleAppearPoint, 1.2s, [](double t)->double { return easeOutExpo(t); }
	));
}

void Result::update()
{
	const double dt = Scene::DeltaTime();

	for (auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->update(dt);
	}
}

void Result::draw() const
{
	// イージング関数用の時間変数.
	const double t_rw = Min(m_resultwindow.sF(), 1.0);

	// さっきまでの背景たち.
	// 分別はこ下側.
	box_under(ubox_left, getData().Fcolor()[left]);
	box_under(ubox_mdle, getData().Fcolor()[mdle]);
	box_under(ubox_rght, getData().Fcolor()[rght]);

	// 図形たち.
	getData().circle().draw(getData().figure().color);
	getData().circle().drawFrame(haba, kuro);
	getData().triangle().draw(getData().figure().color);
	getData().triangle().drawFrame(haba, kuro);
	getData().rect().draw(getData().figure().color);
	getData().rect().drawFrame(haba, kuro);
	FontAsset(FontButton)(getData().figure().text).drawAt(getData().figure().textSize, getData().figure().center, getData().figure().textcolor);

	// 分別はこ上側.
	box_over(obox_left, getData().Fcolor()[left], FontAsset(FontButton), U"●");
	FontAsset(FontButton)(U"\n{}"_fmt(getData().Ftext()[left])).drawAt(obox_left.x + obox_left.w / 2, obox_left.y + obox_left.h * 3 / 5, kuro);
	box_over(obox_mdle, getData().Fcolor()[mdle], FontAsset(FontButton), U"▲");
	FontAsset(FontButton)(U"\n{}"_fmt(getData().Ftext()[mdle])).drawAt(obox_mdle.x + obox_mdle.w / 2, obox_mdle.y + obox_mdle.h * 3 / 5, kuro);
	box_over(obox_rght, getData().Fcolor()[rght], FontAsset(FontButton), U"■");
	FontAsset(FontButton)(U"\n{}"_fmt(getData().Ftext()[rght])).drawAt(obox_rght.x + obox_rght.w / 2, obox_rght.y + obox_rght.h * 3 / 5, kuro);

	// 幕を下ろす.
	m_boxBounce_aud(t_rw, makuSize, makuColor);

	// 結果表示.
	// 結果.
	m_textBounce_aud(t_rw, resultText, FontAsset(FontButton), U"★RESULT★", 80);

	// 獲得スコア.
	m_textBounce_aud(t_rw, yourscoreText, FontAsset(FontButton), U"Your Score:{}"_fmt(getData().score()), 36);

	// ハイスコア.
	m_textBounce_aud(t_rw, highscoreText, FontAsset(FontButton), U"High Score:{}"_fmt(getData().highScores()[getData().stageNum()]), 20);

	// 記録を更新したか.
	if (getData().newRecord())
	{
		m_textBounce_aud(t_rw, newrecordText, FontAsset(FontButton), U"New Record!!", 20);
	}

	// 最大コンボ数.
	//m_textOutExpo_aap(t_rt01, sortedTextAppearPoint, sortedText, kuro, text, U"combo:{}"_fmt(comboNum), 30);

	// 何個仕分けをしたか.
	//m_textOutExpo_aap(t_rt01, sortedTextAppearPoint, sortedText, kuro, FontAsset(FontButton), U"sorted:{}"_fmt(getData().classifyNum() - 1), 30);
	const auto sortedPtr = dynamic_cast<ButtonRectMove*>(m_buttonPtrs.at(0).get());
	if (sortedPtr != nullptr)
	{
		m_textOutExpo_aap(sortedPtr->rate(), sortedTextAppearPoint, sortedText, kuro, FontAsset(FontButton), U"sorted:{}"_fmt(getData().classifyNum() - 1), 30);
	}
	else
	{
		Print << U"Result: 0 番目のボタンは ButtonRectMove ではありません.";
	}

	// 何個仕分けを正しくできたか.
	//m_textOutExpo_aap(t_rt02, trueTextAppearPoint, trueText, kuro, FontAsset(FontButton), U"true:{}"_fmt(getData().correctNum()), 30);
	const auto truePtr = dynamic_cast<ButtonRectMove*>(m_buttonPtrs.at(1).get());
	if (truePtr != nullptr)
	{
		m_textOutExpo_aap(truePtr->rate(), trueTextAppearPoint, trueText, kuro, FontAsset(FontButton), U"true:{}"_fmt(getData().correctNum()), 30);
	}
	else
	{
		Print << U"Result: 1 番目のボタンは ButtonRectMove ではありません.";
	}

	// 何個ミスをしたか.
	//m_textOutExpo_aap(t_rt03, missTextAppearPoint, missText, kuro, FontAsset(FontButton), U"miss:{}"_fmt(getData().missNum()), 30);
	const auto missPtr = dynamic_cast<ButtonRectMove*>(m_buttonPtrs.at(2).get());
	if (missPtr != nullptr)
	{
		m_textOutExpo_aap(missPtr->rate(), missTextAppearPoint, missText, kuro, FontAsset(FontButton), U"miss:{}"_fmt(getData().missNum()), 30);
	}
	else
	{
		Print << U"Result: 2 番目のボタンは ButtonRectMove ではありません.";
	}

	// ボタンのレイヤーが上.
	for (const auto& it : m_buttonPtrs)
	{
		if (it != nullptr) it->draw();
	}
}

void Result::drawFadeIn(double t) const
{
}

void Result::drawFadeOut(double t) const
{
}

/*	End Result Scene		********************************************************************************************************/
