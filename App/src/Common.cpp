#include "stdafx.h"
#include "Common.h"

void GameData::initialize()
{
	m_score = 0;
	m_classifyNum = 0;
	m_correctNum = 0;
	m_missNum = 0;
	m_comboNum = 0;
	m_newRecord = false;

	m_sortRuleGen.init(FigureGenerator::N);
}

void GameData::setSortRule(const size_t nextStageIdx)
{
	if (m_stageIdx != nextStageIdx) m_sortRuleGen.init(nextStageIdx + 1);

	m_stageIdx = nextStageIdx;

	NonRepeatRandomGenerator::GenValue idx = m_sortRuleGen.generate();
	m_currentSortRule = static_cast<SortRule>(idx);
}
