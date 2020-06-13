#pragma once
#include "Vector2D.h"

class Entity
{
public:
	virtual ~Entity() = default;
	Entity();
	explicit Entity(const Vector2D<double>& entityPosition);

	Vector2D<double>& GetEntityPosition();
	void SetEntityPosition(const Vector2D<double>& entityPosition);
	
private:
	Vector2D<double> m_EntityPosition;
};
