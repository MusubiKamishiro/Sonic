#include "InfiniteSpawner.h"
#include "../Camera.h"


InfiniteSpawner::InfiniteSpawner(const Camera & camera, const Vector2f & pos, std::shared_ptr<Enemy> org) : Spawner(org), camera(camera)
{
	original = org;
	this->pos = pos;
	count = 0;
}


InfiniteSpawner::~InfiniteSpawner()
{
}

std::shared_ptr<Enemy> InfiniteSpawner::Spawn()
{
	return CreateClone();
}

void InfiniteSpawner::Update(std::vector<std::shared_ptr<Enemy>>& enemies)
{
	// ƒJƒƒ‰‚Ì”ÍˆÍ“à‚Å‚ ‚ê‚Î¶‚Þ‚æ
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
