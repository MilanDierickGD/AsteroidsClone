#pragma once
#include <chrono>

#include "Collidable.h"
#include "PhysicsObject.h"
#include "Texture.h"

class SuicidalEnemy final : public Collidable, public PhysicsObject
{
public:
    explicit SuicidalEnemy(std::string imagePath);
	
	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;
	void ApplyForceTowardsPlayer(float deltaTime);
	
private:
    void SpawnSimpleEnemy();

	Texture m_SuicidalEnemyTexture;
	std::chrono::steady_clock::time_point m_BulletTimer;
};
