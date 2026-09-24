#pragma once
#include "Color.h"

// 使用する色.
static const Array<ColorF> SortingColorsDefault = { aka, midori, ao };
static const Array<ColorF> SortingColorsChanged = { red, yelow, blue };

// 使用する文字.
static const Array<String> SortingTextsDefault = { U"あか", U"みどり", U"あお" };
static const Array<String> SortingTextsChanged = { U"まる", U"さんかく", U"しかく" };

// ゲームシーン.
enum class SceneSwitch
{
	Title,		// タイトル画面.
	Stage,		// ステージ選択.
	Letsplay,	// ゲームプレイ画面.
	Result,		// 結果発表.
};

// 色が見にくいかどうか.
enum class ColorSwitch
{
	Saisyo,			// デフォルト.
	ColorChange,	// 見づらい.
};

// 説明をスキップするかどうか.
enum class ExplainSkip
{
	Saisyo,	// デフォルト.
	Skip,	// スキップする.
};

// 中断するかどうか.
enum class PauseSwitch
{
	BackButton,		// 中断ボタンを押すまで.
	PauseWindow,	// 中断ウィンドウが出てる画面.
};

// カウントダウン画面管理.
enum class CountSwitch
{
	ExplainRule,	// ルールの説明文.
	ExplainSousa,	// 操作方法の説明.
	Start,			// はじめるボタンを押すまで.
	Countdown,		// カウントダウン.
	Break,			// 待機.
};

// 分類ルール.
enum class ScoreSwitch
{
	ShapeRule,	// 形で分ける場合.
	ColorRule,	// 色で分ける場合.
	TextRule,	// 文字で分ける場合.
};

// 図形操作の画面管理.
enum class FigureSwitch
{
	MakeFigure,	// 図形生成.
	Catch,		// 図形を運ぶとき.
	Release,	// つかんだ図形を離したとき.
	Break,		// 待機.
};

// 仕分ける図形.
struct Figure
{
	Vec2 center;		// 図形の中心座標.
	uint8 size;			// 一辺の長さ or 円の半径.
	ColorF color;		// 図形の色.
	String text;		// 書かれた文字.
	uint8 textSize;		// 書かれた文字の大きさ.
	ColorF textcolor;	// 書かれた文字の色.
};

// 共有するデータ.
class GameData
{
public:
	explicit GameData() = default;

	~GameData() = default;

	void initialize()
	{
		m_score = 0;
		m_classifyNum = 0;
		m_correctNum = 0;
		m_missNum = 0;
		m_comboNum = 0;
		m_newRecord = false;
	}

	void addScore(const int16 amount) { m_score += amount; }

	void countClassifyNum() { ++m_classifyNum; }
	void countCorrectNum() { ++m_correctNum; }
	void countMissNum() { ++m_missNum; }
	void countComboNum() { ++m_comboNum; }

	void resetComboNum() { m_comboNum = 0; }

	void setCurrentScene(const SceneSwitch& scene) { m_currentScene = scene; }
	void setColorMode(const ColorSwitch& scene) { m_currentColorMode = scene; }
	void setExplainSkip(const ExplainSkip& skip) { m_currentExplainSkip = skip; }
	void setPauseSwitch(const PauseSwitch& pause) { m_currentPause = pause; }
	void setCountSwitch(const CountSwitch& skip) { m_currentCount = skip; }
	void setScoreSwitch(const ScoreSwitch& skip) { m_currentScoreSwitch = skip; }
	void setFigureSwitch(const FigureSwitch& skip) { m_currentFigureSwitch = skip; }
	void setHighScore(const size_t idx, const int16 score) { m_highScores[idx] = score; }
	void setFcolor(const Array<ColorF>& colors) { m_Fcolor = colors; }
	void setFtext(const Array<String>& texts) { m_Ftext = texts; }
	void setStageNum(const uint8 n) { m_stageNum = n; }
	void setRuleText(const bool skip) { m_ruleText = skip; }
	void setExplainSkip(const bool skip) { m_explainSkip = skip; }
	void setColorChange(const bool skip) { m_colorChange = skip; }
	void setNewRecord(const bool skip) { m_newRecord = skip; }
	void setFigure(const Figure& f) { m_figure = f; }
	void setCircle(const Circle& circle) { m_circle = circle; }
	void setTriangle(const Triangle& t) { m_triangle = t; }
	void setRect(const Rect& r) { m_rect = r; }
	void setColors(const Array<ColorF>& colors) { m_colors = colors; }
	void setTexts(const Array<String>& texts) { m_texts = texts; }

