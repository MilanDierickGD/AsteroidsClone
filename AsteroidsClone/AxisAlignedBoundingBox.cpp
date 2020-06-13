#include "pch.h"
#include "AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox()
{
	center = Vector2D<float>(0.0f, 0.0f);
	halfSize = Vector2D<float>(0.0f, 0.0f);
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector2D<float>& center, const Vector2D<float>& halfSize):
	center(center),
	halfSize(halfSize)
{
	this->center += halfSize;
}

bool AxisAlignedBoundingBox::Overlaps(const AxisAlignedBoundingBox other) const
{
	if (std::abs(center.x - other.center.x) > halfSize.x + other.halfSize.x) return false;
	if (std::abs(center.y - other.center.y) > halfSize.y + other.halfSize.y) return false;
	return true;
}
