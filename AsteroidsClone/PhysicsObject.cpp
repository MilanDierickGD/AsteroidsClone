#include "pch.h"
#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : Entity()/*, m_ObjectMovement(Vector2D<double>(0.0, 0.0))*/
{
}

PhysicsObject::PhysicsObject(const Vector2D<double>& objectMovement): m_ObjectMovement(objectMovement)
{
}

PhysicsObject::PhysicsObject(const Vector2D<double>& entityPosition, const Vector2D<double>& objectMovement):
	Entity(entityPosition),
	m_ObjectMovement(objectMovement)
{
}

void PhysicsObject::UpdatePhysics(const float deltaTime)
{
	GetEntityPosition().x += m_ObjectMovement.x * deltaTime;
	GetEntityPosition().y += m_ObjectMovement.y * deltaTime;
}

void PhysicsObject::ApplyForce(const Vector2D<double> force)
{
	m_ObjectMovement += force;
}

Vector2D<double>& PhysicsObject::GetObjectMovement()
{
	return m_ObjectMovement;
}

void PhysicsObject::SetObjectMovement(const Vector2D<double>& objectMovement)
{
	m_ObjectMovement = objectMovement;
}