	const SceneSwitch currentScene() const { return m_currentScene; }
	const ColorSwitch currentColorMode() const { return m_currentColorMode; }
	const ExplainSkip currentExplainSkip() const { return m_currentExplainSkip; }
	const PauseSwitch currentPauseSwitch() const { return m_currentPause; }
	const CountSwitch currentCountSwitch() const { return m_currentCount; }
	const ScoreSwitch currentScoreSwitch() const { return m_currentScoreSwitch; }
	const FigureSwitch currentFigureSwitch() const { return m_currentFigureSwitch; }
	const Array<int16>& highScores() const { return m_highScores; }
	const Array<ColorF>& Fcolor() const { return m_Fcolor; }
	const Array<String>& Ftext() const { return m_Ftext; }
	const uint8 stageNum() const { return m_stageNum; }
	const bool ruleText() const { return m_ruleText; }
	const bool explainSkip() const { return m_explainSkip; }
	const bool colorChange() const { return m_colorChange; }
	const bool newRecord() const { return m_newRecord; }
	const int16 score() const { return m_score; }
	const uint8 classifyNum() const { return m_classifyNum; }
	const uint8 correctNum() const { return m_correctNum; }
	const uint8 missNum() const { return m_missNum; }
	const uint8 comboNum() const { return m_comboNum; }
	const Figure& figure() const { return m_figure; }
	const Circle& circle() const { return m_circle; }
	const Triangle& triangle() const { return m_triangle; }
	const Rect& rect() const { return m_rect; }
	const Array<ColorF>& colors() const { return m_colors; }
	const Array<String>& texts() const { return m_texts; }

private:
	SceneSwitch m_currentScene = SceneSwitch::Title;

	ColorSwitch m_currentColorMode = ColorSwitch::Saisyo;

	ExplainSkip m_currentExplainSkip = ExplainSkip::Saisyo;

	PauseSwitch m_currentPause = PauseSwitch::BackButton;

	CountSwitch m_currentCount = CountSwitch::ExplainRule;

	ScoreSwitch m_currentScoreSwitch = ScoreSwitch::ShapeRule;	// 得点計算.

	FigureSwitch m_currentFigureSwitch = FigureSwitch::Break;// 図形操作の画面の信仰.

	Array<int16> m_highScores = { 0, 0, 0 };

	Array<ColorF> m_Fcolor;

	Array<String> m_Ftext;

	uint8 m_stageNum = 0;		// どのステージか.

	bool m_ruleText = false;	// 仕分けルールの表示.

	bool m_explainSkip = false;	// 説明をスキップするかどうか.

	bool m_colorChange = false;	// 色が見づらかったかどうか.

	bool m_newRecord = false;	// 記録を更新したかどうか.

	int16 m_score = 0;

	uint8 m_classifyNum = 0;	// 仕分けた個数.
	
	uint8 m_correctNum = 0;		// 正解した個数.
	
	uint8 m_missNum = 0;		// 間違えた個数.
	
	uint8 m_comboNum = 0;		// 連続正解数をカウント.

	Array<ColorF> m_colors = SortingColorsDefault;

	Array<String> m_texts = SortingTextsDefault;

	// 動かす図形の素材の受け皿.
	Figure m_figure;
	Circle m_circle;
	Triangle m_triangle;
	Rect m_rect;
};

using App = SceneManager<SceneSwitch, GameData>;

