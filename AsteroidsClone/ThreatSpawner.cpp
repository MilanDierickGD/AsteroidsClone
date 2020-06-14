#include "pch.h"
#include "ThreatSpawner.h"
#include "BigAsteroid.h"
#include "ObjectManager.h"
#include "SimpleEnemy.h"

#include <algorithm>

#include "SuicidalEnemy.h"

ThreatSpawner& ThreatSpawner::GetInstance()
{
	static ThreatSpawner instance;
	return instance;
}

void ThreatSpawner::Update()
{
	CountThreats();
	TrySpawnNewWave();
	TrySpawnNewEnemy();
}

void ThreatSpawner::ResetThreats()
{
	m_StaticThreats = 0;
	m_DynamicThreats = 0;

	TrySpawnNewWave();
}

ThreatSpawner::ThreatSpawner(): m_StaticThreats(0), m_DynamicThreats(0),
								m_WaveSpawnCooldown(std::chrono::steady_clock::now()),
								m_EnemySpawningTimer(std::chrono::steady_clock::now()), m_SpawningNewWave(false)
{
}

ThreatSpawner::~ThreatSpawner()
{
}

void ThreatSpawner::CountThreats()
{
	m_StaticThreats = 0;
	m_DynamicThreats = 0;
	
	std::for_each(std::begin(ObjectManager::GetInstance().GetCollidables()),
				std::end(ObjectManager::GetInstance().GetCollidables()), [&](Collidable* collidable)
				{
					switch (collidable->GetCollidableType())
					{
					case BigAsteroidType:
						++m_StaticThreats;
						break;
					case MediumAsteroidType:
						++m_StaticThreats;
						break;
					case SmallAsteroidType:
						++m_StaticThreats;
						break;
					case EnemyBulletType:
						break;
					case EnemyType:
						++m_DynamicThreats;
						break;
					case SuicidalEnemyType:
						++m_DynamicThreats;
					case PlayerType:
						break;
					default:
						break;
					}
				});
}

void ThreatSpawner::TrySpawnNewWave()
{
	if (m_StaticThreats != 0 || m_DynamicThreats != 0) return;

	if (!m_SpawningNewWave)
	{
		m_SpawningNewWave = true;
		m_WaveSpawnCooldown = std::chrono::steady_clock::now();

		std::for_each(std::begin(ObjectManager::GetInstance().GetCollidables()),
					std::end(ObjectManager::GetInstance().GetCollidables()), [](Collidable* collidable)
					{
						collidable->SetDisabled(true);
					});
	}

	const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	const float elapsedSeconds = std::chrono::duration<float>(currentTime - m_WaveSpawnCooldown).count();
	
	if (elapsedSeconds > 5)
	{
		const size_t maximumAsteroidsCount = std::rand() % 6 + 2;
	
		for (size_t counter = 0; counter < maximumAsteroidsCount; ++counter)
		{
			ObjectManager::GetInstance().AddCollidable(new BigAsteroid("Resources/BigAsteroidTexture.png"));
		}

		m_SpawningNewWave = false;
	}
}

void ThreatSpawner::TrySpawnNewEnemy()
{
	if (m_SpawningNewWave) return;
	if (m_DynamicThreats >= 2) return;

	const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	const float elapsedSeconds = std::chrono::duration<float>(currentTime - m_EnemySpawningTimer).count();

	if (elapsedSeconds <= 5) return;

	m_EnemySpawningTimer = std::chrono::steady_clock::now();

	const int spawnChance = std::rand() % 101 + 1;

	if (spawnChance < 50)
	{
		ObjectManager::GetInstance().AddCollidable(new SimpleEnemy("Resources/SimpleEnemyTexture.png"));
	}
	else if (spawnChance >= 50 && spawnChance < 75)
	{
		ObjectManager::GetInstance().AddCollidable(new SuicidalEnemy("Resources/SimpleEnemyTexture.png"));
	}
	
}
