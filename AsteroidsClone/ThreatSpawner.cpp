#include "pch.h"
#include "ThreatSpawner.h"

#include <algorithm>



#include "BigAsteroid.h"
#include "ObjectManager.h"

ThreatSpawner& ThreatSpawner::GetInstance()
{
	static ThreatSpawner instance;
	return instance;
}

void ThreatSpawner::Update()
{
	CountThreats();
	SpawnWave();
}

ThreatSpawner::ThreatSpawner(): m_StaticThreats(0), m_DynamicThreats(0)
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
					case BulletType:
						break;
					case EnemyType:
						++m_DynamicThreats;
						break;
					case PlayerType:
						break;
					default:
						break;
					}
				});
}

void ThreatSpawner::SpawnWave() const
{
	if (m_StaticThreats != 0 || m_DynamicThreats != 0) return;
	
	for (size_t counter = 0; counter < 2; ++counter)
	{
		ObjectManager::GetInstance().AddCollidable(new BigAsteroid("Resources/BigAsteroidTexture.png"));
	}
}
