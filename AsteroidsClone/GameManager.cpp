#include "pch.h"
#include "GameManager.h"

#include "InterfaceManager.h"
#include "ObjectManager.h"
#include "ThreatSpawner.h"

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

GameState GameManager::GetGameState() const
{
	return m_CurrentGameState;
}

void GameManager::SetGameState(const GameState gameState)
{
	m_PreviousGameState = m_CurrentGameState;
	m_CurrentGameState = gameState;

	if ((m_PreviousGameState == Menu || m_PreviousGameState == GameOver) && m_CurrentGameState == Playing)
	{
		ObjectManager::GetInstance().Initialize();
		ThreatSpawner::GetInstance().Initialize();
		m_Score = 0;
	}
}

int GameManager::GetScore() const
{
	return m_Score;
}

void GameManager::Update(const float deltaTime) const
{
	switch (m_CurrentGameState)
	{
	case Menu:
		break;
	case Settings:
		break;
	case Playing:
		ObjectManager::GetInstance().Update(deltaTime);
		ThreatSpawner::GetInstance().Update();
		break;
	case GameOver:
		break;
	default:
		break;
	}
}

void GameManager::Draw() const
{
	switch (m_CurrentGameState)
	{
	case Menu:
        InterfaceManager::GetInstance().Draw();
		break;
	case Settings:
        InterfaceManager::GetInstance().Draw();
		break;
	case Playing:
		InterfaceManager::GetInstance().Draw();
		ObjectManager::GetInstance().Draw();
		break;
	case GameOver:
        InterfaceManager::GetInstance().Draw();
		break;
	default:
        break;
	}
}

void GameManager::AddScore(const int amount)
{
	const int temp = m_PlayerLivesScore;
	m_PlayerLivesScore += amount;
	m_PlayerLivesScore = m_PlayerLivesScore % 10000;
	if (m_PlayerLivesScore < temp)
	{
		ObjectManager::GetInstance().GetPlayer().AddLife();
	}
	m_Score += amount;
}

GameManager::GameManager(): m_CurrentGameState(Menu), m_PreviousGameState(Menu), m_Score(0), m_PlayerLivesScore(0)
{
}

GameManager::~GameManager()
{
}
