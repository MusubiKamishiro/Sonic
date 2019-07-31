#pragma once
#include <memory>
#include "../Geometry.h"

class Player;
class Camera;
class Spawner;


// ステージに設置するブロックの種類
enum SpawnerType
{
	ant,
	grassHopper,
};

class SpawnerFactory
{
private:
	const Player& player;
	const Camera& camera;

public:
	SpawnerFactory(const Camera& camera, const Player& player);
	~SpawnerFactory();

	// ブロックを生成する
	// @param type どの種別のブロックを生成するか
	// @param pos どこに生成するか
	std::shared_ptr<Spawner> Create(SpawnerType type, const Vector2f& pos);
};

