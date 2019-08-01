#include "Event.h"



Event::Event(const Camera& camera, const Vector2f& pos) : Actor(camera)
{
}


Event::~Event()
{
}

bool Event::GetIsAvailable() const
{
	return isAvailable;
}
