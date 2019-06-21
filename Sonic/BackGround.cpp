#include "BackGround.h"
#include <DxLib.h>
#include "Camera.h"

#include "Game.h"


BackGround::BackGround(const Camera& camera) : camera(camera)
{
	img = DxLib::LoadGraph("img/bg.jpg");
	ssize = Game::Instance().GetScreenSize();
}


BackGround::~BackGround()
{
}

void BackGround::Draw()
{
	int left = camera.GetViewRange().Left();
	int top = camera.GetViewRange().Top();

	for (int i = 0; i < 2; ++i)
	{
		DxLib::DrawExtendGraph((-left % ssize.x) + i * ssize.x, -top, (camera.GetViewRange().Width() - left % ssize.x) + i * ssize.x, camera.GetViewRange().Height() - top, img, true);
	}
}
