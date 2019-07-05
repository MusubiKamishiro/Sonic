#include "BlockFactory.h"
#include "Brick.h"


BlockFactory::BlockFactory(const Camera& camera)
{
}


BlockFactory::~BlockFactory()
{
}

std::unique_ptr<Block> BlockFactory::Create(BlockType type, const Camera& camera, const Vector2 & pos)
{
	// ブロックタイプが一致すれば生成
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(camera);
	}
	return nullptr;
}

