#pragma once
#include <memory>
#include <SDL_events.h>

#include "Collidable.h"
#include "PhysicsObject.h"
#include "Texture.h"

class ObjectManager;

class Player final : public Collidable, public PhysicsObject
{
public:
	explicit Player(std::string imagePath, int remainingLives);

	void OnOverlap(Collidable* other) override;
	void Update(float deltaTime) override;
	void Draw() override;
	
	// Simple event propagation from the main game loop
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
	
private:
	Texture m_PlayerTexture;
	double m_Rotation;
	int m_RemainingLives;

	void SpawnBullet();
	void Die();
};
