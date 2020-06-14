#pragma once

#include "AxisAlignedBoundingBox.h"
#include "Entity.h"

enum CollidableType
{
	BigAsteroidType, MediumAsteroidType, SmallAsteroidType, PlayerBulletType, EnemyBulletType, EnemyType, SuicidalEnemyType, PlayerType
};

class Collidable : virtual public Entity
{
public:
	Collidable();
	explicit Collidable(const AxisAlignedBoundingBox& collider2D, CollidableType type);
	
	virtual void OnOverlap(Collidable* other);
	bool Overlaps(Collidable* other);

	AxisAlignedBoundingBox& GetCollider2D();
	void SetCollider2D(const AxisAlignedBoundingBox& collider2D);
	CollidableType& GetCollidableType();
	void SetCollidableType(const CollidableType collidableType);
	bool& IsDisabled();
	void SetDisabled(const bool disabled);
	
private:
	AxisAlignedBoundingBox m_Collider2D;
	CollidableType m_CollidableType;
	bool m_Disabled;
};
