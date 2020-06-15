#include "pch.h"
#include "Particle.h"

Particle::Particle(const Vector2D<double> spawnPosition, const Vector2D<double> objectMovement) : m_Disabled(false),
																								m_ExistenceTimer(
																									std::chrono::steady_clock::now())
{
	m_ParticleTexture = Texture("Resources/ParticleTexture.png");
	SetObjectMovement(objectMovement);
	SetEntityPosition(spawnPosition);
	m_RotationSpeed = std::rand() % 400 - 200;
}

void Particle::Update(const float deltaTime)
{
	const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	const float elapsedSeconds = std::chrono::duration<float>(currentTime - m_ExistenceTimer).count();

	if (elapsedSeconds > 2)
	{
		m_Disabled = true;
	}
	
	UpdatePhysics(deltaTime);
	
	m_Rotation += m_RotationSpeed * deltaTime;

	if (m_Rotation >= 360 || m_Rotation <= -360)
	{
		m_Rotation = 0;
	}
}

void Particle::Draw()
{
	glPushMatrix();
	glTranslatef(GetEntityPosition().x, GetEntityPosition().y, 0);
	glRotatef(m_Rotation, 0, 0, 1);
	m_ParticleTexture.Draw(Point2D<float>(0.0f, 0.0f));
	glPopMatrix();
}

bool Particle::IsDisabled() const
{
	return m_Disabled;
}
