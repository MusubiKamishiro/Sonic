#include "Spawner.h"
#include "Actor/Enemy.h"


std::shared_ptr<Enemy> Spawner::CreateClone()
{
	return original;
}

Spawner::Spawner(std::shared_ptr<Enemy> org)
{
}

Spawner::~Spawner()
{
}
