#pragma once
#include "Texture.h"
#include "Vector2D.h"

class InterfaceManager
{
public:
	InterfaceManager(const InterfaceManager& other) = delete;
	InterfaceManager(InterfaceManager&& other) noexcept = delete;
	InterfaceManager& operator=(const InterfaceManager& other) = delete;
	InterfaceManager& operator=(InterfaceManager&& other) noexcept = delete;

	static InterfaceManager& GetInstance();

	void ProcessMouseClickEvent(Vector2D<float> mousePosition) const;
	
	void Draw() const;
	
private:
	Texture m_TitleText;
	Texture m_StartButtonText;
	Texture m_SettingsButtonText;
	Texture m_GameOverText;
	Texture m_TryAgainButtonText;
	Texture m_BackButtonText;
	Texture m_PlayerTexture;
	
	InterfaceManager();
	~InterfaceManager();

	void ProcessMouseClickEventForMenu(Vector2D<float> mousePosition) const;
	void ProcessMouseClickEventForSettings(Vector2D<float> mousePosition);
	void ProcessMouseClickEventForStats(Vector2D<float> mousePosition);
	void ProcessMouseClickEventForGameOver(Vector2D<float> mousePosition) const;
	
	void DrawMenu() const;
	void DrawSettings() const;
	void DrawStats() const;
	void DrawGameOver() const;
};
