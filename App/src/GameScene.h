#pragma once
#include "Common.h"
#include "Button.h"

class GameScene
{
public:

protected:
	Array<std::unique_ptr<ButtonBase>> m_buttonPtrs;

	std::unique_ptr<ButtonBase> makeButton(const ButtonCtx& ctx)
	{
		return std::make_unique<ButtonRect>(ctx);
	}

	std::unique_ptr<ButtonBase> makeButton(const ButtonCtx& ctx, const Vec2& from, const SecondsF delay, const std::function<double(double)> easing)
	{
		return std::make_unique<ButtonRectMove>(ctx, from, delay, easing);
	}
};

class Title
	: public App::Scene
	, public GameScene
{
public:
	explicit Title(const InitData& init);

	~Title() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

private:
	const String m_TitleName = U"仕分けゲーム";
};

class Stage
	: public App::Scene
	, public GameScene
{
public:
	explicit Stage(const InitData& init);

	~Stage() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

private:
	const String m_StageName = U"ステージ選択";

	const Circle m_sampleCircle = { stage01textback.x + stage01textback.w / 2, stage01textback.y - stage01textback.w / 4 - 10 , stage01textback.w / 4 };

	const Triangle m_sampleTriangle = { (double)(stage02textback.x + stage02textback.w / 2), (double)(stage02textback.y - stage02textback.w / 2 + 66) , (double)(stage02textback.w / 2) };

	const Rect m_sampleRect = { Arg::center(stageMAXtextback.x + stageMAXtextback.w / 2, stageMAXtextback.y - stageMAXtextback.w / 2 + 40) , stageMAXtextback.w / 2 };
	
	String m_colorChangeMark = U"";	// 見づらいマーク.
	
	String m_explainSkipMark = U"";	// 説明スキップマーク.
};

class LetsPlay
	: public App::Scene
	, public GameScene
{
public:
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

private:
	const Font text{ FontMethod::SDF, 30, Typeface::Bold };

	double m_t_cd = 0.0;		// カウントダウンの時間.
	
	uint8 m_timelimit = 15;	// 制限時間.
	
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
};

class Result
	: public App::Scene
	, public GameScene
{
public:
	explicit Result(const InitData& init);

	~Result() = default;

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

private:
	Stopwatch m_resultwindow{ StartImmediately::Yes };
};
