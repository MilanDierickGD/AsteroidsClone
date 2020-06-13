#include "pch.h"
#include "Collidable.h"

Collidable::Collidable()
{
}

Collidable::Collidable(const AxisAlignedBoundingBox& collider2D): m_Collider2D(collider2D)
{
}

Collidable::Collidable(const Vector2D<double>& entityPosition, const AxisAlignedBoundingBox& collider2D):
	Entity(entityPosition),
	m_Collider2D(collider2D)
{
}

void Collidable::OnOverlap(Collidable other)
{
}

bool Collidable::Overlaps(Collidable other)
{
	if (m_Collider2D.Overlaps(other.GetCollider2D()))
	{
		OnOverlap(other);
		other.OnOverlap(*this);
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
