#pragma once
#include <chrono>

#include "Collidable.h"
#include "PhysicsObject.h"
#include "Texture.h"

class PlayerBullet final : public Collidable, public PhysicsObject
{
public:
	PlayerBullet(std::string imagePath, Vector2D<double> spawnPosition, double launchRotation);
	
	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;

	void SpawnBullet(Vector2D<double> spawnPosition, double launchRotation);
	
private:
    Texture m_BulletTexture;
	std::chrono::steady_clock::time_point m_DeathTimer;
};
