#pragma once
#include "../Actor/Actor.h"
#include "../Geometry.h"


class Event : public Actor
{
protected:
	bool isAvailable = true;

public:
	Event(const Camera& camera, const Vector2f& pos);
	virtual ~Event();
	bool GetIsAvailable()const;
//	virtual EventType GetType()const = 0;
	virtual void Update(const Peripheral& p) = 0;
	virtual void Draw() = 0;
};

