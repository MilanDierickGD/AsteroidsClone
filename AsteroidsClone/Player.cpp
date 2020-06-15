#include "pch.h"
#include "Player.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include "EnemyBullet.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "PlayerBullet.h"
#include "ThreatSpawner.h"
#include "utils.h"

Player::Player(const std::string imagePath, const int startingLives):
	m_PlayerTexture(Texture(imagePath)), m_StartingLives(startingLives),m_RemainingLives(startingLives)
{
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(0.0, 0.0),
										Vector2D<double>(m_PlayerTexture.GetWidth() / 2,
														m_PlayerTexture.GetHeight() / 2)));

	SetCollidableType(PlayerType);
	SetEntityPosition(Vector2D<double>(640.0, 400.0));
	m_Rotation = 0.0;
}

void Player::OnOverlap(Collidable* other)
{
	if (other->GetCollidableType() != PlayerBulletType)
	{
		Die();
	}
}

void Player::Update(const float deltaTime)
{
	const UINT8 *state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_LEFT])
	{
		m_Rotation += 250.0 * deltaTime;
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		m_Rotation -= 250.0 * deltaTime;
	}

	if (m_Rotation >= 360 || m_Rotation <= -360)
	{
		m_Rotation = 0;
	}

	
	if (state[SDL_SCANCODE_UP])
	{
		const double radians = m_Rotation * M_PI / 180;
		const double xRotated = 500.0 * deltaTime * std::cos(radians) - 0.0 * std::sin(radians);
		const double yRotated = 500.0 * deltaTime * std::sin(radians) + 0.0 * std::cos(radians);
		ApplyForce(Vector2D<double>(xRotated, yRotated));
	}

	if (state[SDL_SCANCODE_DOWN])
	{
		const double radians = m_Rotation * M_PI / 180;
		const double xRotated = -500.0 * deltaTime * std::cos(radians) - 0.0 * std::sin(radians);
		const double yRotated = -500.0 * deltaTime * std::sin(radians) + 0.0 * std::sin(radians);
		ApplyForce(Vector2D<double>(xRotated, yRotated));
	}
	
	UpdatePhysics(deltaTime);
	GetCollider2D().center = GetEntityPosition();

	if (GetObjectMovement().x > 350)
	{
		GetObjectMovement().x = 350;
	}
	else if (GetObjectMovement().x < -350)
	{
		GetObjectMovement().x = -350;
	}
	if (GetObjectMovement().y > 350)
	{
		GetObjectMovement().y = 350;
	}
	else if (GetObjectMovement().y < -350)
	{
		GetObjectMovement().y = -350;
	}
}

void Player::Draw()
{
	glPushMatrix();
	glTranslatef(static_cast<GLfloat>(GetEntityPosition().x + GetCollider2D().halfSize.x), static_cast<GLfloat>(GetEntityPosition().y + GetCollider2D().halfSize.y), 0);
	glRotatef(static_cast<GLfloat>(m_Rotation), 0, 0, 1);
	m_PlayerTexture.Draw(Point2D<float>{
        static_cast<float>(-GetCollider2D().halfSize.x), static_cast<float>(-GetCollider2D().halfSize.y)
    });
	glPopMatrix();
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.scancode == SDL_SCANCODE_SPACE)
	{
		SpawnBullet();
	}
}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Player::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Player::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	SpawnBullet();
}

void Player::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Player::Reset()
{
	ThreatSpawner::GetInstance().ResetThreats();
	GetEntityPosition().x = 1280.0 / 2 - GetCollider2D().halfSize.x;
	GetEntityPosition().y = 800.0 / 2 - GetCollider2D().halfSize.y;
	m_Rotation = 0;
	GetObjectMovement().Zero();
	m_RemainingLives = m_StartingLives;
}

int Player::GetRemainingLives() const
{
	return m_RemainingLives;
}

void Player::AddLife()
{
	++m_RemainingLives;
}

void Player::SpawnBullet()
{
	int counter = 0;
	std::for_each(std::begin(ObjectManager::GetInstance().GetCollidables()), std::end(ObjectManager::GetInstance().GetCollidables()), [&counter](Collidable* collidable)
	{
		if (collidable->GetCollidableType() == PlayerBulletType)
		{
			++counter;
		}
	});

	if (counter < 4)
	{
		ObjectManager::GetInstance().AddCollidable(new PlayerBullet("Resources/PlayerBulletTexture.png", GetEntityPosition() + GetCollider2D().halfSize, m_Rotation));
	}
}

void Player::Die()
{		
	if (--m_RemainingLives == 0)
	{
		GameManager::GetInstance().SetGameState(GameOver);
	}

	ThreatSpawner::GetInstance().ResetThreats();
	ObjectManager::GetInstance().PurgeAllParticles();
	GetEntityPosition().x = 1280.0 / 2 - GetCollider2D().halfSize.x;
	GetEntityPosition().y = 800.0 / 2 - GetCollider2D().halfSize.y;
	m_Rotation = 0;
	GetObjectMovement().Zero();
}
