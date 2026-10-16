#include "stdafx.h"
#include "GameScene.h"

/*	Start Game Scene	********************************************************************************************************/

void GameScene::makeButton(const ButtonTableKey key, const ButtonCtx& ctx, ButtonWorkCallBack workCallBack)
{
	auto ptr = std::make_unique<ButtonRect>(ctx);

	ptr->setWorkCallBack([workCallBack, p = ptr.get()]() { workCallBack(p); });

	m_buttonTable[key].push_back(std::move(ptr));
}

void GameScene::makeButton(const ButtonTableKey key, const ButtonCtx& ctx, ButtonWorkCallBack workCallBack, const Vec2& from, const double delay, ButtonRectMove::Easing easing)
{
	auto ptr = std::make_unique<ButtonRectMove>(ctx, from, delay, easing);

	ptr->setWorkCallBack([workCallBack, p = ptr.get()]() { workCallBack(p); });

	m_buttonTable[key].push_back(std::move(ptr));
}

void GameScene::updateButtonsAt(const ButtonTableKey key)
{
	auto it = m_buttonTable.find(key);	// .at() ではエラー落ちするので調べておく.
	if (it == m_buttonTable.end())
	{
		Print << U"updateButtonsAt: 未登録の key {} です."_fmt(key);
		return;
	}

	for (auto& button : it->second)
	{
		if (button != nullptr) button->update();
	}
}

void GameScene::drawButtonsAt(const ButtonTableKey key) const
{
	const auto& it = m_buttonTable.find(key);
	if (it == m_buttonTable.end())
	{
		Print << U"drawButtonsAt: 未登録の key {} です."_fmt(key);
		return;
	}

	for (const auto& button : it->second)
	{
		if (button != nullptr) button->draw();
	}
}

void GameScene::enableButtonsAt(const ButtonTableKey key)
{
	for (auto& it : m_buttonTable[key])
	{
		it->turnOnDraw();
		it->turnOnPerform();
	}
}

/*	End Game Scene		********************************************************************************************************/

/*	Start Title Scene	********************************************************************************************************/

Title::Title(const InitData& init)
	: IScene{ init }
{
	initialize();

	enableButtonsAt(static_cast<ButtonTableKey>(TitleFlow::Default));
}

void Title::update()
{
	const double dt = Scene::DeltaTime();

	updateButtonsAt(static_cast<ButtonTableKey>(TitleFlow::Default));
}

void Title::draw() const
{
	drawUI();
}

void Title::drawFadeIn(double t) const
{
}

void Title::drawFadeOut(double t) const
{
}

void Title::drawUI() const
{
	FontAsset(FontTitle)(m_TitleName).drawAt(400, 100, ColorF{ 0.2 });

	drawButtonsAt(static_cast<ButtonTableKey>(TitleFlow::Default));
}

void Title::initialize()
{
	FontAsset(FontTitle).preload(m_TitleName);

	Scene::SetBackground(bg_shiro);

	makeButton(
		static_cast<ButtonTableKey>(TitleFlow::Default),
		ButtonCtx(m_gameStart, botan * 1.4, U"はじめる", FontButton),
		[&](ButtonBase* self)
		{
			getData().initialize();
			changeScene(SceneSwitch::Stage, 0.0);
		});

	makeButton(
		static_cast<ButtonTableKey>(TitleFlow::Default),
		ButtonCtx(m_quitGame, botan * 1.4, U"やめる", FontButton),
		[&](ButtonBase* self)
		{
			System::Exit();
		});
}

/*	End Title Scene		********************************************************************************************************/

/*	Start Stage Scene	********************************************************************************************************/

Stage::Stage(const InitData& init)
	: IScene{ init }
{
	initialize();

	enableButtonsAt(static_cast<ButtonTableKey>(UILayer::Default));
}

void Stage::update()
{
	updateButtonsAt(static_cast<ButtonTableKey>(UILayer::Default));
}

void Stage::draw() const
{
	drawUI();
}

void Stage::drawFadeIn(double t) const
{
}

void Stage::drawFadeOut(double t) const
{
}

