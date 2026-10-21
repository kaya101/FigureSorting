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
	AudioAsset(AudioManager::get().getName(BGMID::Title)).play();

	updateButtonsAt(static_cast<ButtonTableKey>(TitleFlow::Default));
}

void Title::draw() const
{
	FontAsset(FontTitle)(m_TitleName).drawAt(400, 100, ColorF{ 0.2 });

	drawButtonsAt(static_cast<ButtonTableKey>(TitleFlow::Default));
}

void Title::drawFadeIn(double t) const
{
	getData().uiManager().fadeIn(t);
}

void Title::drawFadeOut(double t) const
{
	AudioAsset(AudioManager::get().getName(BGMID::Title)).stop(FadeTime);

	getData().uiManager().fadeOut(t);
}

void Title::initialize()
{
	FontAsset(FontTitle).preload(m_TitleName);

	Scene::SetBackground(bg_shiro);

	makeButton(
		static_cast<ButtonTableKey>(TitleFlow::Default),
		ButtonCtx(m_gameStart, botan * 1.4, U"はじめる", FontButton),
		[this](ButtonBase* self)
		{
			changeScene(SceneSwitch::Stage, FadeTime);
		});

	makeButton(
		static_cast<ButtonTableKey>(TitleFlow::Default),
		ButtonCtx(m_quitGame, botan * 1.4, U"やめる", FontButton),
		[this](ButtonBase* self)
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
	AudioAsset(AudioManager::get().getName(BGMID::Stage)).play(FadeTime);

	updateButtonsAt(static_cast<ButtonTableKey>(UILayer::Default));
}

void Stage::draw() const
{
	// ステージの説明背景.
	FontAsset(FontTitle)(m_StageName).draw(48, 50, 30, kuro);

	// 01.
	stage01textback.drawFrame(haba, kuro).draw(haiiro);
	FontAsset(FontTitle)(U"Lv.1").drawAt(stagetextSize, stage01text);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける"_fmt(getData().scoreManager().highScores()[static_cast<EnumValue>(StageLevel::Level01)])).draw(stagetextsubSize, stage01textsub);

	// 02.
	stage02textback.drawFrame(haba, kuro).draw(haiiro);
	FontAsset(FontTitle)(U"Lv.2").drawAt(stagetextSize, stage02text);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける\n・色でわける"_fmt(getData().scoreManager().highScores()[static_cast<EnumValue>(StageLevel::Level02)])).draw(stagetextsubSize, stage02textsub);

	// MAX.
	stageMAXtextback.drawFrame(haba, kuro).draw(haiiro);
	FontAsset(FontTitle)(U"Lv.3").drawAt(stagetextSize, stageMAXtext);
	FontAsset(FontTitle)(U"High Score:{}\n\n・形でわける\n・色でわける\n・文字でわける"_fmt(getData().scoreManager().highScores()[static_cast<EnumValue>(StageLevel::LevelMAX)])).draw(stagetextsubSize, stageMAXtextsub);

	// 図形の見本.
	m_sampleCircle.drawFrame(haba, kuro).draw(getData().uiManager().color(SortingBoxIdx::Left));
	m_sampleTriangle.drawFrame(haba, kuro).draw(getData().uiManager().color(SortingBoxIdx::Midle));
	m_sampleRect.drawFrame(haba, kuro).draw(getData().uiManager().color(SortingBoxIdx::Right));

	FontAsset(FontTitle)(U"色が見づらい場合：").drawAt(16, colorchangeText, kuro);

	FontAsset(FontTitle)(U"説明を飛ばすとき：").drawAt(16, explainskipText, kuro);

	// ボタンのレイヤーが一番上.
	drawButtonsAt(static_cast<ButtonTableKey>(UILayer::Default));
}

void Stage::drawFadeIn(double t) const
{
	getData().uiManager().fadeIn(t);
}

void Stage::drawFadeOut(double t) const
{
	AudioAsset(AudioManager::get().getName(BGMID::Stage)).stop(FadeTime);

	getData().uiManager().fadeOut(t);
}

void Stage::initialize()
{
	Scene::SetBackground(bg_shiro);

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(stage01botan, botan * 1.4, U"これ!!", FontButton),
		[this](ButtonBase* self)
		{
			setupSortRule(StageLevel::Level01, getData());
			changeScene(SceneSwitch::Letsplay, FadeTime);
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(stage02botan, botan * 1.4, U"これ!!", FontButton),
		[this](ButtonBase* self)
		{
			setupSortRule(StageLevel::Level02, getData());
			changeScene(SceneSwitch::Letsplay, FadeTime);
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(stageMAXbotan, botan * 1.4, U"これ!!", FontButton),
		[this](ButtonBase* self)
		{
			setupSortRule(StageLevel::LevelMAX, getData());
			changeScene(SceneSwitch::Letsplay, FadeTime);
		});

	makeButton(
		static_cast<ButtonTableKey>(UILayer::Default),
		ButtonCtx(colorchangeBox, bg_shiro, U"", FontButton),
		[this](ButtonBase* self)
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
		[this](ButtonBase* self)
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
	const auto& it = m_updateTable.find(m_currentFlow);
	if (it != m_updateTable.end()) it->second();
}

void LetsPlay::draw() const
{
	const auto& it = m_drawTable.find(m_currentFlow);
	if (it != m_drawTable.end()) it->second();
}

void LetsPlay::drawFadeIn(double t) const
{
	getData().uiManager().fadeIn(t);
}

void LetsPlay::drawFadeOut(double t) const
{
	AudioAsset(AudioManager::get().getName(BGMID::LetsPlay)).stop(0.0s);
}

void LetsPlay::initialize()
{
	Scene::SetBackground(bg_shiro);

	m_t_cd = 0.0;
	m_gt = 0;
	m_currentFlow = LetsPlayFlow::ExplainPage1;

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::ExplainPage1),
		ButtonCtx(explainNextButton, makuColor, U"→", FontButton),
		[this](ButtonBase* self)
		{
			MoveNextFlow(LetsPlayFlow::ExplainPage2);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::ExplainPage2),
		ButtonCtx(explainOK, makuColor, U"OK", FontButton),
		[this](ButtonBase* self)
		{
			MoveNextFlow(LetsPlayFlow::Start);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::ExplainPage2),
		ButtonCtx(explainBackButton, makuColor, U"←", FontButton),
		[this](ButtonBase* self)
		{
			MoveNextFlow(LetsPlayFlow::ExplainPage1);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Start),
		ButtonCtx(startbotan, kuro, U"START", FontButton),
		[this](ButtonBase* self)
		{
			// 仕分けルールを表示する.
			m_countdown.restart();
			m_playtime.reset();

			MoveNextFlow(LetsPlayFlow::CountDown);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Play),
		ButtonCtx(stopbotan, murasaki, U"←", FontButton),
		[this](ButtonBase* self)
		{
			m_playtime.pause();
			m_countdown.pause();
			getData().gameManager().turnOnPause();

			MoveNextFlow(LetsPlayFlow::Pause);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Pause),
		ButtonCtx(pauseRetire, daidai, U"ステージに戻る", FontButton),
		[this](ButtonBase* self)
		{
			getData().reset();
			m_gt = 0;
			m_playtime.reset();
			m_countdown.reset();

			changeScene(SceneSwitch::Stage, 0.0);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Pause),
		ButtonCtx(pauseContinue, daidai, U"つづける", FontButton),
		[this](ButtonBase* self)
		{
			m_playtime.resume();
			m_countdown.resume();
			getData().gameManager().turnOffPause();
			
			MoveNextFlow(LetsPlayFlow::Play);
		});

	makeButton(
		static_cast<ButtonTableKey>(LetsPlayFlow::Pause),
		ButtonCtx(stopbotan, murasaki, U"←", FontButton),
		[this](ButtonBase* self)
		{
			m_playtime.resume();
			m_countdown.resume();
			getData().gameManager().turnOffPause();
			
			MoveNextFlow(LetsPlayFlow::Play);
		});

	initUpdateTable();

	initDrawTable();
}

void LetsPlay::initUpdateTable()
{
	m_updateTable[LetsPlayFlow::ExplainPage1] = [this]()
		{
			AudioAsset(AudioManager::get().getName(BGMID::Explain)).play();

			updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_updateTable[LetsPlayFlow::ExplainPage2] = [this]()
		{
			AudioAsset(AudioManager::get().getName(BGMID::Explain)).play();

			updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_updateTable[LetsPlayFlow::Start] = [this]()
		{
			AudioAsset(AudioManager::get().getName(BGMID::Explain)).stop(FadeTime);

			updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_updateTable[LetsPlayFlow::CountDown] = [this]()
		{
			updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));

			m_t_cd = m_countdown.sF();

			if (4 < m_t_cd)
			{
				m_countdown.reset();
				m_t_cd = 0.0;
				
				// 制限時間の開始.
				m_playtime.restart();

				// 最初の図形の生成.
				getData().gameManager().generateFigure();

				MoveNextFlow(LetsPlayFlow::Play);
			}
		};

	m_updateTable[LetsPlayFlow::Play] = [this]()
		{
			AudioAsset(AudioManager::get().getName(BGMID::LetsPlay)).play();

			updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));

			// 制限時間.
			m_gt = m_playtime.s();

			// 時間切れになったとき.
			if (m_timelimit - m_gt <= 0)
			{
				m_playtime.reset();
				m_gt = 0;

				// ハイスコアを更新したかどうかの記録.
				getData().scoreManager().updateHighScores(getData().gameManager().stageLevel());

				changeScene(SceneSwitch::Result, 0.0);
				return;
			}

			// 分類したか.
			getData().gameManager().update();

			// 分類の判定.
			if (getData().gameManager().isClassified())
			{
				getData().scoreManager().classify(getData().gameManager());
				m_truefalse.restart();

				// 図形の再生成.
				getData().gameManager().generateFigure();
				getData().gameManager().clearClassified();
			}

			int32 t_tf = (m_truefalse.ms() / 30);
			if (getData().scoreManager().isCorrectSorted())
			{
				// 正解したエフェクト.
				effect_TrueOrFalse(t_tf, getData().scoreManager().comboNum(), kuro, FontAsset(U"FontText"), 30);
			}
			else
			{
				// 間違えた時のエフェクト.
				effect_TrueOrFalse(t_tf, getData().scoreManager().comboNum(), kuro, FontAsset(U"FontText"), 30);
			}
			// 時間経過で消す.
			if (t_tf > 20) m_truefalse.reset();
		};

	m_updateTable[LetsPlayFlow::Pause] = [this]()
		{
			updateButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};
}

