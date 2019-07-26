#include "SpawnerFactory.h"
#include "../Actor/Ant.h"
#include "../Actor/GrassHopper.h"
#include "../Spawner/OnetimeSpawner.h"


SpawnerFactory::SpawnerFactory(const Camera& camera, const Player& player) : camera(camera), player(player)
{
}


SpawnerFactory::~SpawnerFactory()
{
}

std::shared_ptr<Spawner> SpawnerFactory::Create(SpawnerType type, const Vector2f & pos)
{
	// ブロックタイプが一致すれば生成
	if (type == SpawnerType::ant)
	{
		auto org = std::make_shared<Ant>(camera, player, pos);
		return std::make_unique<OnetimeSpawner>(camera, pos, org);
	}
	else if (type == SpawnerType::grassHopper)
	{
		auto org = std::make_shared<GrassHopper>(camera, player, pos);
		return std::make_unique<OnetimeSpawner>(camera, pos, org);
	}
	
	return nullptr;
}
