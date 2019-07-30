#include "OnetimeSpawner.h"
#include "../Camera.h"


OnetimeSpawner::OnetimeSpawner(const Camera & camera, const Vector2f & pos, std::shared_ptr<Enemy> org) : Spawner(org), camera(camera)
{
	original = org;
	this->pos = pos;
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
	// ˆê“xŽY‚ñ‚¾‚ç‚à‚¤¶‚Ü‚È‚¢‚æ
	if (isSpawned)
	{
		return;
	}

	// ƒJƒƒ‰‚Ì”ÍˆÍ“à‚Å‚ ‚ê‚Î¶‚Þ‚æ
	auto& range = camera.GetViewRange();
	if ((pos.x > range.Left()) && (pos.x < range.Right()))
	{
		enemies.push_back(Spawn());
		isSpawned = true;
	}
}
