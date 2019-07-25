#include "OnetimeSpawner.h"



OnetimeSpawner::OnetimeSpawner(const Camera & camera, const Vector2f & pos, std::shared_ptr<Enemy> org) : Spawner(org), camera(camera)
{
}

OnetimeSpawner::~OnetimeSpawner()
{
}

std::shared_ptr<Enemy> OnetimeSpawner::Spawn()
{
	return std::shared_ptr<Enemy>();
}

void OnetimeSpawner::Update(std::vector<std::shared_ptr<Actor>>& actors)
{

}
