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

	m_prevLastElement = -1;

	refill();
}

const NonRepeatRandomGenerator::GenValue NonRepeatRandomGenerator::generate()
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

std::unique_ptr<SortedShapeBase> FigureGenerator::generate(const SortRule rule, const bool isChangedColor)
{
	NonRepeatRandomGenerator::GenValue shapeIdx = m_shapeGen.generate();
	NonRepeatRandomGenerator::GenValue colorIdx = m_colorGen.generate();
	NonRepeatRandomGenerator::GenValue textIdx = m_textGen.generate();

	auto& function = SortingShapes[shapeIdx];

	String text{};
	ColorF color{};

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
	SortedShapeCtx ctx(AppearPoint, ShapoeSize, color, text, static_cast<SortingShapeType>(shapeIdx));

	return function(ctx);
}

/*	End FigureGenerator				********************************************************************************************************/
