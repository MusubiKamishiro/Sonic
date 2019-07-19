#pragma once
#include "Actor.h"

class Player;

///“GŠî’êƒNƒ‰ƒX
class Enemy : public Actor
{
protected:
	const Player& player;
public:
	Enemy(Camera& camera, Player& player, Vector2f& pos);
	~Enemy();

	virtual void Update(const Peripheral& p) = 0;

	virtual void Draw() = 0;
};

