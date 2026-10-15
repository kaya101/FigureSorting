#pragma once

using EnumValue = size_t;

// ゲームシーン.
enum class SceneSwitch : EnumValue
{
	Title,		// タイトル画面.
	Stage,		// ステージ選択.
	Letsplay,	// ゲームプレイ画面.
	Result,		// 結果発表.
};

// ステージレベル.
enum class StageLevel : EnumValue
{
	Level01 = 0,
	Level02 = 1,
	LevelMAX = 2,
	Count = 3		// 要素数.
};

// 仕分けるルール.
enum class SortRule : EnumValue
{
	ShapeRule = 0,
	ColorRule = 1,
	TextRule = 2
};
