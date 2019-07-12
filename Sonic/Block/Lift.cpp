#include "Lift.h"
#include <DxLib.h>
#include "../Camera.h"


Lift::Lift(const Vector2& pos, const Camera& camera) : Block(Rect(pos, Size(16, 16)), camera), camera(camera)
{
	moveCount = 0;
}


Lift::~Lift()
{
}

void Lift::Update()
{
	if (moveCount / 30 % 2 == 0)
	{
		rect.center.y += 2;
	}
	else
	{
		rect.center.y -= 2;
	}

	++moveCount;
}

void Lift::Draw()
{
	auto& offset = camera.GetViewRange();

	DxLib::DrawRectExtendGraph(rect.Left() - offset.Left(), rect.Top() - offset.Top(), rect.Right() - offset.Left(), rect.Bottom() - offset.Top(), 16, 112, 16, 16, img, true);
}
