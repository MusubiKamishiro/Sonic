#pragma once
#include <memory>
#include "../Geometry.h"

class Camera;
class Event;

// ステージに設置するイベントの種類
enum EventType
{
	coin,	// コイン
};

class EventFactory
{
private:
	const Camera& camera;

public:
	EventFactory(const Camera& camera);
	~EventFactory();

	std::shared_ptr<Event> Create(EventType type, const Vector2f& pos);
};

