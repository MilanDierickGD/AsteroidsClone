#include "pch.h"
#include "ObjectManager.h"
#include "BigAsteroid.h"

#include <algorithm>
#include <iostream>
#include <iterator>

ObjectManager::ObjectManager() : m_Player(Player("Resources/PlayerTexture.png", 3))
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::PurgeDisabledCollidables()
{
	// const std::vector<Collidable*>::iterator iterator = std::remove_if(std::begin(m_Collidables),
	// 																	std::end(m_Collidables),
	// 																	[](Collidable* collidable)
	// 																	{
	// 																		return collidable->IsDisabled();
	// 																	});
	//
	// std::for_each(iterator, std::end(m_Collidables), [](Collidable* collidable)
	// {
	// 	delete collidable;
	// });
	//
	// m_Collidables.erase(iterator, std::end(m_Collidables));

	m_Collidables.erase(std::remove_if(std::begin(m_Collidables),
                                                                        std::end(m_Collidables),
                                                                        [](Collidable* collidable)
                                                                        {
                                                                            return collidable->IsDisabled();
                                                                        }), std::end(m_Collidables));
}

void ObjectManager::PurgeDisabledParticles()
{
	m_Particles.erase(std::remove_if(std::begin(m_Particles), std::end(m_Particles), [](Particle* particle)
	{
		return particle->IsDisabled();
	}), std::end(m_Particles));
}

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager instance;
	return instance;
}

void ObjectManager::Initialize()
{
	// We might be resetting from a previous game state, so we need to make sure our data is reset

	m_Player.Reset();

	m_Collidables.erase(std::begin(m_Collidables), std::end(m_Collidables));
}

void ObjectManager::Update(const float deltaTime)
{
	m_Player.Update(deltaTime);

	// for (std::vector<Collidable*>::value_type collidable : m_Collidables)
	// {
	// 	collidable->Update(deltaTime);
	// }

	for (size_t counter = 0; counter < m_Collidables.size(); ++counter)
	{
		m_Collidables[counter]->Update(deltaTime);
	}

	for (size_t counter = 0; counter < m_Particles.size(); ++counter)
	{
		m_Particles[counter]->Update(deltaTime);
	}
	
	CheckAllForBounds();
	CheckAllCollisions();
	PurgeDisabledCollidables();
	PurgeDisabledParticles();
}

void ObjectManager::Draw()
{
	m_Player.Draw();
	
	for (std::vector<Collidable*>::value_type collidable : m_Collidables)
	{
		collidable->Draw();
	}

	for (std::vector<Particle*>::value_type particle: m_Particles)
	{
		particle->Draw();
	}
}

void ObjectManager::CheckAllCollisions()
{
	const size_t size = m_Collidables.size();

	for (size_t counter = 0; counter < size; ++counter)
	{
		m_Player.Overlaps(m_Collidables[counter]);
	}
	
	for (size_t counter1 = 0; counter1 < size; ++counter1)
	{
		for	(size_t counter2 = 0; counter2 < size; ++counter2)
		{
			if (counter1 == counter2) continue;
			m_Collidables[counter1]->Overlaps(m_Collidables[counter2]);
		}
	}
}

void ObjectManager::CheckObjectForBounds(Collidable& collidable)
{
	if (collidable.GetEntityPosition().x < 0.0)
	{
		collidable.GetEntityPosition().x = 1280.0;
	}
	else if (collidable.GetEntityPosition().x > 1280.0)
	{
		collidable.GetEntityPosition().x = 0.0;
	}

	if (collidable.GetEntityPosition().y < 0.0)
	{
		collidable.GetEntityPosition().y = 800.0;
	}
	else if (collidable.GetEntityPosition().y > 800.0)
	{
		collidable.GetEntityPosition().y = 0.0;
	}
}

void ObjectManager::CheckAllForBounds()
{
	CheckObjectForBounds(m_Player);
	
	std::for_each(std::begin(m_Collidables), std::end(m_Collidables), [this](Collidable* collectible)
	{
		CheckObjectForBounds(*collectible);
	});
}

void ObjectManager::AddCollidable(Collidable* collidable)
{
	m_Collidables.push_back(std::move(collidable));
}

void ObjectManager::AddParticle(Particle* particle)
{
	m_Particles.push_back(std::move(particle));
}

void ObjectManager::PurgeAllParticles()
{
	m_Particles.erase(std::begin(m_Particles), std::end(m_Particles));
}

Player& ObjectManager::GetPlayer()
{
	return m_Player;
}

const std::vector<Collidable*>& ObjectManager::GetCollidables() const
{
	return m_Collidables;
}
