#include "Lift.h"
#include <DxLib.h>
#include "../Camera.h"


Lift::Lift(const Vector2& pos, const Camera& camera, unsigned int runLength) : Block(pos, camera, runLength), camera(camera)
{
	moveCount = 0;
	speed = Vector2f(0, runLength);
}


Lift::~Lift()
{
}

void Lift::Update()
{
	++moveCount;

	if (moveCount  % 30 == 0)
	{
		speed *= -1;
	}

	rect.center.y += speed.y;
}

void Lift::Draw()
{
	auto& offset = camera.GetViewRange();

	auto right = rect.Right();
	for (int left = rect.Left(); left < right; left += blockSize)
	{
		DxLib::DrawRectExtendGraph(left - offset.Left(), rect.Top() - offset.Top(),
			left + blockSize - offset.Left(), rect.Bottom() - offset.Top(), 16, 112, 16, 16, img, true);
	}
}