void Stage::drawUI() const
{
	// ステージの説明背景.
	FontAsset(FontTitle)(m_StageName).draw(48, 50, 30, kuro);

	// 01.
	stage01textback.drawFrame(haba, kuro).draw(haiiro);
	FontAsset(FontTitle)(U"Lv.1").drawAt(stagetextSize, stage01text);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける"_fmt(getData().gameManager().scoreManager().highScores()[static_cast<EnumValue>(StageLevel::Level01)])).draw(stagetextsubSize, stage01textsub);

	// 02.
	stage02textback.drawFrame(haba, kuro).draw(haiiro);
	FontAsset(FontTitle)(U"Lv.2").drawAt(stagetextSize, stage02text);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける\n・色でわける"_fmt(getData().gameManager().scoreManager().highScores()[static_cast<EnumValue>(StageLevel::Level02)])).draw(stagetextsubSize, stage02textsub);

	// MAX.
	stageMAXtextback.drawFrame(haba, kuro).draw(haiiro);
	FontAsset(FontTitle)(U"Lv.3").drawAt(stagetextSize, stageMAXtext);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける\n・色でわける\n・文字でわける"_fmt(getData().gameManager().scoreManager().highScores()[static_cast<EnumValue>(StageLevel::LevelMAX)])).draw(stagetextsubSize, stageMAXtextsub);

	// 図形の見本.
	m_sampleCircle.drawFrame(haba, kuro).draw(FigureGenerator::SortingColorsDefault[0]);// 色変えに対応するように !!.
	m_sampleTriangle.drawFrame(haba, kuro).draw(FigureGenerator::SortingColorsDefault[1]);
	m_sampleRect.drawFrame(haba, kuro).draw(FigureGenerator::SortingColorsDefault[2]);

	FontAsset(FontTitle)(U"色が見づらい場合：").drawAt(16, colorchangeText, kuro);

	FontAsset(FontTitle)(U"説明を飛ばすとき：").drawAt(16, explainskipText, kuro);

	// ボタンのレイヤーが一番上.
	drawButtonsAt(static_cast<ButtonTableKey>(UILayer::Default));
}

