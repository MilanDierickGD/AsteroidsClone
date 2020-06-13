#pragma once
#include "Vector2D.h"

struct AxisAlignedBoundingBox
{
	AxisAlignedBoundingBox();
	AxisAlignedBoundingBox(const Vector2D<float>& center, const Vector2D<float>& halfSize);

	bool Overlaps(AxisAlignedBoundingBox other) const;
	
	Vector2D<float> center;
	Vector2D<float> halfSize;
};
