#pragma once
#include "Geometry.h"

class Collider
{
private:

public:
	Collider();
	~Collider();

	static bool IsCollided(const Rect& ra, const Rect& rb);
};

