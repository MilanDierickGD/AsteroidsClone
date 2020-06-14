#pragma once
#include "Collidable.h"
#include "PhysicsObject.h"
#include "Texture.h"

class ObjectManager;

class Bullet final : public Collidable, public PhysicsObject
{
public:
	Bullet(std::string imagePath, Vector2D<double> spawnPosition, double launchRotation);
	
	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;

	void SpawnBullet(Vector2D<double> spawnPosition, double launchRotation);
	
private:
	Texture m_BulletTexture;
};
