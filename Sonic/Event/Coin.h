#pragma once
#include "Event.h"


class Coin : public Event
{
public:
	Coin(const Camera& camera, const Vector2f& pos);
	~Coin();

	void Update(const Peripheral& p)override final;
	void Draw()override final;
	void OnCollision(Actor& actor, const Rect& col)override final;
	void OnDead();
};

