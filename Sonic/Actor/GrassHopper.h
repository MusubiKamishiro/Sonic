#pragma once
#include "Enemy.h"


class GrassHopper : public Enemy
{
public:
	GrassHopper(Camera& camera, Player& player, Vector2f pos);
	~GrassHopper();

	void Update(const Peripheral& p)override final;

	void Draw()override final;

	void OnDead();
};

