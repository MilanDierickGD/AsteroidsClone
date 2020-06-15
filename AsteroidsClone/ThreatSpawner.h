#pragma once
#include <chrono>

class ThreatSpawner
{
public:
	ThreatSpawner(const ThreatSpawner& other) = delete;
	ThreatSpawner(ThreatSpawner&& other) noexcept = delete;
	ThreatSpawner& operator=(const ThreatSpawner& other) = delete;
	ThreatSpawner& operator=(ThreatSpawner&& other) noexcept = delete;
	
	static ThreatSpawner& GetInstance();

	void Initialize();
	void Update();
	void ResetThreats();
	
private:
	int m_StaticThreats; // Threats that have predicable movement and don't perform special actions
	int m_DynamicThreats; // Threats that move around faster than usual and shoot bullets
	std::chrono::steady_clock::time_point m_WaveSpawnCooldown;
	std::chrono::steady_clock::time_point m_EnemySpawningTimer;
	bool m_SpawningNewWave;

	ThreatSpawner();
	~ThreatSpawner();
	
	void CountThreats();
	void TrySpawnNewWave();
	void TrySpawnNewEnemy();
};
