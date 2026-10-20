#include "stdafx.h"
#include "Common.h"

void GameData::initialize()
{
	m_scoreManager.init();
	m_gameManager.init();
}

void GameData::reset()
{
	m_scoreManager.reset();
	m_gameManager.reset();
}

void GameData::retry()
{
	m_scoreManager.retry();
	m_gameManager.retry();
}

//void GameData::setSortRule(const size_t nextStageIdx)
//{
//	if (m_stageIdx != nextStageIdx) m_sortRuleGen.init(nextStageIdx + 1);
//
//	m_stageIdx = nextStageIdx;
//
//	NonRepeatRandomGenerator::GenValue idx = m_sortRuleGen.generate();
//	m_currentSortRule = static_cast<SortRule>(idx);
//}