//図形出現の中心座標.
constexpr uint16 center_X = 400;
constexpr uint16 center_Y = 470;
constexpr Vec2 center = { center_X, center_Y };
//図形の基本サイズ.
constexpr uint8 size = 120;
//図形の文字の基本サイズ.
constexpr uint8 textSize = 28;

//図形の枠.
constexpr uint8 haba = 3;

//各ステージの番号.
constexpr uint8 STAGE01 = 0;
constexpr uint8 STAGE02 = 1;
constexpr uint8 STAGEMAX = 2;

//よく使う色とか座標.
//はじめるボタン.
constexpr RectF hajimeru = { 250, 350, 300, 80 };
//やめるボタン.
constexpr RectF yameru = { 250, 450, 300, 80 };


// stage01 の説明窓.
constexpr Rect stage01textback = { 50, 260, 220, 300 };
// stage02 の説明窓.
constexpr Rect stage02textback = { 290, 260, 220, 300 };
// stageMAX の説明窓.
constexpr Rect stageMAXtextback = { 530, 260, 220, 300 };
// stage の説明文字の大きさ.
static uint8 stagetextSize = 5 * stage01textback.w / 22;
// stage01 の説明文字の位置.
static Vec2 stage01text = { stage01textback.x + stage01textback.w / 2, stage01textback.y + stagetextSize };
// stage02 の説明文字の位置.
static Vec2 stage02text = { stage02textback.x + stage02textback.w / 2, stage02textback.y + stagetextSize };
// stageMAX の説明文字の位置.
static Vec2 stageMAXtext = { stageMAXtextback.x + stageMAXtextback.w / 2, stageMAXtextback.y + stagetextSize };
// stage のハイスコアとルール内容の文字の大きさ.
static uint8 stagetextsubSize = stage01textback.w / 11;
// stage01 のハイスコアとルール内容の位置.
static Vec2 stage01textsub = { stage01textback.x + 10, stage01textback.y + 5 * stage01textback.w / 22 + 30 };
// stage02 のハイスコアとルール内容の位置.
static Vec2 stage02textsub = { stage02textback.x + 10, stage02textback.y + 5 * stage02textback.w / 22 + 30 };
// stageMAX のハイスコアとルール内容の位置.
static Vec2 stageMAXtextsub = { stageMAXtextback.x + 10, stageMAXtextback.y + 5 * stageMAXtextback.w / 22 + 30 };
// stage01 ボタン.
static Rect stage01botan = { Arg::center(stage01textback.x + stage01textback.w / 2, (int16)(stage01textback.y + 7 * stage01textback.h / 8)), (stage01textback.w - 20), (int16)(8 * stage01textback.h / 45) };
// stage02 ボタン.
static Rect stage02botan = { Arg::center(stage02textback.x + stage02textback.w / 2, (int16)(stage02textback.y + 7 * stage02textback.h / 8)), (stage02textback.w - 20), (int16)(8 * stage02textback.h / 45) };
// stageMAX ボタン.
static Rect stageMAXbotan = { Arg::center(stageMAXtextback.x + stageMAXtextback.w / 2, (int16)(stageMAXtextback.y + 7 * stageMAXtextback.h / 8)), (stageMAXtextback.w - 20), (int16)(8 * stageMAXtextback.h / 45) };
// stage ボタンの文字「これ!!」の大きさ.
static uint8 stagebotantextSize = 2 * stage01botan.w / 11;
//色を変えた印を入れる窓.
constexpr Rect colorchangeBox = { 730, 50, 20, 20 };
//色を変えるかどうかの文字の位置.
static Vec2 colorchangeText = { 658, colorchangeBox.y + colorchangeBox.h/2 };
//説明をスキップした印を入れる窓.
constexpr Rect explainskipBox = { 730, 80, 20, 20 };
//説明を飛ばすかどうかの文字の位置.
static Vec2 explainskipText = { 658, explainskipBox.y + explainskipBox.h/2 };


