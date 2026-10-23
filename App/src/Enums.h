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
	TextRule = 2,
	Count = 3
};

// 仕分ける図形の種類.
enum class SortingShapeType : EnumValue
{
	Cricle = 0,
	Square = 1,
	Triangle = 2,
	Count = 3
};

enum class SortingBoxIdx : EnumValue
{
	Left = 0,
	Midle = 1,
	Right = 2,
	Count = 3
};

enum class SortingBoxLayerIdx : EnumValue
{
	Upperside = 0,
	Lowerside = 1,
	Count = 2
};

enum class ScoreChange : EnumValue
{
	Increase = 0,
	Decrease = 1,
	Count = 2
};

enum class UILayer : EnumValue
{
	SortRule,
	SortBoxesUpperside,
	SortBoxesLowerside,
	SortedShape,
	ResultCurtain,		// 結果画面の幕.
	ResultTexts,
	ResultButtons,
};

enum class BGMID : EnumValue
{
	Title,
	Stage,
	Explain,
	LetsPlay,
	Result,
	Count
};

enum class SEID : EnumValue
{
	ClickButton,
	CorrectSortCombo1,
	CorrectSortCombo2,
	CorrectSortCombo3,
	WrongSort,
	ResultCurtain,
	Count
};

enum class ButtonID : EnumValue
{
	TitleStartGame,
	TitleQuitGame,
	StageSelectLevel01,
	StageSelectLevel02,
	StageSelectLevelMAX,
	StageChangeColor,
	StageSkipExplain,
	LetsPlayMoveNextExplain,
	LetsPlayMovePrevExplain,
	LetsPlayOK,
	LetsPlayStart,
	LetsPlayOpenPause,
	LetsPlayClosePause,
	LetsPlayRetire,
	LetsPlayContinue,
	ResultTryAgain,
	ResultBackStage,
	ResultBackTitle,
	Count
};
