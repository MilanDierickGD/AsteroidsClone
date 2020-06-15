#pragma once
#include <unordered_set>

#include "Collidable.h"
#include "Player.h"

class ObjectManager
{
public:
	ObjectManager(const ObjectManager& other) = delete;
	ObjectManager(ObjectManager&& other) noexcept = delete;
	ObjectManager& operator=(const ObjectManager& other) = delete;
	ObjectManager& operator=(ObjectManager&& other) noexcept = delete;
	
	static ObjectManager& GetInstance();

	void Initialize();
	void Update(float deltaTime);
	void Draw();
	void CheckAllCollisions();
	void AddCollidable(Collidable* collidable);

	Player& GetPlayer();
	const std::vector<Collidable*>& GetCollidables() const;
	
private:
	std::vector<Collidable*> m_Collidables;
	Player m_Player;

	ObjectManager();
	~ObjectManager();

	void PurgeDisabledCollidables();
	void CheckAllForBounds();
	void CheckObjectForBounds(Collidable& collidable);
};
