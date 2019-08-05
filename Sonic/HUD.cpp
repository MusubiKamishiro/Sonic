#include "HUD.h"
#include <DxLib.h>
#include "Game.h"
#include "System/FileSystem.h"
#include "System/ImageLoader.h"


HUD::HUD()
{
	score = 0;

	ImageData data;
	Game::Instance().GetFileSystem()->Load("img/tile5.jpg", data);
	img = data.GetHandle();
}


HUD::~HUD()
{
}

void HUD::AddScore(int inscore)
{
	score += inscore;
}

void HUD::Update()
{

}

void HUD::Draw()
{
	DxLib::DrawExtendGraph(0, 0, 100, 100, img, true);
	DxLib::DrawFormatString(100, 80, 0x00ff00, "* %d", score);
}
