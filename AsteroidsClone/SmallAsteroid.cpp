#include "pch.h"
#include "SmallAsteroid.h"

#include "GameManager.h"

SmallAsteroid::SmallAsteroid(const std::string imagePath,
							const Vector2D<double> parentAsteroidPosition)
{
	m_SmallAsteroidTexture = Texture(imagePath);

	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
                            Vector2D<double>(m_SmallAsteroidTexture.GetWidth() / 2,
                                            m_SmallAsteroidTexture.GetHeight() / 2)));

	SetDisabled(false);
	SetCollidableType(SmallAsteroidType);
	SpawnAsteroid(parentAsteroidPosition);
}

void SmallAsteroid::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	GetCollider2D().center.x = GetEntityPosition().x + GetCollider2D().halfSize.x;
	GetCollider2D().center.y = GetEntityPosition().y + GetCollider2D().halfSize.y;
}

void SmallAsteroid::Draw()
{
	m_SmallAsteroidTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x),
                                static_cast<float>(GetEntityPosition().y)));
}

void SmallAsteroid::OnOverlap(Collidable* other)
{
	switch (other->GetCollidableType())
	{
	case EnemyBulletType: case EnemyType:
		Destroy();
		break;
	case PlayerBulletType:
		Destroy();
		GameManager::GetInstance().AddScore(100);
		break;
	default:
        break;
	}
}

void SmallAsteroid::SpawnAsteroid(const Vector2D<double> parentAsteroidPosition)
{
	SetEntityPosition(parentAsteroidPosition);
	GetCollider2D().center = parentAsteroidPosition;
	SetObjectMovement(Vector2D<double>(std::rand() % 600 - 300, std::rand() % 600 - 300));
}

void SmallAsteroid::Destroy()
{
	SetDisabled(true);
	
	for	(size_t counter = 0; counter < 15; ++counter)
	{
		ObjectManager::GetInstance().AddParticle(new Particle(GetEntityPosition() + GetCollider2D().halfSize, Vector2D<double>(std::rand() % 50, std::rand() % 50)));
	}
}
