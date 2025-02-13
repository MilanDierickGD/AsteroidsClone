﻿#pragma once
#include <chrono>

#include "Collidable.h"
#include "PhysicsObject.h"
#include "Texture.h"

class SimpleEnemy final : public Collidable, public PhysicsObject
{
public:
	explicit SimpleEnemy(std::string imagePath);

	void Update(float deltaTime) override;
	void Draw() override;
	void OnOverlap(Collidable* other) override;
	
private:
	void SpawnSimpleEnemy();
	void SpawnBullet();

	Texture m_SimpleEnemyTexture;
	std::chrono::steady_clock::time_point m_BulletTimer;
};
