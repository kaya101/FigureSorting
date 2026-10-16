#pragma once
#include "Enums.h"
#include "SortedShape.h"

class NonRepeatRandomGenerator
{
public:
	using GenValue = size_t;

	NonRepeatRandomGenerator() = default;

	~NonRepeatRandomGenerator() = default;

	void init(const GenValue n);

	const GenValue generate();

private:
	GenValue m_n;

	std::vector<GenValue> m_v;

	GenValue m_prevLastElement;

	std::mt19937 m_engine;

	// 連続を許さない要素の補充.
	void refill();
};

class FigureGenerator
{
public:
	static constexpr NonRepeatRandomGenerator::GenValue N = 3;

	static constexpr Vec2 AppearPoint = { 400, 470 };	// 図形出現の中心座標.

	static constexpr size_t ShapoeSize = 120;			// 図形の基本サイズ.

	static constexpr size_t TextSize = 28;				// 図形の文字の基本サイズ.

	// 使用する図形.
	static const std::array<std::function<std::unique_ptr<SortedShapeBase>(const SortedShapeCtx&)>, N> SortingShapes;

	// 使用する色.
	static const std::array<ColorF, N> SortingColorsDefault;
	static const std::array<ColorF, N> SortingColorsChanged;

	// 使用する文字.
	static const std::array<String, N> SortingTextsDefault;
	static const std::array<String, N> SortingTextsChanged;

	explicit FigureGenerator() = default;

	~FigureGenerator() = default;

	void init();

	std::unique_ptr<SortedShapeBase> generate(const StageLevel level, const SortRule rule, const bool isChangedColor);

private:
	NonRepeatRandomGenerator m_shapeGen;

	NonRepeatRandomGenerator m_colorGen;

	NonRepeatRandomGenerator m_textGen;
};
