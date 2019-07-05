#include "Brick.h"
#include <DxLib.h>
#include "../Camera.h"


Brick::Brick(const Camera& camera) : Block(camera), camera(camera)
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
	
	DxLib::DrawRectExtendGraphF(0, 0, 30, 30, 16, 16, 32, 32, img, true);
}
