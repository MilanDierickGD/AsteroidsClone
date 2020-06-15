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
	void SetGameState(GameState gameState);
	int GetScore() const;

	void Update(float deltaTime) const;
	void Draw() const;

	void AddScore(int amount);
	
private:
	GameState m_CurrentGameState;
	GameState m_PreviousGameState;
	int m_Score;
	
	GameManager();
	~GameManager();
};
