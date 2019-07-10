#include "Brick.h"
#include <DxLib.h>
#include "../Camera.h"


Brick::Brick(const Vector2& pos, const Camera& camera) : Block(Rect(pos, Size(16, 16)), camera), camera(camera)
{
}


Brick::~Brick()
{
}

void Brick::Update()
{
}

void Brick::Draw()
{
	auto& offset = camera.GetViewRange();
	
	DxLib::DrawRectExtendGraph(rect.Left() - offset.Left(), rect.Top() - offset.Top(), rect.Right() - offset.Left(), rect.Bottom() - offset.Top(), 16, 0, 16, 16, img, true);
}
