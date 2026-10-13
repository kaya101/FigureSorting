#include "stdafx.h"
#include "NonRepeatRandomGenerator.h"

NonRepeatRandomGenerator::NonRepeatRandomGenerator(const GenValue n)
	: m_n(n)
	, m_engine(std::random_device{}())
{
	init();
}

const NonRepeatRandomGenerator::GenValue NonRepeatRandomGenerator::generate()
{
	if (m_v.empty()) refill();

	const GenValue e = m_v.front();

	m_v.erase(m_v.begin());

	return e;
}

void NonRepeatRandomGenerator::init()
{
	m_prevLastElement = -1;

	refill();
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
