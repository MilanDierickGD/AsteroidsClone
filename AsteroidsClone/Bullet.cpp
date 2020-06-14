#include "pch.h"
#include "Bullet.h"

#include <iostream>


#include "ObjectManager.h"

Bullet::Bullet(const std::string imagePath, const Vector2D<double> spawnPosition,
				const double launchRotation)
{
	m_BulletTexture = Texture(imagePath);
	
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
                                Vector2D<double>(m_BulletTexture.GetWidth() / 2,
                                                m_BulletTexture.GetHeight() / 2)));

	SetCollidableType(BulletType);
	SetDisabled(false);
	SpawnBullet(spawnPosition, launchRotation);	
}

void Bullet::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	GetCollider2D().center = GetEntityPosition();
}

void Bullet::Draw()
{
	m_BulletTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x), static_cast<float>(GetEntityPosition().y)));
}

void Bullet::OnOverlap(Collidable* other)
{
	SetDisabled(true);
}

void Bullet::SpawnBullet(const Vector2D<double> spawnPosition, const double launchRotation)
{
	SetEntityPosition(Vector2D<double>(spawnPosition.x + std::cos(launchRotation) * 20,
										spawnPosition.y + std::sin(launchRotation) * 20));
	GetCollider2D().center = GetEntityPosition();

	const double radians = launchRotation * M_PI / 180;
	const double xRotated = 1000.0 * std::cos(radians) - 0.0 * std::sin(radians);
	const double yRotated = 1000.0 * std::sin(radians) + 0.0 * std::cos(radians);
	
	SetObjectMovement(Vector2D<double>(xRotated, yRotated));
}


