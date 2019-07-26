#pragma once
#include "Enemy.h"


class GrassHopper : public Enemy
{
public:
	GrassHopper(const Camera& camera, const Player& player, Vector2f pos);
	~GrassHopper();

	std::shared_ptr<Enemy> MakeClone();

	void Update(const Peripheral& p)override final;

	void Draw()override final;

	void OnDead();
};

