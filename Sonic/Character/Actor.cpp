#include "Actor.h"



Actor::Actor(Camera& camera) : camera(camera)
{
}


Actor::~Actor()
{
}

Vector2f Actor::GetPos() const
{
	return pos;
}
