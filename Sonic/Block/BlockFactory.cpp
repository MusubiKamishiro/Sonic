#include "BlockFactory.h"
#include "Brick.h"
#include "Slide.h"
#include "Lift.h"
#include "Pendulum.h"


BlockFactory::BlockFactory(const Camera& camera) : camera(camera)
{
}


BlockFactory::~BlockFactory()
{
}

std::shared_ptr<Block> BlockFactory::Create(BlockType type, const Vector2& pos, unsigned int runLength)
{
	// ブロックタイプが一致すれば生成
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(pos, camera);
	}
	else if (type == BlockType::slide)
	{
		return std::make_unique<Slide>(pos, camera, runLength);
	}
	else if (type == BlockType::lift)
	{
		return std::make_unique<Lift>(pos, camera, runLength);
	}
	else if (type == BlockType::pendulum)
	{
		return std::make_unique<Pendulum>(pos, camera, runLength);
	}
	return nullptr;
}
