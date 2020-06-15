#pragma once
#include <chrono>

#include "PhysicsObject.h"
#include "Texture.h"

class Particle final : public PhysicsObject
{
public:
	Particle(Vector2D<double> spawnPosition, Vector2D<double> objectMovement);

	void Update(float deltaTime) override;
	void Draw() override;

	bool IsDisabled() const;

private:
	Texture m_ParticleTexture;
	float m_Rotation;
	float m_RotationSpeed;
	bool m_Disabled;
	std::chrono::steady_clock::time_point m_ExistenceTimer;
};
