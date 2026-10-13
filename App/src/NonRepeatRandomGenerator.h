#pragma once

class NonRepeatRandomGenerator
{
public:
	using GenValue = size_t;

	NonRepeatRandomGenerator(const GenValue n);

	~NonRepeatRandomGenerator() = default;

	const GenValue generate();

private:
	GenValue m_n;

	std::vector<GenValue> m_v;

	GenValue m_prevLastElement;

	std::mt19937 m_engine;

	void init();

	// 連続を許さない要素の補充.
	void refill();
};
