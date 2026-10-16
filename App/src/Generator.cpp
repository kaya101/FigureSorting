#include "stdafx.h"
#include "Generator.h"
#include "Common.h"

/*	Start NonRepeatRandomGenerator	********************************************************************************************************/

void NonRepeatRandomGenerator::init(const GenValue n)
{
	m_n = n;

	std::random_device seedGen;
	auto seed = seedGen();
	m_engine = std::mt19937(seed);

	m_prevLastElement = 999;

	refill();
}

const GenValue NonRepeatRandomGenerator::generate()
{
	if (m_v.empty()) refill();

	const GenValue e = m_v.front();

	m_v.erase(m_v.begin());

	return e;
}

// 連続を許さない要素の補充.
void NonRepeatRandomGenerator::refill()
{
	// 0 から N-1 までの値を生成.
	m_v.clear();
	m_v.resize(m_n);
	std::iota(m_v.begin(), m_v.end(), 0);

	if (m_n <= 1) return;

	// 補充した要素の先頭が、補充前の最後の要素と異なるようにする.
	do std::shuffle(m_v.begin(), m_v.end(), m_engine);
	while (m_v.front() == m_prevLastElement);

	m_prevLastElement = m_v.back();
}

/*	End NonRepeatRandomGenerator	********************************************************************************************************/

/*	Start FigureGenerator			********************************************************************************************************/

// 使用する図形.
const std::array<std::function<std::unique_ptr<SortedShapeBase>(const SortedShapeCtx&)>, FigureGenerator::N> FigureGenerator::SortingShapes = {
	[](const SortedShapeCtx& ctx) { return std::make_unique<SortedCricle>(ctx); },
	[](const SortedShapeCtx& ctx) { return std::make_unique<SortedSquare>(ctx); },
	[](const SortedShapeCtx& ctx) { return std::make_unique<SortedTriangle>(ctx); }
};

// 使用する色.
const std::array<ColorF, FigureGenerator::N> FigureGenerator::SortingColorsDefault = { aka, midori,   ao };
const std::array<ColorF, FigureGenerator::N> FigureGenerator::SortingColorsChanged = { red,  yelow, blue };

// 使用する文字.
const std::array<String, FigureGenerator::N> FigureGenerator::SortingTextsDefault = { U"あか", U"みどり"  , U"あお" };
const std::array<String, FigureGenerator::N> FigureGenerator::SortingTextsChanged = { U"まる", U"さんかく", U"しかく" };

void FigureGenerator::init()
{
	m_shapeGen.init(N);
	m_colorGen.init(N);
	m_textGen.init(N);
}

std::unique_ptr<SortedShapeBase> FigureGenerator::generate(const StageLevel level, const SortRule rule, const bool isChangedColor)
{
	std::unique_ptr<SortedShapeCtx> ctxPtr;
	GenValue shapeIdx;
	GenValue colorIdx;
	GenValue textIdx;

	// 形による分類パターンの決定.
	shapeIdx = m_shapeGen.generate();
	ColorF color = (isChangedColor) ? yelow : midori;
	String text = U"";

	// 色 による分類パターンの追加.
	if (level >= StageLevel::Level02) colorIdx = m_colorGen.generate();

	// 文字 による分類パターンの追加.
	if (level >= StageLevel::LevelMAX) textIdx = m_textGen.generate();

	// 生成.
	auto& function = SortingShapes[shapeIdx];
	if (isChangedColor)
	{
		color = SortingColorsChanged[colorIdx];
		text = SortingTextsChanged[textIdx];
	}
	else
	{
		color = SortingColorsDefault[colorIdx];
		text = SortingTextsDefault[textIdx];
	}
	ctxPtr = std::make_unique<SortedShapeCtx>(AppearPoint, ShapoeSize, color, text, static_cast<SortingShapeType>(shapeIdx));

	auto shapePtr = function(*ctxPtr);

	ctxPtr = nullptr;

	return shapePtr;
}

/*	End FigureGenerator				********************************************************************************************************/
