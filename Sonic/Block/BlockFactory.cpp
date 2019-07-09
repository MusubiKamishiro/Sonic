#include "BlockFactory.h"
#include "Brick.h"


BlockFactory::BlockFactory(const Camera& camera) : camera(camera)
{
}


BlockFactory::~BlockFactory()
{
}

std::shared_ptr<Block> BlockFactory::Create(BlockType type, const Vector2& pos)
{
	// �u���b�N�^�C�v����v����ΐ���
	if (type == BlockType::brick)
	{
		return std::make_unique<Brick>(pos, camera);
	}
	return nullptr;
}

