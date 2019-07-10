#include "Geometry.h"
#include <DxLib.h>
#include <cmath>


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


Rect Rect::CreateOverlappedRangeRect(const Rect & rcA, const Rect & rcB)
{
	int left = max(rcA.Left(), rcB.Left());
	int right = min(rcA.Right(), rcB.Right());
	int bottom = min(rcA.Bottom(), rcB.Bottom());
	int top = max(rcA.Top(), rcB.Top());

	Rect rc;
	rc.size.width = right - left;
	rc.size.height = bottom - top;
	rc.center.x = rc.size.width / 2 + left;
	rc.center.y = rc.size.height / 2 + top;

	return rc;
}

void Rect::Draw(const unsigned int & color)
{
	DxLib::DrawBox(Left(), Top(), Right(), Bottom(), color, false);
}

void Circle::Draw(const unsigned int & color)
{
	DxLib::DrawCircle(pos.x, pos.y, radius, color, false);
}
