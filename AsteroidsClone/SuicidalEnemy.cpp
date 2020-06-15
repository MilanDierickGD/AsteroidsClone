#include "pch.h"
#include "SuicidalEnemy.h"

#include <iostream>



#include "GameManager.h"
#include "ObjectManager.h"


SuicidalEnemy::SuicidalEnemy(const std::string imagePath): m_SuicidalEnemyTexture(Texture(imagePath)),
															m_BulletTimer(std::chrono::steady_clock::now())
{
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
                                    Vector2D<double>(m_SuicidalEnemyTexture.GetWidth() / 2,
                                                    m_SuicidalEnemyTexture.GetHeight() / 2)));

	SetCollidableType(EnemyType);
	SetDisabled(false);
	SpawnSimpleEnemy();
}

void SuicidalEnemy::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	ApplyForceTowardsPlayer(deltaTime);

	if (GetObjectMovement().x > 100)
	{
		GetObjectMovement().x = 100;
	}
	else if (GetObjectMovement().x < -100)
	{
		GetObjectMovement().x = -100;
	}
	if (GetObjectMovement().y > 100)
	{
		GetObjectMovement().y = 100;
	}
	else if (GetObjectMovement().y < -100)
	{
		GetObjectMovement().y = -100;
	}
	
	GetCollider2D().center.x = GetEntityPosition().x + GetCollider2D().halfSize.x;
	GetCollider2D().center.y = GetEntityPosition().y + GetCollider2D().halfSize.y;
}

void SuicidalEnemy::Draw()
{
	m_SuicidalEnemyTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x), static_cast<float>(GetEntityPosition().y)));
}

void SuicidalEnemy::OnOverlap(Collidable* other)
{
	switch (other->GetCollidableType())
	{
	case EnemyBulletType: case PlayerType:
        SetDisabled(true);
		break;
	case PlayerBulletType:
        SetDisabled(true);
		GameManager::GetInstance().AddScore(200);
		break;
	default:
        break;
	}
}

void SuicidalEnemy::ApplyForceTowardsPlayer(const float deltaTime)
{
	if (ObjectManager::GetInstance().GetPlayer().GetEntityPosition().x > GetEntityPosition().x)
	{
		ApplyForce(Vector2D<double>(500.0 * deltaTime, 0.0f));
	}
	else if (ObjectManager::GetInstance().GetPlayer().GetEntityPosition().x < GetEntityPosition().x)
	{
		ApplyForce(Vector2D<double>(-500.0 * deltaTime, 0.0f));
	}

	if (ObjectManager::GetInstance().GetPlayer().GetEntityPosition().y > GetEntityPosition().y)
	{
		ApplyForce(Vector2D<double>(0.0, 500.0f * deltaTime));
	}
	else if (ObjectManager::GetInstance().GetPlayer().GetEntityPosition().y < GetEntityPosition().y)
	{
		ApplyForce(Vector2D<double>(0.0, -500.0f * deltaTime));
	}
}

void SuicidalEnemy::SpawnSimpleEnemy()
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
        SetEntityPosition(Vector2D<double>(1280.0, std::rand() % 800));
		GetCollider2D().center = GetEntityPosition();
		SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
		break;
	default:
        break;
	}
}
