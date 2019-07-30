#include "Spawner.h"
#include "../Actor/Enemy.h"


std::shared_ptr<Enemy> Spawner::CreateClone()
{
	return original->MakeClone();
}

Spawner::Spawner(std::shared_ptr<Enemy> org)
{
	isSpawned = false;
}

Spawner::~Spawner()
{
}

Vector2f Spawner::GetPos() const
{
	return pos;
}
