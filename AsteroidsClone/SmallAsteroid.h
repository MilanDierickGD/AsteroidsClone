#pragma once
#include "ObjectManager.h"

class SmallAsteroid final : public Collidable, public PhysicsObject
{
public:
	SmallAsteroid(std::string imagePath, Vector2D<double> parentAsteroidPosition);
	
	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;

	void SpawnAsteroid(Vector2D<double> parentAsteroidPosition);
	
private:
    Texture m_SmallAsteroidTexture;
};
