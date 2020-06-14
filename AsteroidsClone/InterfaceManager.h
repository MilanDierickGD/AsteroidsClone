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

	void ProcessMouseClickEvent(Vector2D<float> mousePosition);
	
	void Draw();
	void DrawMenu();
	void DrawSettings();
	void DrawStats();
	void DrawGameOver();
	
private:
	Texture m_TitleText;
	Texture m_StartText;
	Texture m_OptionsText;
	Texture m_GameOverText;
	Texture m_TryAgainText;
	Texture m_BackText;
	
	InterfaceManager();
	~InterfaceManager();
};
