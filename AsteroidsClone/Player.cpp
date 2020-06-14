#include "pch.h"
#include "Player.h"

#include <iostream>

#include "EnemyBullet.h"
#include "ObjectManager.h"

#include <memory>


#include "PlayerBullet.h"
#include "ThreatSpawner.h"
#include "utils.h"

Player::Player(const std::string imagePath, const int remainingLives):
	m_PlayerTexture(Texture(imagePath)), m_RemainingLives(remainingLives)
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

	if (state[SDL_SCANCODE_A])
	{
		m_Rotation += 200.0 * deltaTime;
	}

	if (state[SDL_SCANCODE_D])
	{
		m_Rotation -= 200.0 * deltaTime;
	}

	if (m_Rotation >= 360 || m_Rotation <= -360)
	{
		m_Rotation = 0;
	}

	
	if (state[SDL_SCANCODE_W])
	{
		const double radians = m_Rotation * M_PI / 180;
		const double xRotated = 400.0 * deltaTime * std::cos(radians) - 0.0 * std::sin(radians);
		const double yRotated = 400.0 * deltaTime * std::sin(radians) + 0.0 * std::cos(radians);
		ApplyForce(Vector2D<double>(xRotated, yRotated));
	}

	if (state[SDL_SCANCODE_S])
	{
		const double radians = m_Rotation * M_PI / 180;
		const double xRotated = -400.0 * deltaTime * std::cos(radians) - 0.0 * std::sin(radians);
		const double yRotated = -400.0 * deltaTime * std::sin(radians) + 0.0 * std::sin(radians);
		ApplyForce(Vector2D<double>(xRotated, yRotated));
	}
	
	UpdatePhysics(deltaTime);
	GetCollider2D().center = GetEntityPosition();

	if (GetObjectMovement().x > 300)
	{
		GetObjectMovement().x = 300;
	}
	else if (GetObjectMovement().x < -300)
	{
		GetObjectMovement().x = -300;
	}
	if (GetObjectMovement().y > 300)
	{
		GetObjectMovement().y = 300;
	}
	else if (GetObjectMovement().y < -300)
	{
		GetObjectMovement().y = -300;
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

	utils::DrawRect(Point2f(static_cast<float>(GetEntityPosition().x), static_cast<float>(GetEntityPosition().y)), m_PlayerTexture.GetWidth(), m_PlayerTexture.GetHeight(), 1.0f);
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

void Player::SpawnBullet()
{
	ObjectManager::GetInstance().AddCollidable(new PlayerBullet("Resources/PlayerBulletTexture.png", GetEntityPosition() + GetCollider2D().halfSize, m_Rotation));
}

void Player::Die()
{
	if (--m_RemainingLives == 0)
	{
		//GameOver();
	}

	ThreatSpawner::GetInstance().ResetThreats();
	GetEntityPosition().x = 1280.0 / 2 - GetCollider2D().halfSize.x;
	GetEntityPosition().y = 800.0 / 2 - GetCollider2D().halfSize.y;
	m_Rotation = 0;
	GetObjectMovement().Zero();
}
