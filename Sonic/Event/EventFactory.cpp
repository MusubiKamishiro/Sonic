#include "EventFactory.h"
#include "Coin.h"


EventFactory::EventFactory(const Camera& camera) : camera(camera)
{
}


EventFactory::~EventFactory()
{
}

std::shared_ptr<Event> EventFactory::Create(EventType type, const Vector2f & pos)
{
	if (type == EventType::coin)
	{
		return std::make_unique<Coin>(camera, pos);
	}
	return nullptr;
}
