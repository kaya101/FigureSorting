#pragma once

static const String FontTitle = U"TitleFont";
static const String FontButton = U"FontButton";

// 背景の白.
constexpr ColorF bg_shiro{ U"#fef4f4" };

// 白と黒.
constexpr ColorF shiro{ U"#e8ecef" };
constexpr ColorF kuro{ U"#0d0015" };

// ボタンの色.
constexpr ColorF botan{ U"#006e54" };

// グレー.
constexpr ColorF haiiro{ U"#adadad" };

// 黄緑.
constexpr ColorF kimidori{ U"#c3d825" };

// 基本七色 of 私.
constexpr ColorF aka{ U"#e2041b" };
constexpr ColorF daidai{ U"#f6ad49" };
constexpr ColorF kiiro{ U"#ffd900" };
constexpr ColorF midori{ U"#38b48b" };
constexpr ColorF ao{ U"#2ca9e1" };
constexpr ColorF ai{ U"#4d5aaf" };
constexpr ColorF murasaki{ U"#9d5b8b" };

// 色が分かりにくい人用.
constexpr ColorF red{ U"#ff4b00" };
constexpr ColorF yelow{ U"#fff100" };
constexpr ColorF blue{ U"#4dc4ff" };

// 幕の透ける灰色.
constexpr ColorF makuColor = { 0.6, 0.6, 0.6, 0.8 };

// 背景が透ける透明.
constexpr ColorF toumei{ 1, 1, 1, 0 };

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

	void turnOnChangedColor() { m_isChangedColor = true; }
	void turnOffChangedColor() { m_isChangedColor = false; }

	void turnOnSkippedExplain() { m_isSkippedExplain = true; }
	void turnOffSkippedExplain() { m_isSkippedExplain = false; }

	void setPauseSwitch(const PauseSwitch& pause) { m_currentPause = pause; }
	void setCountSwitch(const CountSwitch& skip) { m_currentCount = skip; }
	void setScoreSwitch(const ScoreSwitch& skip) { m_currentScoreSwitch = skip; }
	void setFigureSwitch(const FigureSwitch& skip) { m_currentFigureSwitch = skip; }
	void setHighScore(const size_t idx, const int16 score) { m_highScores[idx] = score; }
	void setFcolor(const Array<ColorF>& colors) { m_Fcolor = colors; }
	void setFtext(const Array<String>& texts) { m_Ftext = texts; }
	void setStageNum(const uint8 n) { m_stageNum = n; }
	void setRuleText(const bool skip) { m_ruleText = skip; }
	void setNewRecord(const bool skip) { m_newRecord = skip; }
	void setColors(const Array<ColorF>& colors) { m_colors = colors; }
	void setTexts(const Array<String>& texts) { m_texts = texts; }

	const bool isChangedColor() const { return m_isChangedColor; }
	const bool isSkippedExplain() const { return m_isSkippedExplain; }
	const PauseSwitch currentPauseSwitch() const { return m_currentPause; }
	const CountSwitch currentCountSwitch() const { return m_currentCount; }
	const ScoreSwitch currentScoreSwitch() const { return m_currentScoreSwitch; }
	const FigureSwitch currentFigureSwitch() const { return m_currentFigureSwitch; }
	const Array<int16>& highScores() const { return m_highScores; }
	const Array<ColorF>& Fcolor() const { return m_Fcolor; }
	const Array<String>& Ftext() const { return m_Ftext; }
	const uint8 stageNum() const { return m_stageNum; }
	const bool ruleText() const { return m_ruleText; }
	const bool newRecord() const { return m_newRecord; }
	const int16 score() const { return m_score; }
	const uint8 classifyNum() const { return m_classifyNum; }
	const uint8 correctNum() const { return m_correctNum; }
	const uint8 missNum() const { return m_missNum; }
	const uint8 comboNum() const { return m_comboNum; }
	const Array<ColorF>& colors() const { return m_colors; }
	const Array<String>& texts() const { return m_texts; }

private:
	bool m_isChangedColor = false;		// 色が見にくいかどうか.

	bool m_isSkippedExplain = false;	// 説明をスキップするかどうか.

	PauseSwitch m_currentPause = PauseSwitch::BackButton;

	CountSwitch m_currentCount = CountSwitch::ExplainRule;

	ScoreSwitch m_currentScoreSwitch = ScoreSwitch::ShapeRule;	// 得点計算.

	FigureSwitch m_currentFigureSwitch = FigureSwitch::Break;// 図形操作の画面の信仰.

	Array<int16> m_highScores = { 0, 0, 0 };

	Array<ColorF> m_Fcolor;

	Array<String> m_Ftext;

	uint8 m_stageNum = 0;		// どのステージか.

	bool m_ruleText = false;	// 仕分けルールの表示.

	bool m_newRecord = false;	// 記録を更新したかどうか.

	int16 m_score = 0;

	uint8 m_classifyNum = 0;	// 仕分けた個数.
	
	uint8 m_correctNum = 0;		// 正解した個数.
	
	uint8 m_missNum = 0;		// 間違えた個数.
	
	uint8 m_comboNum = 0;		// 連続正解数をカウント.

	Array<ColorF> m_colors = SortingColorsDefault;

	Array<String> m_texts = SortingTextsDefault;
};

