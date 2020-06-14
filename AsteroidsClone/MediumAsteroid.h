#pragma once

#include "Collidable.h"
#include "ObjectManager.h"
#include "PhysicsObject.h"
#include "Texture.h"

class MediumAsteroid final : public Collidable, public PhysicsObject
{
public:
	MediumAsteroid(std::string imagePath, Vector2D<double> parentAsteroidPosition);
	
	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;

	void Split();
	void SpawnAsteroid(Vector2D<double> parentAsteroidPosition);
	
private:
    Texture m_MediumAsteroidTexture;
};
