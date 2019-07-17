#include "Block.h"
#include <DxLib.h>


Block::Block(const Vector2& pos, const Camera & camera, int count) : blockSize(16)
{
	img = DxLib::LoadGraph("img/blocks.png");

	rect = Rect(pos, Size(blockSize * count, blockSize));
	rect.center.x -= rect.size.width / 2;
}

Rect Block::GetCollider() const
{
	return rect;
}
