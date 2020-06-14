#include "pch.h"
#include "Collidable.h"

Collidable::Collidable()
= default;

Collidable::Collidable(const AxisAlignedBoundingBox& collider2D, const CollidableType type): m_Collider2D(collider2D),
																							m_CollidableType(type),
																							m_Disabled(false)
{
}

void Collidable::OnOverlap(Collidable* other)
{
}

bool Collidable::Overlaps(Collidable* other)
{
	if (m_Disabled)
	{
		return false;
	}
	if (m_Collider2D.Overlaps(other->GetCollider2D()))
	{
		OnOverlap(other);
		other->OnOverlap(this);
		return true;
	}
	
	return false;
}

AxisAlignedBoundingBox& Collidable::GetCollider2D()
{
	return m_Collider2D;
}

void Collidable::SetCollider2D(const AxisAlignedBoundingBox& collider2D)
{
	m_Collider2D = collider2D;
}

CollidableType& Collidable::GetCollidableType()
{
	return m_CollidableType;
}

void Collidable::SetCollidableType(const CollidableType collidableType)
{
	m_CollidableType = collidableType;
}

bool& Collidable::IsDisabled()
{
	return m_Disabled;
}

void Collidable::SetDisabled(const bool disabled)
{
	m_Disabled = disabled;
}
