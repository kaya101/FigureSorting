#pragma once
#include "Common.h"
#include "Button.h"

class GameScene
{
public:
	using ButtonWorkCallBack = std::function<void(ButtonBase* self)>;

	using ButtonTableKey = int16;

	void virtual drawUI() const = 0;

	void virtual initialize() = 0;

protected:
	//Array<std::unique_ptr<ButtonBase>> m_buttonPtrs;
	HashTable<ButtonTableKey, Array<std::unique_ptr<ButtonBase>>> m_buttonTable;

	void makeButton(const ButtonTableKey key, const ButtonCtx& ctx, ButtonWorkCallBack workCallBack);

	void makeButton(const ButtonTableKey key, const ButtonCtx& ctx, ButtonWorkCallBack workCallBack, const Vec2& from, const double delay, ButtonRectMove::Easing easing);

	void updateButtonsAt(const ButtonTableKey key);

	void drawButtonsAt(const ButtonTableKey key) const;

	void enableButtonsAt(const ButtonTableKey key);
};

class Title
	: public App::Scene
	, public GameScene
{
public:
	enum class TitleFlow : ButtonTableKey
	{
		Default,
	};

	explicit Title(const InitData& init);

	~Title() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	void drawUI() const override;

	void initialize() override;

private:
	static constexpr RectF m_gameStart = { 250, 350, 300, 80 };

	static constexpr RectF m_quitGame = { 250, 450, 300, 80 };

	const String m_TitleName = U"仕分けゲーム";
};

class Stage
	: public App::Scene
	, public GameScene
{
public:
	enum class StageFlow : ButtonTableKey
	{
		Default,
	};

	explicit Stage(const InitData& init);

	~Stage() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	void drawUI() const override;

	void initialize() override;

private:
	static constexpr RectF stage01textback = { 50, 260, 220, 300 };
	
	static constexpr RectF stage02textback = { 290, 260, 220, 300 };
	
	static constexpr RectF stageMAXtextback = { 530, 260, 220, 300 };
	
	static constexpr uint8 stagetextSize = 5 * stage01textback.size.x / 22;

	//static constexpr Vec2 stage01text = { stage01textback.pos.x + stage01textback.w / 2, stage01textback.y + stagetextSize };
	static constexpr Vec2 stage01text = stage01textback.pos + Vec2(stage01textback.size.x * 0.5, stagetextSize);
	
	//static constexpr Vec2 stage02text = { stage02textback.pos.x + stage02textback.w / 2, stage02textback.y + stagetextSize };
	static constexpr Vec2 stage02text = stage02textback.pos + Vec2(stage02textback.size.x * 0.5, stagetextSize);
	
	//static constexpr Vec2 stageMAXtext = { stageMAXtextback.pos.x + stageMAXtextback.w / 2, stageMAXtextback.y + stagetextSize };
	static constexpr Vec2 stageMAXtext = stageMAXtextback.pos + Vec2(stageMAXtextback.size.x * 0.5, stagetextSize);
	
	static constexpr uint8 stagetextsubSize = stage01textback.size.x / 11;
	
	//static constexpr Vec2 stage01textsub = { stage01textback.x + 10, stage01textback.y + 5 * stage01textback.w / 22 + 30 };
	static constexpr Vec2 stage01textsub = stage01textback.pos + Vec2(10, 5 * stage01textback.size.x / 22 + 30);
	
	//static constexpr Vec2 stage02textsub = { stage02textback.x + 10, stage02textback.y + 5 * stage02textback.w / 22 + 30 };
	static constexpr Vec2 stage02textsub = stage02textback.pos + Vec2(10, 5 * stage02textback.size.x / 22 + 30);
	
	//static constexpr Vec2 stageMAXtextsub = { stageMAXtextback.x + 10, stageMAXtextback.y + 5 * stageMAXtextback.w / 22 + 30 };
	static constexpr Vec2 stageMAXtextsub = stageMAXtextback.pos + Vec2(10, 5 * stageMAXtextback.size.x / 22 + 30);
	
	static constexpr RectF stage01botan = { Arg::center(stage01textback.pos.x + stage01textback.size.x / 2, (int16)(stage01textback.pos.y + 7 * stage01textback.size.y / 8)), (stage01textback.size.x - 20), (int16)(8 * stage01textback.size.y / 45) };
	
	static constexpr RectF stage02botan = { Arg::center(stage02textback.pos.x + stage02textback.size.x / 2, (int16)(stage02textback.pos.y + 7 * stage02textback.size.y / 8)), (stage02textback.size.x - 20), (int16)(8 * stage02textback.size.y / 45) };
	
	static constexpr RectF stageMAXbotan = { Arg::center(stageMAXtextback.pos.x + stageMAXtextback.size.x / 2, (int16)(stageMAXtextback.pos.y + 7 * stageMAXtextback.size.y / 8)), (stageMAXtextback.size.x - 20), (int16)(8 * stageMAXtextback.size.y / 45) };
	
	static constexpr uint8 stagebotantextSize = 2 * stage01botan.size.x / 11;
	
	static constexpr RectF colorchangeBox = { 730, 50, 20, 20 };
	
	static constexpr Vec2 colorchangeText = { 658, colorchangeBox.pos.y + colorchangeBox.size.y / 2 };
	
	static constexpr RectF explainskipBox = { 730, 80, 20, 20 };

	static constexpr Vec2 explainskipText = { 658, explainskipBox.pos.y + explainskipBox.size.y / 2 };

	const String m_StageName = U"ステージ選択";

	const Circle m_sampleCircle = { stage01textback.x + stage01textback.w / 2, stage01textback.y - stage01textback.w / 4 - 10 , stage01textback.w / 4 };

	const Triangle m_sampleTriangle = { (double)(stage02textback.x + stage02textback.w / 2), (double)(stage02textback.y - stage02textback.w / 2 + 66) , (double)(stage02textback.w / 2) };

	const RectF m_sampleRect = { Arg::center(stageMAXtextback.x + stageMAXtextback.w / 2, stageMAXtextback.y - stageMAXtextback.w / 2 + 40) , stageMAXtextback.w / 2 };
	
	const String m_markedText = U"〆";
};

