#include "pch.h"
#include "Entity.h"

Entity::Entity() : m_EntityPosition(Vector2D<double>(0.0, 0.0))
{
}

Entity::Entity(const Vector2D<double>& entityPosition): m_EntityPosition(entityPosition)
{
}

void Entity::Update(const float deltaTime)
{
}

void Entity::Draw()
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
