#pragma once
#include "Actor.h"

class Player;

///�G���N���X
class Enemy : public Actor
{
protected:
	const Player& player;
public:
	Enemy(Camera& camera, Player& player);
	~Enemy();
};

