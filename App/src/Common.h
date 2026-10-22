#pragma once
#include "Enums.h"
#include "Generator.h"
#include "Manager.h"

static const String FontTitle = U"TitleFont";
static const String FontButton = U"FontButton";
inline constexpr StringView FontText = U"FontText";

static constexpr uint8 FrameWidth = 3;	// 図形の枠.

static constexpr RectF GameWindow = { 0, 0, 800, 600 };

static constexpr ColorF CurtainColor = { 0.6, 0.6, 0.6, 0.8 };
static constexpr ColorF BackGroundColor{ U"#fef4f4" };
static constexpr ColorF MainWhite = Palette::White;
static constexpr ColorF MainBlack = Palette::Black;
static constexpr ColorF MainGray{ U"#adadad" };
static constexpr ColorF MainRed{ U"#e2041b" };
static constexpr ColorF MainOrange{ U"#f6ad49" };
static constexpr ColorF MainYellow{ U"#ffd900" };
static constexpr ColorF MainGreen{ U"#38b48b" };
static constexpr ColorF MainBlue{ U"#2ca9e1" };
static constexpr ColorF MainPurple{ U"#9d5b8b" };
static constexpr ColorF ButtonColor = ColorF{ U"#006e54" } * 1.4;

// 色が分かりにくい人用.
// https://scrapbox.io/mandaRa/Okabe-Ito_Scale
static constexpr ColorF ChangedColorOrange{ U"#E69F00" };
static constexpr ColorF ChangedColorBlue{ U"#0072B2" };
static constexpr ColorF ChangedColorBluishgreen{ U"#009E73" };

//static constexpr ColorF shiro{ U"#e8ecef" };
//static constexpr ColorF kuro{ U"#0d0015" };
//static constexpr ColorF kimidori{ U"#c3d825" };
//static constexpr ColorF ai{ U"#4d5aaf" };
//static constexpr ColorF toumei{ 1, 1, 1, 0 };

// 共有するデータ.
class GameData
{
public:
	explicit GameData()
		: m_uiManager(m_gameManager, m_scoreManager)
	{
		initialize();
	}

	~GameData() = default;

	void initialize();
	void reset();
	void retry();

	GameManager& gameManager() { return m_gameManager; }
	ScoreManager& scoreManager() { return m_scoreManager; }
	UIManager& uiManager() { return m_uiManager; }

private:
	GameManager m_gameManager;
	ScoreManager m_scoreManager;
	UIManager m_uiManager;
};

using App = SceneManager<SceneSwitch, GameData>;

// イージング関数.
// 何度か跳ねるやつ.
static constexpr double easeOutBounce(double t)
{
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (t < 1 / d1)
	{
		return n1 * t * t;
	}
	else if (t < 2 / d1)
	{
		return n1 * (t -= 1.5 / d1) * t + 0.75;
	}
	else if (t < 2.5 / d1)
	{
		return n1 * (t -= 2.25 / d1) * t + 0.9375;
	}
	else
	{
		return n1 * (t -= 2.625 / d1) * t + 0.984375;
	}
}
// ぎゅっと最初に動く.
static constexpr double easeOutExpo(double t)
{
	return t == 1 ? 1 : 1 - pow(2, -10 * t);
}
// 大体一定の速度で動く.
static constexpr double easeOutQuad(double t)
{
	return 1 - (1 - t) * (1 - t);
}
