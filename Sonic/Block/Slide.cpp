#include "Slide.h"
#include <DxLib.h>
#include "../Camera.h"


Slide::Slide(const Vector2& pos, const Camera& camera) : Block(Rect(pos, Size(16, 16)), camera), camera(camera)
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
		rect.center.x += 2;
	}
	else
	{
		rect.center.x -= 2;
	}

	++moveCount;
}

void Slide::Draw()
{
	auto& offset = camera.GetViewRange();

	DxLib::DrawRectExtendGraph(rect.Left() - offset.Left(), rect.Top() - offset.Top(), rect.Right() - offset.Left(), rect.Bottom() - offset.Top(), 0, 112, 16, 16, img, true);
}