void Stage::initialize()
{
	Scene::SetBackground(bg_shiro);

	m_isChangedColor = false;

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(stage01botan, botan * 1.4, U"これ!!", FontButton),
		[&](ButtonBase* self)
		{
			setupSortRule(StageLevel::Level01, getData());
			changeScene(SceneSwitch::Letsplay, 0.0);
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(stage02botan, botan * 1.4, U"これ!!", FontButton),
		[&](ButtonBase* self)
		{
			setupSortRule(StageLevel::Level02, getData());
			changeScene(SceneSwitch::Letsplay, 0.0);
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(stageMAXbotan, botan * 1.4, U"これ!!", FontButton),
		[&](ButtonBase* self)
		{
			setupSortRule(StageLevel::LevelMAX, getData());
			changeScene(SceneSwitch::Letsplay, 0.0);
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(colorchangeBox, bg_shiro, U"", FontButton),
		[&](ButtonBase* self)
		{
			if (!getData().gameManager().isChangedColor())
			{
				// on にする.
				getData().gameManager().turnOnChangedColor();
				self->setText(m_markedText);
			}
			else
			{
				// off にする.
				getData().gameManager().turnOffChangedColor();
				self->setText(U"");
			}
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(explainskipBox, bg_shiro, U"", FontButton),
		[&](ButtonBase* self)
		{
			if (!getData().gameManager().isSkippedExplain())
			{
				// スキップする.
				getData().gameManager().turnOnSkippedExplain();
				self->setText(m_markedText);
			}
			else
			{
				// スキップしない.
				getData().gameManager().turnOffSkippedExplain();
				self->setText(U"");
			}
		});

	getData().gameManager().init();
}

void Stage::setupSortRule(const StageLevel level, GameData& gd) const
{
	// 素材の準備.
	gd.gameManager().setSortRule(static_cast<EnumValue>(level));
}

/*	End Stage Scene		********************************************************************************************************/

/*	Start LetsPlay Scene	********************************************************************************************************/

LetsPlay::LetsPlay(const InitData& init)
	: IScene{ init }
{
	initialize();

	if (getData().gameManager().isSkippedExplain())
	{
		MoveNextFlow(LetsPlayFlow::Start);
	}
	else
	{
		MoveNextFlow(LetsPlayFlow::ExplainPage1);
	}
}

void LetsPlay::update()
{
	updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));

	// 制限時間.
	m_gt = m_playtime.s();
	FontAsset(FontText)(U"time(s):{}"_fmt(m_timelimit - m_gt)).draw(20, 60, kuro);

	// 時間切れになったとき.
	if (m_timelimit - m_gt <= 0)
	{
		m_playtime.reset();
		m_gt = 0;

		// ハイスコアを更新したかどうかの記録.
		//getData().gameManager().scoreManager().updateHighScores(getData().gameManager().stageLevel());

		changeScene(SceneSwitch::Result, 0.0);
	}

	// 説明とカウントダウン画面.
	switch (m_currentFlow)
	{
	case LetsPlayFlow::ExplainPage1:
		break;
	case LetsPlayFlow::ExplainPage2:
		break;
	case LetsPlayFlow::Start:
		break;
	case LetsPlayFlow::CountDown:

		//m_canDisplayRule = true;

		m_t_cd = m_countdown.sF();

		if (4 < m_t_cd)
		{
			m_countdown.reset();
			m_t_cd = 0.0;
			//m_currentFigureSwitch = FigureSwitch::MakeFigure;

			// 制限時間の開始.
			m_playtime.restart();

			MoveNextFlow(LetsPlayFlow::Play);

			break;
		}

		break;
	case LetsPlayFlow::Play:

		getData().gameManager().update();

		break;

	case LetsPlayFlow::Pause:
		break;
	default:
		break;
	}
}

void LetsPlay::draw() const
{
	drawUI();
}

void LetsPlay::drawFadeIn(double t) const
{
}

void LetsPlay::drawFadeOut(double t) const
{
}

void LetsPlay::drawUI() const
{
	// 説明とカウントダウン画面.
	switch (m_currentFlow)
	{
	case LetsPlayFlow::ExplainPage1:	// 仕分けルール説明.

		// ちょっと暗くする.
		makuSize.draw(makuColor);

		// 説明窓.
		explainWindow.drawFrame(haba, kuro).draw(shiro);
		FontAsset(FontText)(U"-ルール説明-").draw(30, explainMain, kuro);
		FontAsset(FontText)(U"「かたち」は\n図形の形").drawAt(26, explainSubShape, kuro);
		FontAsset(FontText)(U"「いろ」は\n図形の色").drawAt(26, explainSubColor, kuro);
		FontAsset(FontText)(U"「もじ」は\n図形の文字").drawAt(26, explainSubText, kuro);

		// 区切りの線.
		Line{ explainLineLeftBegin, explainLineLeftEnd }.draw(haba, kuro);
		Line{ explainLineRightBegin, explainLineRightEnd }.draw(haba, kuro);

		// 飾りの図形.
		explainShapeCircle.drawFrame(haba, kuro).draw((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[1].colors.colorChanged : ScoreManager::SortingAnswers[1].colors.colorDefault);
		explainShapeTriangle.drawFrame(haba, kuro).draw((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[1].colors.colorChanged : ScoreManager::SortingAnswers[1].colors.colorDefault);
		explainShapeRect.drawFrame(haba, kuro).draw((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[1].colors.colorChanged : ScoreManager::SortingAnswers[1].colors.colorDefault);

		explainColorCircle.drawFrame(haba, kuro).draw((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[0].colors.colorChanged : ScoreManager::SortingAnswers[0].colors.colorDefault);
		explainColorTriangle.drawFrame(haba, kuro).draw((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[1].colors.colorChanged : ScoreManager::SortingAnswers[1].colors.colorDefault);
		explainColorRect.drawFrame(haba, kuro).draw((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[2].colors.colorChanged : ScoreManager::SortingAnswers[2].colors.colorDefault);

		FontAsset(FontText)((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[0].texts.textChanged : ScoreManager::SortingAnswers[0].texts.textDefault).draw(30, explainTextmaru, kuro);
		FontAsset(FontText)((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[1].texts.textChanged : ScoreManager::SortingAnswers[1].texts.textDefault).draw(30, explainTextsankaku, kuro);
		FontAsset(FontText)((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[2].texts.textChanged : ScoreManager::SortingAnswers[2].texts.textDefault).draw(30, explainTextshikaku, kuro);

		break;

	case LetsPlayFlow::ExplainPage2:	// 図形の動かし方の説明.

		// ちょっと暗くする.
		makuSize.draw(makuColor);

		// 説明窓.
		explainWindow.drawFrame(haba, kuro).draw(shiro);
		FontAsset(FontText)(U"-操作方法-").draw(30, explainMain, kuro);
		FontAsset(FontText)(U"左クリックでつかんで移動!!").drawAt(30, 400, 300, kuro);

		break;

	case LetsPlayFlow::Start:	// スタートボタンを押す.

		// ちょっと暗くする.
		makuSize.draw(makuColor);

		// START ボタンがクリックできることを分かりやすく.
		FontAsset(FontText)(U"クリックしてスタート").drawAt(16, 400, 340, kuro);

		break;

	case LetsPlayFlow::CountDown:

	{
		const double t_cdmaku = Min(m_countdown.sF() / 2, 1.0);

		// 開幕演出.
		m_boxOutQuad_adu(t_cdmaku, makuSize, makuColor);
		if (m_t_cd <= 1)
		{
			FontAsset(FontText)(U"3").drawAt(countdownsize, countdownpoint, kuro);

			// ルールの読み忘れを無くす矢印.
			FontAsset(FontText)(U"↑").drawAt(50, yondeyoLeft, kuro);
			FontAsset(FontText)(U"↑").drawAt(50, yondeyoRight, kuro);
			break;
		}
		else if (1 < m_t_cd && m_t_cd <= 2)
		{
			FontAsset(FontText)(U"2").drawAt(countdownsize, countdownpoint, kuro);
			break;
		}
		else if (2 < m_t_cd && m_t_cd <= 3)
		{
			FontAsset(FontText)(U"1").drawAt(countdownsize, countdownpoint, kuro);

			// ルールの読み忘れを無くす矢印.
			FontAsset(FontText)(U"↑").drawAt(50, yondeyoLeft, kuro);
			FontAsset(FontText)(U"↑").drawAt(50, yondeyoRight, kuro);
			break;
		}
		else if (3 < m_t_cd && m_t_cd <= 4)
		{
			FontAsset(FontText)(U"START!!").drawAt(countdownsize, countdownpoint, kuro);
		}
	}
	break;

	case LetsPlayFlow::Play:

		// 動かす図形.
		getData().gameManager().draw();

		break;

	case LetsPlayFlow::Pause:
		break;

	default:
		break;
	}

	if (getData().gameManager().isPaused())
	{
		// 一時停止のウィンドウ.
		pauseWindow.drawFrame(haba, kuro).draw(ColorF{ 0.7, 0.7, 0.7, 0.8 });
		FontAsset(FontText)(U"--PAUSE--").drawAt(40, (pauseWindow.x + pauseWindow.w / 2), (pauseWindow.y + pauseWindow.h / 3), kuro);
	}

	drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
}

void LetsPlay::initialize()
{
	Scene::SetBackground(bg_shiro);

	/*m_figureGen.init();

	m_scoreManager.init();*/

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::ExplainPage1),
		ButtonCtx(explainNextButton, makuColor, U"→", FontButton),
		[&](ButtonBase* self)
		{
			MoveNextFlow(LetsPlayFlow::ExplainPage2);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::ExplainPage2),
		ButtonCtx(explainOK, makuColor, U"OK", FontButton),
		[&](ButtonBase* self)
		{
			MoveNextFlow(LetsPlayFlow::Start);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::ExplainPage2),
		ButtonCtx(explainBackButton, makuColor, U"←", FontButton),
		[&](ButtonBase* self)
		{
			MoveNextFlow(LetsPlayFlow::ExplainPage1);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Start),
		ButtonCtx(startbotan, kuro, U"START", FontButton),
		[&](ButtonBase* self)
		{
			// 仕分けルールを表示する.
			m_countdown.restart();
			m_playtime.reset();

			MoveNextFlow(LetsPlayFlow::CountDown);

			// 初期化.
			getData().initialize();
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Play),
		ButtonCtx(stopbotan, murasaki, U"←", FontButton),
		[&](ButtonBase* self)
		{
			m_playtime.pause();
			m_countdown.pause();
			getData().gameManager().turnOnPause();

			MoveNextFlow(LetsPlayFlow::Pause);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Pause),
		ButtonCtx(pauseRetire, daidai, U"ステージに戻る", FontButton),
		[&](ButtonBase* self)
		{
			getData().initialize();
			m_gt = 0;
			m_playtime.reset();
			m_countdown.reset();
			getData().gameManager().turnOffPause();
			changeScene(SceneSwitch::Stage, 0.0);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Pause),
		ButtonCtx(pauseContinue, daidai, U"つづける", FontButton),
		[&](ButtonBase* self)
		{
			m_playtime.resume();
			m_countdown.resume();
			getData().gameManager().turnOffPause();
			changeScene(SceneSwitch::Letsplay, 0.0);
			
			MoveNextFlow(LetsPlayFlow::Play);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Pause),
		ButtonCtx(stopbotan, murasaki, U"←", FontButton),
		[&](ButtonBase* self)
		{
			m_playtime.resume();
			m_countdown.resume();
			getData().gameManager().turnOffPause();
			changeScene(SceneSwitch::Letsplay, 0.0);
			
			MoveNextFlow(LetsPlayFlow::Play);
		});
}

void LetsPlay::MoveNextFlow(const LetsPlayFlow next)
{
	m_currentFlow = next;

	enableButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
}

/*	End LetsPlay Scene		********************************************************************************************************/

/*	Start Result Scene	********************************************************************************************************/

Result::Result(const InitData& init)
	: IScene{ init }
{
	initialize();

	enableButtonsAt(static_cast<ButtonTableKey>(ResultFlow::Default));

	const auto key = static_cast<ButtonTableKey>(ResultFlow::Default);
	const auto& it = m_buttonTable.find(key);
	if (it == m_buttonTable.end())
	{
		Print << U"Result::Result: 未登録の key {} です."_fmt(key);
	}
	else
	{
		for (auto& button : it->second)
		{
			if (button == nullptr) continue;

			if (const auto& btn = dynamic_cast<ButtonRectMove*>(button.get()))
			{
				btn->startStopwatch();
			}
		}
	}
}

void Result::update()
{
	const double dt = Scene::DeltaTime();

	updateButtonsAt(static_cast<ButtonTableKey>(ResultFlow::Default));
}

void Result::draw() const
{
	// イージング関数用の時間変数.
	const double t_rw = Min(m_resultwindow.sF(), 1.0);

	// さっきまでの背景たち.
	getData().gameManager().draw();

	// 幕を下ろす.
	m_boxBounce_aud(t_rw, makuSize, makuColor);

	// 結果表示.
	// 結果.
	m_textBounce_aud(t_rw, resultText, FontAsset(FontButton), U"★RESULT★", 80);

	// 獲得スコア.
	m_textBounce_aud(t_rw, yourscoreText, FontAsset(FontButton), U"Your Score:{}"_fmt(getData().gameManager().scoreManager().score()), 36);

	// ハイスコア.
	m_textBounce_aud(t_rw, highscoreText, FontAsset(FontButton), U"High Score:{}"_fmt(getData().gameManager().scoreManager().highScores()[static_cast<EnumValue>(getData().gameManager().stageLevel())]), 20);

	// 記録を更新したか.
	if (getData().gameManager().scoreManager().newRecord())
	{
		m_textBounce_aud(t_rw, newrecordText, FontAsset(FontButton), U"New Record!!", 20);
	}

	// 最大コンボ数.
	//m_textOutExpo_aap(t_rt01, sortedTextAppearPoint, sortedText, kuro, text, U"combo:{}"_fmt(comboNum), 30);

	const auto key = static_cast<ButtonTableKey>(ResultFlow::Default);
	const auto& table = m_buttonTable.find(key);
	if (table == m_buttonTable.end())
	{
		Print << U"Result.draw: 未登録の key {} です."_fmt(key);
	}
	else
	{
		const auto& buttons = table->second;

		// 何個仕分けをしたか.
		if (const auto& sortedPtr = dynamic_cast<ButtonRectMove*>(buttons[0].get()))
		{
			if (sortedPtr == nullptr)
			{
				Print << U"Result: 0 番目のボタンは ButtonRectMove ではありません.";
			}
			else
			{
				m_textOutExpo_aap(sortedPtr->rate(), sortedTextAppearPoint, sortedText, kuro, FontAsset(FontButton), U"sorted:{}"_fmt(getData().gameManager().scoreManager().classifyNum() - 1), 30);
			}
		}

		// 何個仕分けを正しくできたか.
		if (const auto& truePtr = dynamic_cast<ButtonRectMove*>(buttons[1].get()))
		{
			if (truePtr != nullptr)
			{
				m_textOutExpo_aap(truePtr->rate(), trueTextAppearPoint, trueText, kuro, FontAsset(FontButton), U"true:{}"_fmt(getData().gameManager().scoreManager().correctNum()), 30);
			}
			else
			{
				Print << U"Result: 1 番目のボタンは ButtonRectMove ではありません.";
			}
		}

		// 何個ミスをしたか.
		if (const auto missPtr = dynamic_cast<ButtonRectMove*>(buttons[2].get()))
		{
			if (missPtr != nullptr)
			{
				m_textOutExpo_aap(missPtr->rate(), missTextAppearPoint, missText, kuro, FontAsset(FontButton), U"miss:{}"_fmt(getData().gameManager().scoreManager().missNum()), 30);
			}
			else
			{
				Print << U"Result: 2 番目のボタンは ButtonRectMove ではありません.";
			}
		}
	}

	drawUI();
}

void Result::drawFadeIn(double t) const
{
}

void Result::drawFadeOut(double t) const
{
}

void Result::drawUI() const
{
	// ボタンのレイヤーが上.
	drawButtonsAt(static_cast<ButtonTableKey>(ResultFlow::Default));
}

void Result::initialize()
{
	Scene::SetBackground(bg_shiro);
	m_resultwindow.restart();

	// 0 番目.
	makeButton(
		static_cast<ButtonTableKey>(ResultFlow::Default),
		ButtonCtx(m_playAgain, kiiro, U"もう一回", FontButton),
		[&](ButtonBase* self)
		{
			getData().initialize();
			
			m_resultwindow.reset();
			
			changeScene(SceneSwitch::Letsplay, 0.0);
		},
		m_playAgainAppearPoint, 1.0, easeOutExpo);

	// 1 番目.
	makeButton(
		static_cast<ButtonTableKey>(ResultFlow::Default),
		ButtonCtx(m_backStage, kiiro, U"ステージへ", FontButton),
		[&](ButtonBase* self)
		{
			getData().initialize();
			
			m_resultwindow.reset();
			
			changeScene(SceneSwitch::Stage, 0.0);
		},
		m_backStageAppearPoint, 1.1, easeOutExpo);

	// 2 番目.
	makeButton(
		static_cast<ButtonTableKey>(ResultFlow::Default),
		ButtonCtx(m_backTitle, murasaki * 1.4, U"タイトルへ", FontButton),
		[&](ButtonBase* self)
		{
			getData().initialize();
			
			m_resultwindow.reset();
			
			changeScene(SceneSwitch::Title, 0.0);
		},
		m_backTitleAppearPoint, 1.2, easeOutExpo);
}

/*	End Result Scene		********************************************************************************************************/
