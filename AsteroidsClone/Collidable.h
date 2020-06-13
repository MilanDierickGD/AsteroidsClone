#pragma once
#include "AxisAlignedBoundingBox.h"
#include "Entity.h"

class Collidable : Entity
{
public:
	Collidable();
	explicit Collidable(const AxisAlignedBoundingBox& collider2D);
	Collidable(const Vector2D<double>& entityPosition, const AxisAlignedBoundingBox& collider2D);

	virtual void OnOverlap(Collidable other);
	bool Overlaps(Collidable other);

	AxisAlignedBoundingBox& GetCollider2D();
	void SetCollider2D(const AxisAlignedBoundingBox& collider2D);
private:
	AxisAlignedBoundingBox m_Collider2D;
};
