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
	// �u���b�N�^�C�v����v����ΐ���
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(camera);
	}
	return nullptr;
}

