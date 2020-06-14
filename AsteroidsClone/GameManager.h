#pragma once

enum GameState
{
	Menu, Settings, Playing, GameOver
};

class GameManager
{
public:
	GameManager(const GameManager& other) = delete;
	GameManager(GameManager&& other) noexcept = delete;
	GameManager& operator=(const GameManager& other) = delete;
	GameManager& operator=(GameManager&& other) noexcept = delete;

	static GameManager& GetInstance();
	GameState GetGameState() const;
	
private:
	GameState m_GameState;
	
	GameManager();
	~GameManager();
};
