#pragma once
#include "Enemy.h"


class Ant : public Enemy
{
private:

public:
	Ant(const Camera& camera, const Player& player, Vector2f pos);
	~Ant();

	std::shared_ptr<Enemy> MakeClone();

	void Update(const Peripheral& p)override final;

	void Draw()override final;

	void OnDead();
};

