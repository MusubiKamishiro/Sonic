#include "BlockFactory.h"
#include "Brick.h"
#include "Slide.h"
#include "Lift.h"


BlockFactory::BlockFactory(const Camera& camera) : camera(camera)
{
}


BlockFactory::~BlockFactory()
{
}

std::shared_ptr<Block> BlockFactory::Create(BlockType type, const Vector2& pos)
{
	// ブロックタイプが一致すれば生成
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(pos, camera);
	}
	else if (type == BlockType::slide)
	{
		return std::make_unique<Slide>(pos, camera);
	}
	else if (type == BlockType::lift)
	{
		return std::make_unique<Lift>(pos, camera);
	}
	return nullptr;
}

