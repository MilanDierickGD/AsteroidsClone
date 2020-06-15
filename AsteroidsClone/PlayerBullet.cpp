#include "pch.h"
#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const std::string imagePath, const Vector2D<double> spawnPosition, const double launchRotation): m_DeathTimer(std::chrono::steady_clock::now())
{
	m_BulletTexture = Texture(imagePath);
	
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
                                Vector2D<double>(m_BulletTexture.GetWidth() / 2,
                                                m_BulletTexture.GetHeight() / 2)));

	SetCollidableType(PlayerBulletType);
	SetDisabled(false);
	SpawnBullet(spawnPosition, launchRotation);
}

void PlayerBullet::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	GetCollider2D().center = GetEntityPosition();

	const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	const float elapsedSeconds = std::chrono::duration<float>(currentTime - m_DeathTimer).count();

	if (elapsedSeconds > 2)
	{
		SetDisabled(true);
	}
}

void PlayerBullet::Draw()
{
	m_BulletTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x), static_cast<float>(GetEntityPosition().y)));
}

void PlayerBullet::OnOverlap(Collidable* other)
{
	if (other->GetCollidableType() != PlayerBulletType || other->GetCollidableType() != EnemyBulletType || other->GetCollidableType() != PlayerType)
	{
		SetDisabled(true);
	}
}

void PlayerBullet::SpawnBullet(const Vector2D<double> spawnPosition, const double launchRotation)
{
	SetEntityPosition(Vector2D<double>(spawnPosition.x - GetCollider2D().halfSize.x + std::cos(launchRotation * M_PI / 180) * 60,
                                    spawnPosition.y - GetCollider2D().halfSize.y + std::sin(launchRotation * M_PI / 180) * 60));
	
	GetCollider2D().center = GetEntityPosition() + GetCollider2D().halfSize;

	const double radians = launchRotation * M_PI / 180;
	const double xRotated = 1000.0 * std::cos(radians) - 0.0 * std::sin(radians);
	const double yRotated = 1000.0 * std::sin(radians) + 0.0 * std::cos(radians);
	
	SetObjectMovement(Vector2D<double>(xRotated, yRotated));
}
