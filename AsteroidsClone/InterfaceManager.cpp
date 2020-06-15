#include "pch.h"
#include "InterfaceManager.h"

#include "GameManager.h"
#include "ObjectManager.h"
#include "utils.h"

InterfaceManager& InterfaceManager::GetInstance()
{
	static InterfaceManager instance;
	return instance;
}

void InterfaceManager::ProcessMouseClickEvent(const Vector2D<float> mousePosition) const
{
	switch (GameManager::GetInstance().GetGameState())
	{
	case Menu:
		ProcessMouseClickEventForMenu(mousePosition);
		break;
	case Settings:
		break;
	case Playing:
		break;
	case GameOver:
		ProcessMouseClickEventForGameOver(mousePosition);
		break;
	default:
        break;
	}
}

void InterfaceManager::Draw() const
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

InterfaceManager::InterfaceManager() : m_TitleText(Texture("Resources/TitleText.png")),
										m_StartButtonText(Texture("Resources/PlayButtonText.png")),
										m_SettingsButtonText(Texture("Resources/SettingsButtonText.png")),
										m_GameOverText(Texture("Resources/GameOverText.png")),
										m_TryAgainButtonText(Texture("Resources/TryAgainButtonText.png")),
										m_PlayerTexture(Texture("Resources/PlayerTexture.png"))
{
}

InterfaceManager::~InterfaceManager()
{
}

void InterfaceManager::ProcessMouseClickEventForMenu(const Vector2D<float> mousePosition) const
{
	if (utils::IsPointInRect(Point2f(mousePosition.x, mousePosition.y),
							Rectf(1280.0f / 2 - m_TitleText.GetWidth() / 2, 400, m_StartButtonText.GetWidth(),
								m_StartButtonText.GetHeight())))
	{
		GameManager::GetInstance().SetGameState(Playing);
	}
}

void InterfaceManager::ProcessMouseClickEventForSettings(Vector2D<float> mousePosition)
{
}

void InterfaceManager::ProcessMouseClickEventForStats(Vector2D<float> mousePosition)
{
}

void InterfaceManager::ProcessMouseClickEventForGameOver(const Vector2D<float> mousePosition) const
{
	if (utils::IsPointInRect(Point2f(mousePosition.x, mousePosition.y), Rectf(1280.0f / 2 - m_GameOverText.GetWidth() / 2, 400, m_TryAgainButtonText.GetWidth(), m_TryAgainButtonText.GetHeight())))
	{
		GameManager::GetInstance().SetGameState(Playing);
	}
}

void InterfaceManager::DrawMenu() const
{
	m_TitleText.Draw(Point2D<float>(1280.0f / 2 - m_TitleText.GetWidth() / 2, 600.0f));
	m_StartButtonText.Draw(Point2D<float>(1280.0f / 2 - m_TitleText.GetWidth() / 2, 400));
	m_SettingsButtonText.Draw(Point2D<float>(1280.0f / 2 - m_TitleText.GetWidth() / 2 + m_StartButtonText.GetWidth() + 50, 400));
}

void InterfaceManager::DrawSettings() const
{
}

void InterfaceManager::DrawStats() const
{
	const Texture scoreText = Texture(std::to_string(GameManager::GetInstance().GetScore()), "Resources/Calibri Regular.ttf", 64, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	scoreText.Draw(Point2D<float>(70, 700));

	for (size_t counter = 0; counter < ObjectManager::GetInstance().GetPlayer().GetRemainingLives(); ++counter)
	{
		glPushMatrix();
		glTranslatef(100 + counter * 10 + counter * m_PlayerTexture.GetWidth(), 650, 0);
		glRotatef(90, 0, 0, 1);
		m_PlayerTexture.Draw(Point2D<float>(0, 0));
		glPopMatrix();
	}
}

void InterfaceManager::DrawGameOver() const
{
	m_GameOverText.Draw(Point2D<float>(1280.0f / 2 - m_GameOverText.GetWidth() / 2, 600.0f));
	m_TryAgainButtonText.Draw(Point2D<float>(1280.0f / 2 - m_TryAgainButtonText.GetWidth() / 2, 400));
}
