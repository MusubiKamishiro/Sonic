#pragma once
#include "Enemy.h"


class Ant : public Enemy
{
private:

public:
	Ant(Camera& camera, Player& player, Vector2f pos);
	~Ant();

	void Update(const Peripheral& p)override final;

	void Draw()override final;
};

