#include "Block.h"
#include <DxLib.h>


Block::Block(const Rect& rect, const Camera & camera)
{
	img = DxLib::LoadGraph("img/blocks.png");
	this->rect = rect;
}

Rect Block::GetCollider() const
{
	return rect;
}