using App = SceneManager<SceneSwitch, GameData>;

//各ステージの番号.
constexpr uint8 STAGE01 = 0;
constexpr uint8 STAGE02 = 1;
constexpr uint8 STAGEMAX = 2;




//幕.
constexpr Rect makuSize = { 0, 0, 800, 600 };


// 分類箱の位置.
static constexpr uint8 left = 0;
static constexpr uint8 mdle = 1;
static constexpr uint8 rght = 2;
// 分類箱の下側.
static constexpr Rect ubox_left = { 50, 390, 160, 140 };
static constexpr Rect ubox_mdle = { 320, 110, 160, 140 };
static constexpr Rect ubox_rght = { 590, 390, 160, 140 };
// 分類箱の上側.
static constexpr Rect obox_left = { 50, 410, 160, 120 };
static constexpr Rect obox_mdle = { 320, 130, 160, 120 };
static constexpr Rect obox_rght = { 590, 410, 160, 120 };


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

//お気に入りの乱数生成.
static unsigned int randInt() {
	static unsigned int tx = 123456789, ty = 362436069, tz = 521288629, tw = 88675123;
	unsigned int tt = (tx ^ (tx << 11));
	tx = ty; ty = tz; tz = tw;
	return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
}
//リンク「https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#9-xorshift」.



//イージング.
//何度か跳ねるやつ.
static double easeOutBounce(double t) {
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (t < 1 / d1) {
		return n1 * t * t;
	}
	else if (t < 2 / d1) {
		return n1 * (t -= 1.5 / d1) * t + 0.75;
	}
	else if (t < 2.5 / d1) {
		return n1 * (t -= 2.25 / d1) * t + 0.9375;
	}
	else {
		return n1 * (t -= 2.625 / d1) * t + 0.984375;
	}
}
//ぎゅっと最初に動く.
static double easeOutExpo(double t) {
	return t == 1 ? 1 : 1 - pow(2, -10 * t);
}
//大体一定の速度で動く.
static double easeOutQuad(double t) {
	return 1 - (1 - t) * (1 - t);
}

//左上頂点表示を変換して利用するタイプ.
//四角の中心座標( x, y )を求める関数.
//static double culc_x(const RectF& rectf) {
//	return rectf.x + (rectf.w / 2);
//}
//static double culc_y(const RectF& rectf) {
//	return rectf.y + (rectf.h / 2);
//}

// 分類箱.
static constexpr uint8 haba = 3;	// 図形の枠.
static void box_under(const Rect& box, const ColorF& colorf)
{
	box.draw(colorf * 0.8);
	box.drawFrame(haba, kuro);
}
static void box_over(const Rect& box, const ColorF& colorf, const Font& font, const String& string)
{
	box.draw(colorf);
	box.drawFrame(haba, kuro);
	font(U"{}"_fmt(string)).drawAt((box.x + box.w / 2), (box.y + box.h / 2), kuro);
}

//それのボタンバージョン, 当たり判定付き.
//static bool m_buttonOutExpo_aap(double t, const Vec2& vec2, const RectF& rectf, const ColorF& colorf, const Font& font, const String& text, const uint8& size, const ColorF& framecolor) {
//
//	if (rectf.mouseOver()) {
//		Cursor::RequestStyle(CursorStyle::Hand);
//		//長押し判定.
//		if (MouseL.pressed()) {
//			//左上座標準拠.
//			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.draw(colorf * 0.8 * 0.8);
//			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.drawFrame(haba, framecolor);
//			font(text).drawAt(size, (vec2.x + easeOutExpo(t) * (rectf.x - vec2.x) + rectf.w / 2), (vec2.y + easeOutExpo(t) * (rectf.y - vec2.y) + rectf.h / 2));
//		}
//		else {
//			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.draw(colorf * 0.8);
//			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.drawFrame(haba, framecolor);
//			font(text).drawAt(size, (vec2.x + easeOutExpo(t) * (rectf.x - vec2.x) + rectf.w / 2), (vec2.y + easeOutExpo(t) * (rectf.y - vec2.y) + rectf.h / 2));
//		}
//	}
//	else {
//		RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.draw(colorf);
//		RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.drawFrame(haba, framecolor);
//		font(text).drawAt(size, (vec2.x + easeOutExpo(t) * (rectf.x - vec2.x) + rectf.w / 2), (vec2.y + easeOutExpo(t) * (rectf.y - vec2.y) + rectf.h / 2));
//	}
//	return t >= 1 && rectf.mouseOver() && MouseL.up();
//}
