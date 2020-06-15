#include "pch.h"
#include "MediumAsteroid.h"

#include <memory>


#include "GameManager.h"
#include "SmallAsteroid.h"

MediumAsteroid::MediumAsteroid(const std::string imagePath,
								const Vector2D<double> parentAsteroidPosition)
{
	m_MediumAsteroidTexture = Texture(imagePath);
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
                                Vector2D<double>(m_MediumAsteroidTexture.GetWidth() / 2,
                                                m_MediumAsteroidTexture.GetHeight() / 2)));

	SetDisabled(false);
	SetCollidableType(MediumAsteroidType);
	SpawnAsteroid(parentAsteroidPosition);
}

void MediumAsteroid::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	GetCollider2D().center.x = GetEntityPosition().x + GetCollider2D().halfSize.x;
	GetCollider2D().center.y = GetEntityPosition().y + GetCollider2D().halfSize.y;
}

void MediumAsteroid::Draw()
{
	m_MediumAsteroidTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x),
                                    static_cast<float>(GetEntityPosition().y)));
}

void MediumAsteroid::OnOverlap(Collidable* other)
{
	switch (other->GetCollidableType())
	{
	case EnemyBulletType: case EnemyType:
		Split();
		SetDisabled(true);
		break;
	case PlayerBulletType:
		Split();
        SetDisabled(true);
		GameManager::GetInstance().AddScore(50);
		break;
	default:
        break;
	}
}

void MediumAsteroid::Split()
{
	SmallAsteroid* smallAsteroid1 = new SmallAsteroid("Resources/SmallAsteroidTexture.png",
                                                GetEntityPosition());
	SmallAsteroid* smallAsteroid2 = new SmallAsteroid("Resources/SmallAsteroidTexture.png",
                                                    GetEntityPosition());
	ObjectManager::GetInstance().AddCollidable(smallAsteroid1);
	ObjectManager::GetInstance().AddCollidable(smallAsteroid2);
}

void MediumAsteroid::SpawnAsteroid(const Vector2D<double> parentAsteroidPosition)
{
	SetEntityPosition(parentAsteroidPosition);
	GetCollider2D().center = parentAsteroidPosition;
	SetObjectMovement(Vector2D<double>(std::rand() % 200 - 100, std::rand() % 200 - 100));
}
