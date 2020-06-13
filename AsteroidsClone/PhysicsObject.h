#pragma once
#include "Entity.h"
#include "Vector2D.h"

class PhysicsObject : Entity
{
public:
	PhysicsObject();
	explicit PhysicsObject(const Vector2D<double>& objectMovement);
	PhysicsObject(const Vector2D<double>& entityPosition, const Vector2D<double>& objectMovement);

	virtual void UpdatePhysics(float deltaTime);
	void ApplyForce(Vector2D<double> force);
	
private:
	Vector2D<double> m_ObjectMovement;
};
