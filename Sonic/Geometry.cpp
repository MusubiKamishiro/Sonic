#include "Geometry.h"
#include <DxLib.h>
#include <cmath>


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


void Rect::Draw(const unsigned int & color)
{
	DxLib::DrawBox(Left(), Top(), Right(), Bottom(), color, false);
}

void Circle::Draw(const unsigned int & color)
{
	DxLib::DrawCircle(pos.x, pos.y, radius, color, false);
}
