#include "pch.h"
#include "SmallAsteroid.h"

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
	if (other->GetCollidableType() == BulletType)
	{
		SetDisabled(true);
	}
}

void SmallAsteroid::SpawnAsteroid(Vector2D<double> parentAsteroidPosition)
{
	SetEntityPosition(parentAsteroidPosition);
	GetCollider2D().center = parentAsteroidPosition;
	SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
}
