#include "PauseScene.h"
#include <DxLib.h>


void PauseScene::FadeinUpdate(const Peripheral & p)
{
}

void PauseScene::FadeoutUpdate(const Peripheral & p)
{
}

PauseScene::PauseScene()
{
}


PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Peripheral & p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DxLib::DrawString(0, 0, "PauseScene", 0x00ff00);
	
	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	//DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);

	(this->*updater)(p);
}
