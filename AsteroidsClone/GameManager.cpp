#include "pch.h"
#include "GameManager.h"

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

GameState GameManager::GetGameState() const
{
	return m_GameState;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}
