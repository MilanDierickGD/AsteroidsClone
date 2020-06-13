#include "pch.h"
#include "Player.h"

Player::Player(const std::string imagePath, const int remainingLives): m_PlayerTexture(Texture(imagePath)),
																		m_RemainingLives(remainingLives)
{
	SetCollider2D(AxisAlignedBoundingBox(Vector2D<float>(200.0f, 200.0f),
										Vector2D<float>(m_PlayerTexture.GetWidth() / 2,
														m_PlayerTexture.GetHeight() / 2)));
}

void Player::OnOverlap(Collidable other)
{
}

void Player::Update(float deltaTime)
{
}

void Player::UpdatePhysics(float deltaTime)
{
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Player::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Player::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Player::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}
