#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;


class Player : public Actor
{
private:
	void Move(const Peripheral& p);

public:
	Player(Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw()override final;
};

