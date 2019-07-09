#include "Collider.h"
#include <cmath>


Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::IsCollided(const Rect& ra, const Rect& rb)
{
	auto cx = std::abs(ra.center.x - rb.center.x);
	auto cy = std::abs(ra.center.y - rb.center.y);
	auto w = (ra.Width() + rb.Width()) / 2;
	auto h = (ra.Height() + rb.Height()) / 2;

	return ((cx < w) && (cy < h));

	return ((std::abs(ra.center.x - rb.center.x) < (ra.Width() + rb.Width()) / 2)) && ((std::abs(ra.center.y - rb.center.y) < (ra.Height() + rb.Height()) / 2));
}