class LetsPlay
	: public App::Scene
	, public GameScene
{
public:
	enum class LetsPlayFlow : ButtonTableKey
	{
		Default,
		Explain,	// ルール/操作方法の説明.
		Start,		// はじめるボタンを押すまで.
		Pause,		// 中断ウィンドウが出てる画面.
	};

	// 正誤判定.
	enum class TrueOrFalse
	{
		WaitSort,	// 仕分け待ち.
		TrueSort,	// 正解したとき.
		FalseSort,	// 間違えたとき.
	};

	explicit LetsPlay(const InitData& init);

	~LetsPlay() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	void drawUI() const override;

	void initialize() override;

private:
	// 図形出現の中心座標.
	static constexpr uint16 center_X = 400;
	static constexpr uint16 center_Y = 470;
	static constexpr Vec2 center = { center_X, center_Y };

	// 図形の基本サイズ.
	static constexpr uint8 size = 120;

	// 図形の文字の基本サイズ.
	static constexpr uint8 textSize = 28;

	// 仕分けるルールの説明窓.
	static constexpr Rect explainWindow = { 115, 100, 570, 400 };

	// "説明" の位置.
	static constexpr Vec2 explainMain = { 120, 100 };

	// かたちの文字の位置.
	static constexpr Vec2 explainSubShape = { 210, 200 };

	// 色の文字の位置.
	static constexpr Vec2 explainSubColor = { 400, 200 };

	// もじの文字の位置.
	static constexpr Vec2 explainSubText = { 590, 200 };

	// 区切りの線.
	static constexpr Vec2 explainLineLeftBegin = { 305, 170 };
	static constexpr Vec2 explainLineLeftEnd = { 305, 470 };
	static constexpr Vec2 explainLineRightBegin = { 495, 170 };
	static constexpr Vec2 explainLineRightEnd = { 495, 470 };

	// かたちのまる.
	static constexpr Circle explainShapeCircle = { 165, 300, 35 };

	// かたちのさんかく.
	static constexpr Triangle explainShapeTriangle = { 240, 360, 70 };

	// かたちのしかく.
	static constexpr Rect explainShapeRect = { 135, 400, 70 };

	// 色のまる.
	static constexpr Circle explainColorCircle = { 355, 300, 35 };

	// 色のさんかく.
	static constexpr Triangle explainColorTriangle = { 430, 360, 70 };

	// 色のしかく.
	static constexpr Rect explainColorRect = { 325, 400, 70 };

	// 文字の"まる".
	static constexpr Vec2 explainTextmaru = { 525, 270 };
	// 文字の"さんかく".
	static constexpr Vec2 explainTextsankaku = { 560, 340 };
	// 文字の"しかく".
	static constexpr Vec2 explainTextshikaku = { 515, 410 };

	// 右のページに進むボタン.
	static constexpr Rect explainNextButton = { 690, 275, 50 };
	// 左のページに戻るボタン.
	static constexpr Rect explainBackButton = { 60, 275, 50 };
	// ルール説明のOKボタン.
	static constexpr Rect explainOK = { 300, 520, 200, 60 };
	// 中断ボタン.
	static constexpr Rect stopbotan = { 690, 60, 60, 60 };

	// 加点.
	static constexpr uint8 plus = 0;
	// 減点.
	static constexpr uint8 minus = 1;
	const Array<Array<int16>> Score = {
		{ 100, -50 }, // Lv.01.
		{ 250, -300 }, // Lv.02.
		{ 500, -1000 }, // Lv.MAX.
	};

	// スタートボタン.
	static constexpr Rect startbotan = { 220, 260, 360, 60 };
	// 仕分けルールの表示位置.
	static constexpr Vec2 siwakerule = { 400, 60 };
	// 仕分けルールの文字の大きさ.
	static constexpr uint8 siwakesize = 48;
	// カウントダウンの表示位置.
	static constexpr Vec2 countdownpoint = { 400, 300 };
	// カウントダウンの文字の大きさ.
	static constexpr uint8 countdownsize = 40;
	// ルールの読み忘れ帽子.
	static constexpr Vec2 yondeyoLeft = { 280, 120 };
	static constexpr Vec2 yondeyoRight = { 520, 120 };
	// 一時中止のウィンドウ.
	static constexpr Rect pauseWindow = { 200, 130, 400, 240 };
	// やめてステージに戻るボタン.
	static constexpr Rect pauseRetire = { 230, 290, 160, 50 };
	// 再開するボタン.
	static constexpr Rect pauseContinue = { 404, 290, 160, 50 };

	// 見えない壁の当たり判定.
	// 仕分けてるとき.
	const Array<uint16> wallx = { 50, 750 };
	const Array<uint16> wally = { 130, 530 };

	const Font text{ FontMethod::SDF, 30, Typeface::Bold };

	double m_t_cd = 0.0;		// カウントダウンの時間.
	
	//uint8 m_timelimit = 15;	// 制限時間.
	uint8 m_timelimit = 3;	// 制限時間.
	
	uint8 m_gt = 0;			// 制限時間のカウントダウン時間.

	bool m_pause = false;

	TrueOrFalse m_tof = TrueOrFalse::WaitSort;	// 正誤判定.

	Stopwatch m_countdown{ StartImmediately::Yes };	// ゲーム開始のカウントダウン.
	
	Stopwatch m_playtime{ StartImmediately::No };		// 制限時間.
	
	Stopwatch m_truefalse{ StartImmediately::Yes };	// 正誤判定のエフェクト.

	// 動かす図形の素材の受け皿.
	Figure figure;
	
	Circle circle{};
	
	Triangle triangle{};
	
	Rect rect{};

	// 図形を持ち運ぶときの図形の中心とカーソルの距離を保持する.
	int16 m_distance_x = 0;
	int16 m_distance_y = 0;

	LetsPlayFlow m_currentFlow = LetsPlayFlow::Default;

	// 図形の色を決める関数.
	void decide_color(Figure& figure, const uint8& stageNum, const bool& colorchange) const
	{
		// そのステージで使える色は何種類あるうちのどれか.
		uint8 num = randInt() % kinds[stageNum][COLOR];

		// 色を変更しているとき.
		if (colorchange) {
			figure.color = colorchangecolor[stageNum][num];
		}
		// 最初の状態のまま.
		else {
			figure.color = color[stageNum][num];
		}
	}

	// 図形の文字を決める関数.
	void decide_text(Figure& figure, const uint8& stageNum, const bool& colorchange) const
	{
		// そのステージで使える文字は何種類あるうちのどれか.
		uint8 num = randInt() % kinds[stageNum][TEXT];

		// 色を変更しているとき.
		if (colorchange && stageNum == STAGEMAX) {
			figure.text = colorchangetext[num];
		}
		// 最初のまま.
		else {
			figure.text = teXt[stageNum][num];
		}
	}

	// 中心座標から四角の左上座標を求める関数.
	const int16 culc_lx(const Figure& figure) const { return figure.center.x - (figure.size / 2); }
	const int16 culc_ly(const Figure& figure) const { return figure.center.y - (figure.size / 2); }

	// 正三角形の 3 頂点から辺の長さを求める関数.
	// 実際は 2 点で足りるけど.
	const double culc_Length(const Triangle& triangle) const { return sqrt(pow(triangle.p1.x - triangle.p0.x, 2) + pow(triangle.p1.y - triangle.p0.y, 2)); }

	// 任意の座標成分より,図形の中心がはみ出ないようにする関数.
	const double check_wallx(const Array<uint16>& wall, const int16& point_x, const Figure& figure) const
	{
		if (point_x - figure.size / 2 <= wall[0]) {
			return wall[0] + figure.size / 2;
		}
		else if (wall[1] <= point_x + figure.size / 2) {
			return wall[1] - figure.size / 2;
		}
		else {
			return point_x;
		}
	}
	const double check_wally(const Array<uint16>& wall, const int16& point_y, const Figure& figure) const
	{
		if (point_y - figure.size / 2 <= wall[0]) {
			return wall[0] + figure.size / 2;
		}
		else if (wall[1] <= point_y + figure.size / 2) {
			return wall[1] - figure.size / 2;
		}
		else {
			return point_y;
		}
	}

	// ゲーム結果画面の幕が上がるやつ.
	void m_boxOutQuad_adu(const double t, const Rect& rect, const ColorF& colorf) const
	{
		RectF{ rect.x, rect.y, rect.w, rect.h * (1 - easeOutQuad(t)) }.draw(colorf);
	}

	// 正誤判定のエフェクト.
	void effect_TrueOrFalse(double t, const uint8& comboNum, const ColorF& colorf, const Font& font, const uint8& textsize);
};

