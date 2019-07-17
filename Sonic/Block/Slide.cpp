#include "Slide.h"
#include <DxLib.h>
#include "../Camera.h"


Slide::Slide(const Vector2& pos, const Camera& camera, unsigned int runLength) : Block(pos, camera, runLength), camera(camera), speed((int) runLength)
{
	moveCount = 0;
}


Slide::~Slide()
{
}

void Slide::Update()
{
	if (moveCount / 30 % 2 == 0)
	{
		rect.center.x += speed;
	}
	else
	{
		rect.center.x -= speed;
	}

	++moveCount;
}

void Slide::Draw()
{
	auto& offset = camera.GetViewRange();

	auto right = rect.Right();
	for (int left = rect.Left(); left < right; left += blockSize)
	{
		DxLib::DrawRectExtendGraph(left - offset.Left(), rect.Top() - offset.Top(),
			left + blockSize - offset.Left(), rect.Bottom() - offset.Top(), 0, 112, 16, 16, img, true);
	}
}