void LetsPlay::initDrawTable()
{
	m_drawTable[LetsPlayFlow::ExplainPage1] = [this]()
		{
			// ちょっと暗くする.
			makuSize.draw(makuColor);

			// 説明窓.
			explainWindow.drawFrame(haba, kuro).draw(shiro);
			FontAsset(U"FontText")(U"-ルール説明-").draw(30, explainMain, kuro);
			FontAsset(U"FontText")(U"「かたち」は\n図形の形").drawAt(26, explainSubShape, kuro);
			FontAsset(U"FontText")(U"「いろ」は\n図形の色").drawAt(26, explainSubColor, kuro);
			FontAsset(U"FontText")(U"「もじ」は\n図形の文字").drawAt(26, explainSubText, kuro);

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

			FontAsset(U"FontText")((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[0].texts.textChanged : ScoreManager::SortingAnswers[0].texts.textDefault).draw(30, explainTextmaru, kuro);
			FontAsset(U"FontText")((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[1].texts.textChanged : ScoreManager::SortingAnswers[1].texts.textDefault).draw(30, explainTextsankaku, kuro);
			FontAsset(U"FontText")((getData().gameManager().isChangedColor()) ? ScoreManager::SortingAnswers[2].texts.textChanged : ScoreManager::SortingAnswers[2].texts.textDefault).draw(30, explainTextshikaku, kuro);

			drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_drawTable[LetsPlayFlow::ExplainPage2] = [this]()
		{
			// ちょっと暗くする.
			makuSize.draw(makuColor);

			// 説明窓.
			explainWindow.drawFrame(haba, kuro).draw(shiro);
			FontAsset(U"FontText")(U"-操作方法-").draw(30, explainMain, kuro);
			FontAsset(U"FontText")(U"左クリックでつかんで移動!!").drawAt(30, 400, 300, kuro);

			drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_drawTable[LetsPlayFlow::Start] = [this]()
		{
			// ちょっと暗くする.
			makuSize.draw(makuColor);

			// START ボタンがクリックできることを分かりやすく.
			FontAsset(U"FontText")(U"クリックしてスタート").drawAt(16, 400, 340, kuro);

			drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_drawTable[LetsPlayFlow::CountDown] = [this]()
		{
			const double t_cdmaku = Min(m_countdown.sF() / 2, 1.0);

			getData().uiManager().draw(UILayer::SortBoxesLowerside);
			getData().uiManager().draw(UILayer::SortBoxesUpperside);

			// 開幕演出.
			m_boxOutQuad_adu(t_cdmaku, makuSize, makuColor);

			getData().uiManager().draw(UILayer::SortRule);

			if (m_t_cd <= 1)
			{
				FontAsset(U"FontText")(U"3").drawAt(countdownsize, countdownpoint, kuro);

				// ルールの読み忘れを無くす矢印.
				FontAsset(U"FontText")(U"↑").drawAt(50, yondeyoLeft, kuro);
				FontAsset(U"FontText")(U"↑").drawAt(50, yondeyoRight, kuro);
			}
			else if (1 < m_t_cd && m_t_cd <= 2)
			{
				FontAsset(U"FontText")(U"2").drawAt(countdownsize, countdownpoint, kuro);
			}
			else if (2 < m_t_cd && m_t_cd <= 3)
			{
				FontAsset(U"FontText")(U"1").drawAt(countdownsize, countdownpoint, kuro);

				// ルールの読み忘れを無くす矢印.
				FontAsset(U"FontText")(U"↑").drawAt(50, yondeyoLeft, kuro);
				FontAsset(U"FontText")(U"↑").drawAt(50, yondeyoRight, kuro);
			}
			else if (3 < m_t_cd && m_t_cd <= 4)
			{
				FontAsset(U"FontText")(U"START!!").drawAt(countdownsize, countdownpoint, kuro);
			}

			drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_drawTable[LetsPlayFlow::Play] = [this]()
		{
			// 動かす図形.
			getData().uiManager().drawPlayingScene();

			// 制限時間.
			FontAsset(U"FontText")(U"time(s):{}"_fmt(m_timelimit - m_gt)).draw(20, 60, kuro);

			drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};

	m_drawTable[LetsPlayFlow::Pause] = [this]()
		{
			// 一時停止のウィンドウ.
			pauseWindow.drawFrame(haba, kuro).draw(ColorF{ 0.7, 0.7, 0.7, 0.8 });
			FontAsset(U"FontText")(U"--PAUSE--").drawAt(40, (pauseWindow.x + pauseWindow.w / 2), (pauseWindow.y + pauseWindow.h / 3), kuro);

			drawButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
		};
}

void LetsPlay::MoveNextFlow(const LetsPlayFlow next)
{
	m_currentFlow = next;

	enableButtonsAt(static_cast<ButtonTableKey>(m_currentFlow));
}

void LetsPlay::effect_TrueOrFalse(double t, const uint8& comboNum, const ColorF& colorf, const Font& font, const uint8& textsize)
{
	const String combo3 = U"Perfect!!!";
	const String combo2 = U"Great!!";
	const String combo1 = U"Good!";
	const String combo0 = U"Miss";
	constexpr uint16 effect_X = 400;
	constexpr uint16 effect_Y = 570;
	if (comboNum >= 3)
	{
		font(combo3.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else if (comboNum == 2)
	{
		font(combo2.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else if (comboNum == 0)
	{
		font(combo0.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else
	{
		font(combo1.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
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
	AudioAsset(AudioManager::get().getName(BGMID::Result)).play(2.0s);

	updateButtonsAt(static_cast<ButtonTableKey>(ResultFlow::Default));
}

void Result::draw() const
{
	// イージング関数用の時間変数.
	const double t_rw = Min(m_resultwindow.sF(), 1.0);

	// さっきまでの背景たち.
	getData().uiManager().drawPlayingScene();

	// 幕を下ろす.
	getData().uiManager().draw(UILayer::ResultCurtain, t_rw);

	// 結果表示.
	getData().uiManager().draw(UILayer::ResultTexts, t_rw);
	
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
				m_textOutExpo_aap(sortedPtr->rate(), sortedTextAppearPoint, sortedText, kuro, FontAsset(FontButton), U"sorted:{}"_fmt(getData().scoreManager().classifyNum()), 30);
			}
		}

		// 何個仕分けを正しくできたか.
		if (const auto& truePtr = dynamic_cast<ButtonRectMove*>(buttons[1].get()))
		{
			if (truePtr != nullptr)
			{
				m_textOutExpo_aap(truePtr->rate(), trueTextAppearPoint, trueText, kuro, FontAsset(FontButton), U"true:{}"_fmt(getData().scoreManager().correctNum()), 30);
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
				m_textOutExpo_aap(missPtr->rate(), missTextAppearPoint, missText, kuro, FontAsset(FontButton), U"miss:{}"_fmt(getData().scoreManager().missNum()), 30);
			}
			else
			{
				Print << U"Result: 2 番目のボタンは ButtonRectMove ではありません.";
			}
		}
	}

	// ボタンのレイヤーが上.
	drawButtonsAt(static_cast<ButtonTableKey>(ResultFlow::Default));
}

void Result::drawFadeIn(double t) const
{
}

void Result::drawFadeOut(double t) const
{
	AudioAsset(AudioManager::get().getName(BGMID::Result)).stop(FadeTime);

	getData().uiManager().fadeOut(t);
}

void Result::initialize()
{
	Scene::SetBackground(bg_shiro);

	m_resultwindow.restart();

	// 0 番目.
	makeButton(
		static_cast<ButtonTableKey>(ResultFlow::Default),
		ButtonCtx(m_playAgain, kiiro, U"もう一回", FontButton),
		[this](ButtonBase* self)
		{
			getData().retry();
			
			m_resultwindow.reset();
			
			changeScene(SceneSwitch::Letsplay, FadeTime);
		},
		m_playAgainAppearPoint, 1.0, easeOutExpo);

	// 1 番目.
	makeButton(
		static_cast<ButtonTableKey>(ResultFlow::Default),
		ButtonCtx(m_backStage, kiiro, U"ステージへ", FontButton),
		[this](ButtonBase* self)
		{
			getData().reset();
			
			m_resultwindow.reset();
			
			changeScene(SceneSwitch::Stage, FadeTime);
		},
		m_backStageAppearPoint, 1.1, easeOutExpo);

	// 2 番目.
	makeButton(
		static_cast<ButtonTableKey>(ResultFlow::Default),
		ButtonCtx(m_backTitle, murasaki * 1.4, U"タイトルへ", FontButton),
		[this](ButtonBase* self)
		{
			getData().retry();
			
			m_resultwindow.reset();
			
			changeScene(SceneSwitch::Title, FadeTime);
		},
		m_backTitleAppearPoint, 1.2, easeOutExpo);
}

/*	End Result Scene		********************************************************************************************************/
