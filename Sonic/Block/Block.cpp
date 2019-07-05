#include "Block.h"
#include <DxLib.h>


Block::Block(const Camera & camera)
{
	img = DxLib::LoadGraph("img/blocks.png");
}
