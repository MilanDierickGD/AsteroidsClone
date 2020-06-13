#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const Vector2D<double>& entityPosition): m_EntityPosition(entityPosition)
{
}

Vector2D<double>& Entity::GetEntityPosition()
{
	return m_EntityPosition;
}

void Entity::SetEntityPosition(const Vector2D<double>& entityPosition)
{
	m_EntityPosition = entityPosition;
}
