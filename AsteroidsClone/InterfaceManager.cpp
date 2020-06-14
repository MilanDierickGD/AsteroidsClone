#include "pch.h"
#include "InterfaceManager.h"

#include "GameManager.h"

InterfaceManager& InterfaceManager::GetInstance()
{
	static InterfaceManager instance;
	return instance;
}

void InterfaceManager::ProcessMouseClickEvent(Vector2D<float> mousePosition)
{
}

void InterfaceManager::Draw()
{
	switch (GameManager::GetInstance().GetGameState())
	{
	case Menu:
		DrawMenu();
		break;
	case Settings:
		DrawSettings();
		break;
	case Playing:
		DrawStats();
		break;
	case GameOver:
		DrawGameOver();
		break;
	default:
		break;
	}
}

void InterfaceManager::DrawMenu()
{
}

void InterfaceManager::DrawSettings()
{
}

void InterfaceManager::DrawStats()
{
}

void InterfaceManager::DrawGameOver()
{
}

InterfaceManager::InterfaceManager()
{
}

InterfaceManager::~InterfaceManager()
{
}
