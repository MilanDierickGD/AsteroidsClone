#pragma once

class ThreatSpawner
{
public:
	ThreatSpawner(const ThreatSpawner& other) = delete;
	ThreatSpawner(ThreatSpawner&& other) noexcept = delete;
	ThreatSpawner& operator=(const ThreatSpawner& other) = delete;
	ThreatSpawner& operator=(ThreatSpawner&& other) noexcept = delete;
	
	static ThreatSpawner& GetInstance();
	
	void Update();
	
private:
	int m_StaticThreats; // Threats that have predicable movement and don't perform special actions
	int m_DynamicThreats; // Threats that move around faster than usual and shoot bullets

	ThreatSpawner();
	~ThreatSpawner();
	
	void CountThreats();
	void SpawnWave() const;
};