class Result
	: public App::Scene
	, public GameScene
{
public:
	enum class ResultFlow : ButtonTableKey
	{
		Default,
	};

	explicit Result(const InitData& init);

	~Result() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	void drawUI() const override;

	void initialize() override;

private:
	static constexpr RectF m_playAgain = { 400, 340, 360, 60 };
	
	static constexpr RectF m_backStage = { 400, 410, 360, 60 };
	
	static constexpr RectF m_backTitle = { 400, 480, 360, 60 };

	static constexpr Vec2 m_playAgainAppearPoint = m_playAgain.pos + Vec2(800, 0);
	static constexpr Vec2 m_backStageAppearPoint = m_backStage.pos + Vec2(800, 0);
	static constexpr Vec2 m_backTitleAppearPoint = m_backTitle.pos + Vec2(800, 0);

	static constexpr Vec2 resultText = { 400, 100 };
	
	static constexpr Vec2 yourscoreText = { 400, 200 };
	
	static constexpr Vec2 highscoreText = { 120, 205 };
	
	static constexpr Vec2 newrecordText = { 120, 230 };
	
	static constexpr Vec2 sortedText = { 60, 380 };
	
	static constexpr Vec2 trueText{ 60, 440 };
	
	static constexpr Vec2 missText = { 60, 500 };

	// 結果画面の飛び出すボタンの出現位置.
	static constexpr Vec2 resultTextAppearPoint = resultText - Vec2(800, 0);
	static constexpr Vec2 yourscoreTextAppearPoint = yourscoreText - Vec2(800, 0);
	static constexpr Vec2 sortedTextAppearPoint = sortedText - Vec2(800, 0);
	static constexpr Vec2 trueTextAppearPoint = trueText - Vec2(800, 0);
	static constexpr Vec2 missTextAppearPoint = missText - Vec2(800, 0);

	Stopwatch m_resultwindow{ StartImmediately::Yes };

	// ゲーム結果画面の幕が下りるやつ.
	void m_boxBounce_aud(const double t, const Rect& rect, const ColorF& colorf) const
	{
		RectF{ rect.x, rect.y, rect.w, rect.h * easeOutBounce(t) }.draw(colorf);
	}
	void m_textBounce_aud(const double t, const Vec2& vec2, const Font& font, const String& text, const uint8& size) const
	{
		font(text).drawAt(size, vec2.x, vec2.y * easeOutBounce(t), kuro);
	}

	// 結果画面でテキストが任意の座標から出てくるやつ.
	void m_textOutExpo_aap(double t, const Vec2& from, const Vec2& vec2, const ColorF& colorf, const Font& font, const String& text, const uint8& size) const
	{
		// 左上座標準拠.
		font(text).draw(size, from.x + easeOutExpo(t) * (vec2.x - from.x), from.y + easeOutExpo(t) * (vec2.y - from.y), colorf);
	}
};
