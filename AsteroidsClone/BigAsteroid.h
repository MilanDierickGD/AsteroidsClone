#pragma once
#include <memory>

#include "Collidable.h"
#include "ObjectManager.h"
#include "PhysicsObject.h"
#include "Texture.h"

class BigAsteroid final : public Collidable, public PhysicsObject
{
public:
	explicit BigAsteroid(std::string imagePath);

	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;

	void Split();
	void SpawnAsteroid();
private:
	Texture m_BigAsteroidTexture;
};
