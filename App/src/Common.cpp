#include "stdafx.h"
#include "Common.h"

void GameData::initialize()
{
	m_gameManager.init();
	m_scoreManager.init();
	m_uiManager.init();
}

void GameData::reset()
{
	m_gameManager.reset();
	m_scoreManager.reset();
	m_uiManager.reset();
}

void GameData::retry()
{
	m_gameManager.retry();
	m_scoreManager.retry();
	m_uiManager.retry();
}
