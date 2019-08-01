#pragma once
#include "Event.h"


class Coin : public Event
{
private:
	int coinSound;

public:
	Coin(const Camera& camera, const Vector2f& pos);
	~Coin();

	void Update(const Peripheral& p)override final;
	void Draw()override final;
	void OnDead();
};