//仕分けるルールの説明窓.
constexpr Rect explainWindow = { 115, 100, 570, 400 };
//"説明" の位置.
constexpr Vec2 explainMain = { 120, 100 };
//かたちの文字の位置.
constexpr Vec2 explainSubShape = { 210, 200 };
//色の文字の位置.
constexpr Vec2 explainSubColor = { 400, 200 };
//もじの文字の位置.
constexpr Vec2 explainSubText = { 590, 200 };
//区切りの線.
constexpr Vec2 explainLineLeftBegin = { 305, 170 };
constexpr Vec2 explainLineLeftEnd = { 305, 470 };
constexpr Vec2 explainLineRightBegin = { 495, 170 };
constexpr Vec2 explainLineRightEnd = { 495, 470 };
//かたちのまる.
constexpr Circle explainShapeCircle = { 165, 300, 35 };
//かたちのさんかく.
constexpr Triangle explainShapeTriangle = { 240, 360, 70 };
//かたちのしかく.
constexpr Rect explainShapeRect = { 135, 400, 70 };

//色のまる.
constexpr Circle explainColorCircle = { 355, 300, 35 };
//色のさんかく.
constexpr Triangle explainColorTriangle = { 430, 360, 70 };
//色のしかく.
constexpr Rect explainColorRect = { 325, 400, 70 };

//文字の"まる".
constexpr Vec2 explainTextmaru = { 525, 270 };
//文字の"さんかく".
constexpr Vec2 explainTextsankaku = { 560, 340 };
//文字の"しかく".
constexpr Vec2 explainTextshikaku = { 515, 410 };

//右のページに進むボタン.
constexpr Rect explainNextButton = { 690, 275, 50 };
//左のページに戻るボタン.
constexpr Rect explainBackButton = {  60, 275, 50 };
//ルール説明のOKボタン.
constexpr Rect explainOK = { 300, 520, 200, 60 };
//中断ボタン.
constexpr Rect stopbotan = { 690, 60, 60, 60 };
//幕.
constexpr Rect makuSize = { 0, 0, 800, 600 };
//スタートボタン.
constexpr Rect startbotan = { 220, 260, 360, 60 };
//仕分けルールの表示位置.
constexpr Vec2 siwakerule = { 400, 60 };
//仕分けルールの文字の大きさ.
constexpr uint8 siwakesize = 48;
//カウントダウンの表示位置.
constexpr Vec2 countdownpoint = { 400, 300 };
//カウントダウンの文字の大きさ.
constexpr uint8 countdownsize = 40;
//ルールの読み忘れ帽子.
constexpr Vec2 yondeyoLeft = { 280, 120 };
constexpr Vec2 yondeyoRight = { 520, 120 };
//一時中止のウィンドウ.
constexpr Rect pauseWindow = { 200, 130, 400, 240 };
//やめてステージに戻るボタン.
constexpr Rect pauseRetire = { 230, 290, 160, 50 };
//再開するボタン.
constexpr Rect pauseContinue = { 404, 290, 160, 50 };
//見えない壁の当たり判定.
//仕分けてるとき.
static Array<uint16> wallx = { 50, 750 };
static Array<uint16> wally = { 130, 530 };

