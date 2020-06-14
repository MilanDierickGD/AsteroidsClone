#include "pch.h"
#include "SimpleEnemy.h"

#include <iostream>



#include "EnemyBullet.h"
#include "ObjectManager.h"

SimpleEnemy::SimpleEnemy(const std::string imagePath) : m_SimpleEnemyTexture(Texture(imagePath)),
														m_BulletTimer(std::chrono::steady_clock::now())
{
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
                                        Vector2D<double>(m_SimpleEnemyTexture.GetWidth() / 2,
                                                        m_SimpleEnemyTexture.GetHeight() / 2)));

	SetCollidableType(EnemyType);
	SetDisabled(false);
	SpawnSimpleEnemy();
}

void SimpleEnemy::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	GetCollider2D().center.x = GetEntityPosition().x + GetCollider2D().halfSize.x;
	GetCollider2D().center.y = GetEntityPosition().y + GetCollider2D().halfSize.y;
	SpawnBullet();
}

void SimpleEnemy::Draw()
{
	m_SimpleEnemyTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x), static_cast<float>(GetEntityPosition().y)));
}

void SimpleEnemy::OnOverlap(Collidable* other)
{
	switch (other->GetCollidableType())
	{
	case BigAsteroidType: case MediumAsteroidType: case SmallAsteroidType: case EnemyBulletType: case PlayerType:
		SetDisabled(true);
		break;
	case EnemyType:
		break;
	case PlayerBulletType:
		SetDisabled(true);
		//ScoreManager::GetInstance().AddPoints(200);
		break;
	default:
		break;
	}
}

void SimpleEnemy::SpawnSimpleEnemy()
{
	const int spawnFace = std::rand() % 4;

	switch (spawnFace)
	{
	case 0:
        SetEntityPosition(Vector2D<double>(std::rand() % 1280, 800.0));
		GetCollider2D().center = GetEntityPosition();
		SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
		break;
	case 1:
        SetEntityPosition(Vector2D<double>(0.0, std::rand() % 800));
		GetCollider2D().center = GetEntityPosition();
		SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
		break;
	case 2:
        SetEntityPosition(Vector2D<double>(std::rand() % 1280, 0.0));
		GetCollider2D().center = GetEntityPosition();
		SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
		break;
	case 3:
        SetEntityPosition(Vector2D<double>(1280, std::rand() % 800));
		GetCollider2D().center = GetEntityPosition();
		SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
		break;
	default:
        break;
	}
}

void SimpleEnemy::SpawnBullet()
{
	const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	const float elapsedSeconds = std::chrono::duration<float>(currentTime - m_BulletTimer).count();
	
	if (elapsedSeconds > 1)
	{
		ObjectManager::GetInstance().AddCollidable(new EnemyBullet("Resources/EnemyBulletTexture.png", GetEntityPosition(), std::rand() % 360));
		m_BulletTimer = std::chrono::steady_clock::now();
	}
}
