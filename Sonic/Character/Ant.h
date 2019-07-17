#pragma once
#include "Enemy.h"


class Ant : public Enemy
{
private:

public:
	Ant(Camera& camera, Player& player);
	~Ant();

	void Update(const Peripheral& p);

	void Draw();
};

