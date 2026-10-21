#pragma once
#include "Enums.h"
#include "Generator.h"
#include "Manager.h"

static const String FontTitle = U"TitleFont";
static const String FontButton = U"FontButton";
inline constexpr StringView FontText = U"FontText";

// 背景の白.
static constexpr ColorF bg_shiro{ U"#fef4f4" };

// 白と黒.
static constexpr ColorF shiro{ U"#e8ecef" };
static constexpr ColorF kuro{ U"#0d0015" };

// ボタンの色.
static constexpr ColorF botan{ U"#006e54" };

// グレー.
static constexpr ColorF haiiro{ U"#adadad" };

// 黄緑.
static constexpr ColorF kimidori{ U"#c3d825" };

// 基本七色 of 私.
static constexpr ColorF aka{ U"#e2041b" };
static constexpr ColorF daidai{ U"#f6ad49" };
static constexpr ColorF kiiro{ U"#ffd900" };
static constexpr ColorF midori{ U"#38b48b" };
static constexpr ColorF ao{ U"#2ca9e1" };
static constexpr ColorF ai{ U"#4d5aaf" };
static constexpr ColorF murasaki{ U"#9d5b8b" };

// 色が分かりにくい人用.
static constexpr ColorF red{ U"#ff4b00" };
static constexpr ColorF yelow{ U"#fff100" };
static constexpr ColorF blue{ U"#4dc4ff" };

// 幕の透ける灰色.
static constexpr ColorF makuColor = { 0.6, 0.6, 0.6, 0.8 };

// 背景が透ける透明.
static constexpr ColorF toumei{ 1, 1, 1, 0 };

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

//幕.
static constexpr RectF makuSize = { 0, 0, 800, 600 };

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

// 分類箱.
static constexpr uint8 haba = 3;	// 図形の枠.
