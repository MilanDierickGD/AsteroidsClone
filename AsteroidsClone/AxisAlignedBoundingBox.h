#pragma once
#include "Vector2D.h"

struct AxisAlignedBoundingBox
{
	AxisAlignedBoundingBox();
	AxisAlignedBoundingBox(const Vector2D<double>& center, const Vector2D<double>& halfSize);

	bool Overlaps(AxisAlignedBoundingBox other) const;
	
	Vector2D<double> center;
	Vector2D<double> halfSize;
};
