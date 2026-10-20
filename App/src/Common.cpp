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
