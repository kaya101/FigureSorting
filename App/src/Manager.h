#pragma once
#include "SortedShape.h"
#include "Generator.h"
#include "Enums.h"

class GameManager;
class ScoreManager
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

	explicit ScoreManager(GameManager& gameManager)
		: m_gameManager(gameManager)
	{
		init();
	}

	~ScoreManager() = default;

	void init();

	void classify(const EnumValue boxIdx);

	void updateHighScores(const StageLevel level);

	void draw() const;

	const ScoreValue score() const { return m_score; }
	const uint8 classifyNum() const { return m_classifyNum; }
	const uint8 correctNum() const { return m_correctNum; }
	const uint8 missNum() const { return m_missNum; }
	const uint8 comboNum() const { return m_comboNum; }
	const bool newRecord() const { return m_newRecord; }
	const std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)>& highScores() const { return m_highScores; }

private:
	GameManager& m_gameManager;

	ScoreValue m_score = 0;

	uint8 m_classifyNum = 0;	// 仕分けた個数.

	uint8 m_correctNum = 0;		// 正解した個数.

	uint8 m_missNum = 0;		// 間違えた個数.

	uint8 m_comboNum = 0;		// 連続正解数をカウント.

	bool m_newRecord = false;	// 記録を更新したかどうか.

	std::array<ScoreValue, static_cast<EnumValue>(StageLevel::Count)> m_highScores = { 0, 0, 0 };

	void sumScore(const ScoreValue amount) { m_score = Max(0, m_score + amount); }

	void correct(const size_t stageIdx);

	void miss(const size_t stageIdx);

	//void countClassifyNum() { ++m_classifyNum; }

	//void countCorrectNum() { ++m_correctNum; }

	//void countMissNum() { ++m_missNum; }

	//void countComboNum() { ++m_comboNum; }

	//void resetComboNum() { m_comboNum = 0; }
};

class GameManager
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
		m_scoreManagerPtr = std::make_unique<ScoreManager>(*this);

		m_sortRuleGenPtr = std::make_unique<NonRepeatRandomGenerator>();
		m_sortRuleGenPtr->init(FigureGenerator::N);

		//init();
	}

	~GameManager() = default;

	void init();

	void update();

	void draw() const;

	void setSortRule(const EnumValue nextStageIdx);

	void turnOnChangedColor() { m_isChangedColor = true; }
	void turnOffChangedColor() { m_isChangedColor = false; }

	void turnOnSkippedExplain() { m_isSkippedExplain = true; }
	void turnOffSkippedExplain() { m_isSkippedExplain = false; }

	void turnOnPause() { m_isPaused = true; }
	void turnOffPause() { m_isPaused = false; }

	void setTF(const TrueOrFalse tf) { m_tof = tf; }

	const SortedShapeBase* sortedShapePtr() const { return m_sortedShapePtr.get(); }
	ScoreManager* scoreManagerPtr() { return m_scoreManagerPtr.get(); }
	const SortRule currentSortRule() const { return m_currentSortRule; }
	const bool isChangedColor() const { return m_isChangedColor; }
	const bool isSkippedExplain() const { return m_isSkippedExplain; }
	const bool isPaused() const { return m_isPaused; }
	const StageLevel stageLevel() const { return m_stageLevel; }

private:
	// 動かす図形の素材の受け皿.
	std::unique_ptr<SortedShapeBase> m_sortedShapePtr;

	std::unique_ptr<ScoreManager> m_scoreManagerPtr;

	std::unique_ptr<NonRepeatRandomGenerator> m_sortRuleGenPtr;

	std::unique_ptr<FigureGenerator> m_figureGenPtr;

	// 図形を持ち運ぶときの図形の中心とカーソルの距離を保持する.
	Vec2 m_distance = Vec2().Zero();

	SortRule m_currentSortRule;

	bool m_isChangedColor;

	bool m_isSkippedExplain = false;

	bool m_canDisplayRule = false;

	bool m_isPaused = false;

	StageLevel m_stageLevel = StageLevel::Count;		// どのステージか.

	TrueOrFalse m_tof = TrueOrFalse::WaitSort;	// 正誤判定.

	Stopwatch m_truefalse{ StartImmediately::Yes };	// 正誤判定のエフェクト.

	FigureSwitch m_currentFigureSwitch = FigureSwitch::MakeFigure;

	std::unique_ptr<SortedShapeBase> generateFigure()
	{
		return m_figureGenPtr->generate(m_currentSortRule, m_isChangedColor);
	}

	// 正誤判定のエフェクト.
	void effect_TrueOrFalse(double t, const uint8& comboNum, const ColorF& colorf, const Font& font, const uint8& textsize);
};
