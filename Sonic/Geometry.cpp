#include "Geometry.h"
#include <cmath>


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


Box::Box(Vector2f invecA, Vector2f invecB)
{
	dotA = invecA;
	dotB = invecB;
}

Box::Box(int ax, int ay, int bx, int by)
{
	dotA = Vector2f(ax, ay);
	dotB = Vector2f(bx, by);
}


bool Circle::HitCircle(Circle& c)
{
	Vector2f line = Vector2f(std::abs(c.pos.x - pos.x), std::abs(c.pos.y - pos.y));

	float distance = std::pow(line.x, 2.0) + std::pow(line.y, 2.0);
	distance = std::sqrt(distance);
	
	if(distance < radius + c.radius)
	{ 
		return true;
	}

	return false;
}
