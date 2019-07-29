#include "OnetimeSpawner.h"
#include "../Camera.h"


OnetimeSpawner::OnetimeSpawner(const Camera & camera, const Vector2f & pos, std::shared_ptr<Enemy> org) : Spawner(org), camera(camera)
{
	original = org;
	this->pos = pos;
	count = 0;
}

OnetimeSpawner::~OnetimeSpawner()
{
}

std::shared_ptr<Enemy> OnetimeSpawner::Spawn()
{
	return CreateClone();
}

void OnetimeSpawner::Update(std::vector<std::shared_ptr<Enemy>>& enemies)
{
	auto& range = camera.GetViewRange();

	if ((pos.x > range.Left()) && (pos.x < range.Right()))
	{
		if (count >= 100)
		{
			enemies.push_back(Spawn());
			count = 0;
		}
		++count;
	}

}
