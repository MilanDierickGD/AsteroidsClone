#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "ObjectManager.h"

#include <memory>

Player::Player(const std::string imagePath, const int remainingLives):
	m_PlayerTexture(Texture(imagePath)), m_RemainingLives(remainingLives)
{
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<double>(900.0, 600.0),
										Vector2D<double>(m_PlayerTexture.GetWidth() / 2,
														m_PlayerTexture.GetHeight() / 2)));

	SetCollidableType(PlayerType);
	SetEntityPosition(Vector2D<double>(900.0, 600.0));
	m_Rotation = 0.0;
}

void Player::OnOverlap(Collidable* other)
{
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
		const double xRotated = 5.0 * std::cos(radians) - 0.0 * std::sin(radians);
		const double yRotated = 5.0 * std::sin(radians) + 0.0 * std::cos(radians);
		ApplyForce(Vector2D<double>(xRotated, yRotated));
	}

	if (state[SDL_SCANCODE_S])
	{
		const double radians = m_Rotation * M_PI / 180;
		const double xRotated = -5.0 * std::cos(radians) - 0.0 * std::sin(radians);
		const double yRotated = -5.0 * std::sin(radians) + 0.0 * std::sin(radians);
		ApplyForce(Vector2D<double>(xRotated, yRotated));
	}
	
	UpdatePhysics(deltaTime);
	GetCollider2D().center = GetEntityPosition();
}

void Player::Draw()
{
	glPushMatrix();
	glTranslatef(static_cast<GLfloat>(GetEntityPosition().x), static_cast<GLfloat>(GetEntityPosition().y), 0);
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

void Player::SpawnBullet()
{
	ObjectManager::GetInstance().AddCollidable(new Bullet("Resources/BulletTexture.png", GetEntityPosition(), m_Rotation));
}