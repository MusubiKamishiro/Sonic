#pragma once
#include "Actor.h"

class Player;

///“GŠî’êƒNƒ‰ƒX
class Enemy : public Actor
{
protected:
	const Player& player;
public:
	Enemy(Camera& camera, Player& player);
	~Enemy();
};