//分類箱の位置.
constexpr uint8 left = 0;
constexpr uint8 mdle = 1;
constexpr uint8 rght = 2;
//分類箱の下側.
constexpr Rect ubox_left = {  50, 390, 160, 140 };
constexpr Rect ubox_mdle = { 320, 110, 160, 140 };
constexpr Rect ubox_rght = { 590, 390, 160, 140 };
//分類箱の上側.
constexpr Rect obox_left = {  50, 410, 160, 120 };
constexpr Rect obox_mdle = { 320, 130, 160, 120 };
constexpr Rect obox_rght = { 590, 410, 160, 120 };
// Result テキスト.
constexpr Vec2 resultText = { 400, 100 };
// Your Score.
constexpr Vec2 yourscoreText = { 400, 200 };
// High Score.
constexpr Vec2 highscoreText = { 120, 205 };
// newrecord.
constexpr Vec2 newrecordText = { 120, 230 };
// sorted.
constexpr Vec2 sortedText = { 60, 380 };
// true.
constexpr Vec2 trueText{ 60, 440 };
// miss.
constexpr Vec2 missText = { 60, 500 };
//もう一度.
constexpr Rect onemore = { 400, 340, 360, 60 };
//ステージに戻る.
constexpr Rect backstage = { 400, 410, 360, 60};
//タイトルに戻る.
constexpr Rect backtitle = { 400, 480, 360, 60 };
//結果画面の飛び出すボタンの出現位置.
static Vec2 resultTextAppearPoint = { resultText.x - 800, resultText.y };
static Vec2 yourscoreTextAppearPoint = { yourscoreText.x - 800, yourscoreText.y };
static Vec2 sortedTextAppearPoint = { sortedText.x - 800, sortedText.y };
static Vec2 trueTextAppearPoint = { trueText.x - 800, trueText.y };
static Vec2 missTextAppearPoint = { missText.x - 800, missText.y };
static Vec2 onemoreAppearPoint = { onemore.x + 800, onemore.y };
static Vec2 backstageAppearPoint = { backstage.x + 800, backstage.y };
static Vec2 backtitleAppearPoint = { backtitle.x + 800, backtitle.y };


//各難易度ごとに何が何種類あるのか.
constexpr uint8 COLOR01 = 1;
constexpr uint8 TEXT01 = 1;

constexpr uint8 COLOR02 = 3;
constexpr uint8 TEXT02 = 1;

constexpr uint8 COLORMAX = 3;
constexpr uint8 TEXTMAX = 3;

//配列にしまう.
static Array<ColorF> color_Lv01 = {
	midori,
	midori,
	midori,
};
static Array<String> text_Lv01 = {
	U"", //文字無し.
	U"", //文字無し.
	U"", //文字無し.
};

static Array<ColorF> color_Lv02 = {
	aka,
	midori,
	ao
};
static Array<String> text_Lv02 = {
	U"", //文字無し.
	U"", //文字無し.
	U"", //文字無し.
};

static Array<ColorF> color_LvMAX = {
	aka,
	midori,
	ao,
};
static Array<String> text_LvMAX = {
	U"あか",
	U"みどり",
	U"あお",
};
//色を変えた時の配列.
static Array<ColorF> colorchangecolor_Lv01 = {
	yelow,
	yelow,
	yelow,
};
static Array<ColorF> colorchangecolor_Lv02 = {
	red,
	yelow,
	blue,
};
static Array<ColorF> colorchangecolor_LvMAX = {
	red,
	yelow,
	blue,
};
static Array<String> colorchangetext = {
	U"まる",
	U"さんかく",
	U"しかく",
};

//加点.
constexpr uint8 plus = 0;
//減点.
constexpr uint8 minus = 1;
static Array<Array<int16>> Score = {
	{ 100, -50 }, // Lv.01.
	{ 250, -300 }, // Lv.02.
	{ 500, -1000 }, // Lv.MAX.
};

//それぞれ何種類ずつあるのかの配列.
constexpr uint8 COLOR = 0;
constexpr uint8 TEXT = 1;
static Array<Array<uint8>> kinds = {
	{ COLOR01, TEXT01 }, // Lv.01.
	{ COLOR02, TEXT02 }, // Lv.02.
	{ COLORMAX, TEXTMAX } // Lv.MAX.
};

static Array<Array<ColorF>> color = {
	{ color_Lv01 },
	{ color_Lv02 },
	{ color_LvMAX }
};
static Array<Array<String>> teXt = {
	{ text_Lv01 },
	{ text_Lv02 },
	{ text_LvMAX }
};
//色を変えたとき.
static Array<Array<ColorF>> colorchangecolor = {
	{ colorchangecolor_Lv01 }, // Lv.01.
	{ colorchangecolor_Lv02 }, // Lv.02.
	{ colorchangecolor_LvMAX } // Lv.MAX.
};
