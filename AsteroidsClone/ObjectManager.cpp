#include "pch.h"
#include "ObjectManager.h"

#include <algorithm>
#include <iterator>



#include "BigAsteroid.h"

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

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager instance;
	return instance;
}

void ObjectManager::Update(const float deltaTime)
{
	m_Player.Update(deltaTime);

	for (std::vector<Collidable*>::value_type collidable : m_Collidables)
	{
		collidable->Update(deltaTime);
	}

	CheckAllForBounds();
	CheckAllCollisions();
	PurgeDisabledCollidables();
}

void ObjectManager::Draw()
{
	m_Player.Draw();
	
	for (std::vector<Collidable*>::value_type collidable : m_Collidables)
	{
		collidable->Draw();
	}
}

void ObjectManager::CheckAllCollisions()
{
	const size_t size = m_Collidables.size();
	for (size_t x = 0; x < size; ++x)
	{
		for	(size_t y = 0; y < size; ++y)
		{
			if (x == y) continue;
			m_Collidables[x]->Overlaps(m_Collidables[y]);
		}
	}
}

void ObjectManager::CheckObjectForBounds(Collidable& collidable)
{
	if (collidable.GetEntityPosition().x < 0.0)
	{
		if (collidable.GetCollidableType() == BulletType)
		{
			collidable.SetDisabled(true);
		}
		else
		{
			collidable.GetEntityPosition().x = 1920.0;
		}
	}
	else if (collidable.GetEntityPosition().x > 1920.0)
	{
		if (collidable.GetCollidableType() == BulletType)
		{
			collidable.SetDisabled(true);
		}
		else
		{
			collidable.GetEntityPosition().x = 0.0;
		}
	}

	if (collidable.GetEntityPosition().y < 0.0)
	{
		if (collidable.GetCollidableType() == BulletType)
		{
			collidable.SetDisabled(true);
		}
		else
		{
			collidable.GetEntityPosition().y = 1080.0;
		}
	}
	else if (collidable.GetEntityPosition().y > 1080.0)
	{
		if (collidable.GetCollidableType() == BulletType)
		{
			collidable.SetDisabled(true);
		}
		else
		{
			collidable.GetEntityPosition().y = 0.0;
		}
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

Player& ObjectManager::GetPlayer()
{
	return m_Player;
}

const std::vector<Collidable*>& ObjectManager::GetCollidables() const
{
	return m_Collidables;
}
