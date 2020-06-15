#include "pch.h"
#include "BigAsteroid.h"


#include "Collidable.h"
#include "GameManager.h"
#include "MediumAsteroid.h"

BigAsteroid::BigAsteroid(const std::string imagePath)
{
	m_BigAsteroidTexture = Texture(imagePath);
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
										Vector2D<double>(m_BigAsteroidTexture.GetWidth() / 2,
														m_BigAsteroidTexture.GetHeight() / 2)));

	SetCollidableType(BigAsteroidType);
	SetDisabled(false);
	SpawnAsteroid();
}

void BigAsteroid::Update(const float deltaTime)
{
	UpdatePhysics(deltaTime);
	GetCollider2D().center.x = GetEntityPosition().x + GetCollider2D().halfSize.x;
	GetCollider2D().center.y = GetEntityPosition().y + GetCollider2D().halfSize.y;
}

void BigAsteroid::Draw()
{
	// TODO: Make the asteroid spin
	m_BigAsteroidTexture.Draw(Point2D<float>(static_cast<float>(GetEntityPosition().x),
										static_cast<float>(GetEntityPosition().y)));
}

void BigAsteroid::OnOverlap(Collidable* other)
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
		GameManager::GetInstance().AddScore(20);
		break;
	default:
        break;
	}
}

void BigAsteroid::Split()
{	
	MediumAsteroid* mediumAsteroid1 = new MediumAsteroid("Resources/MediumAsteroidTexture.png",
													GetEntityPosition());
	MediumAsteroid* mediumAsteroid2 = new MediumAsteroid("Resources/MediumAsteroidTexture.png",
													GetEntityPosition());
	ObjectManager::GetInstance().AddCollidable(mediumAsteroid1);
	ObjectManager::GetInstance().AddCollidable(mediumAsteroid2);

	for	(size_t counter = 0; counter < 50; ++counter)
	{
		ObjectManager::GetInstance().AddParticle(new Particle(GetEntityPosition() + GetCollider2D().halfSize, Vector2D<double>(std::rand() % 100, std::rand() % 100)));
	}
}

void BigAsteroid::SpawnAsteroid()
{
	const int spawnFace = std::rand() % 4;

	switch (spawnFace)
	{
		case 0:
			SetEntityPosition(Vector2D<double>(std::rand() % 1280 , 800.0));
			GetCollider2D().center = GetEntityPosition();
			SetObjectMovement(Vector2D<double>(std::rand() % 100 - 50, std::rand() % 100 - 50));
			break;
		case 1:
			SetEntityPosition(Vector2D<double>(0.0, std::rand() % 800));
			GetCollider2D().center = GetEntityPosition();
			SetObjectMovement(Vector2D<double>(std::rand() % 100 - 50, std::rand() % 100 - 50));
			break;
		case 2:
			SetEntityPosition(Vector2D<double>(std::rand() % 1280 , 0.0));
			GetCollider2D().center = GetEntityPosition();
			SetObjectMovement(Vector2D<double>(std::rand() % 100 - 50, std::rand() % 100 - 50));
			break;
		case 3:
			SetEntityPosition(Vector2D<double>(1280.0, std::rand() % 800));
			GetCollider2D().center = GetEntityPosition();
			SetObjectMovement(Vector2D<double>(std::rand() % 100 - 50, std::rand() % 100 - 50));
			break;
		default:
			break;	
	}
}
