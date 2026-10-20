#pragma once
#include "SortedShape.h"
#include "Generator.h"
#include "Enums.h"

class IManager
{
public:
	virtual ~IManager() = default;

	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void retry() = 0;
};

class GameManager : public IManager
{
public:
	static constexpr RectF SortedArea = { Vec2(50, 130), SizeF(700, 400) };	// 見えない壁の当たり判定.
	static constexpr Vec2 siwakerule = { 400, 60 };	// 仕分けルールの表示位置.
	static constexpr uint8 siwakesize = 48;			// 仕分けルールの文字の大きさ.

	using SortingBoxArray = std::array<RectF, static_cast<EnumValue>(SortingBoxIdx::Count)>;
	static constexpr std::array<SortingBoxArray, static_cast<EnumValue>(SortingBoxLayerIdx::Count)> SortingBoxes = {
		SortingBoxArray{ RectF(50, 390, 160, 140), RectF(320, 110, 160, 140), RectF(590, 390, 160, 140) },	// 下側.
		SortingBoxArray{ RectF(50, 410, 160, 120), RectF(320, 130, 160, 120), RectF(590, 410, 160, 120) }	// 上側.
	};
	static const std::array<String, static_cast<EnumValue>(SortingBoxIdx::Count)> SortingBoxesMarks;

	explicit GameManager()
	{
		init();
	}

	~GameManager() = default;

	void init() override;
	void reset() override;
	void retry() override;

	void update();
	void generateFigure();
	void draw() const;
	void setSortRule(const EnumValue nextStageIdx);
	void turnOnChangedColor() { m_isChangedColor = true; }
	void turnOffChangedColor() { m_isChangedColor = false; }
	void turnOnSkippedExplain() { m_isSkippedExplain = true; }
	void turnOffSkippedExplain() { m_isSkippedExplain = false; }
	void turnOnPause() { m_isPaused = true; }
	void turnOffPause() { m_isPaused = false; }
	void clearClassified() { m_isClassified = false; }

	const SortedShapeBase* sortedShapePtr() const { return m_sortedShapePtr.get(); }
	const SortRule currentSortRule() const { return m_currentSortRule; }
	const bool isChangedColor() const { return m_isChangedColor; }
	const bool isSkippedExplain() const { return m_isSkippedExplain; }
	const bool isPaused() const { return m_isPaused; }
	const bool isClassified() const { return m_isClassified; }
	const SortingBoxIdx boxIdx() const { return m_boxIdx; }
	const StageLevel stageLevel() const { return m_stageLevel; }

private:
	std::unique_ptr<SortedShapeBase> m_sortedShapePtr;

	NonRepeatRandomGenerator m_sortRuleGen;
	FigureGenerator m_figureGen;

	Vec2 m_distance;	// 図形を持ち運ぶときの図形の中心とカーソルの距離を保持する.
	SortRule m_currentSortRule;
	bool m_isChangedColor;
	bool m_isSkippedExplain;
	bool m_canDisplayRule;
	bool m_isPaused;
	bool m_isClassified;
	SortingBoxIdx m_boxIdx;
	StageLevel m_stageLevel;		// どのステージか.
};

class ScoreManager : public IManager
{
public:
	using ScoreValue = int16;

	using ScoreArray = std::array<ScoreValue, static_cast<EnumValue>(ScoreChange::Count)>;
	using StageScoreArray = std::array<ScoreArray, static_cast<EnumValue>(StageLevel::Count)>;
	static constexpr StageScoreArray Scores = {
		ScoreArray{ 100, -50  },	// Lv.01.
		ScoreArray{ 250, -300 },	// Lv.02.
		ScoreArray{ 500, -1000}		// Lv.MAX.
	};
	struct AnswerData
	{
		struct Colors { ColorF colorDefault; ColorF colorChanged; };
		struct Texts { String textDefault; String textChanged; };

		SortingShapeType type;
		Colors colors;
		Texts texts;
	};
	static const std::array<AnswerData, static_cast<EnumValue>(SortingBoxIdx::Count)> SortingAnswers;

	explicit ScoreManager()
	{
		init();
	}

	~ScoreManager() = default;

	void init() override;
	void reset() override;
	void retry() override;

	void classify(const GameManager& gm);
	void updateHighScores(const StageLevel level);
	void draw() const;

	const ScoreValue score() const { return m_score; }
	const uint8 classifyNum() const { return m_classifyNum; }
	const uint8 correctNum() const { return m_correctNum; }
	const uint8 missNum() const { return m_missNum; }
	const uint8 comboNum() const { return m_comboNum; }
	const bool newRecord() const { return m_newRecord; }
	const bool isCorrectSorted() const { return m_isCorrectSorted; }
	const std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)>& highScores() const { return m_highScores; }

private:
	ScoreValue m_score;
	uint8 m_classifyNum;	// 仕分けた個数.
	uint8 m_correctNum;		// 正解した個数.
	uint8 m_missNum;		// 間違えた個数.
	uint8 m_comboNum;		// 連続正解数をカウント.
	bool m_newRecord;		// 記録を更新したかどうか.
	bool m_isCorrectSorted;
	std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)> m_highScores;

	void sumScore(const ScoreValue amount) { m_score = Max(0, m_score + amount); }
	void correct(const StageLevel level);
	void miss(const StageLevel level);
};

class UIManager : public IManager
{
public:
	explicit UIManager()
	{
		init();
	}

	~UIManager() = default;

	void init() override;
	void reset() override;
	void retry() override;

private:
};
