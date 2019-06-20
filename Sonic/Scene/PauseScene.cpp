#include "PauseScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "../Game.h"


void PauseScene::FadeinUpdate(const Peripheral & p)
{
	updater = &PauseScene::WaitUpdate;
}

void PauseScene::FadeoutUpdate(const Peripheral & p)
{
	SceneManager::Instance().PopScene();
}

void PauseScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "pause"))
	{
		updater = &PauseScene::FadeoutUpdate;
	}
}

PauseScene::PauseScene()
{
	img = DxLib::LoadGraph("img/pause.jpg");
	ssize = Game::Instance().GetScreenSize();

	pal = 255;
	updater = &PauseScene::FadeinUpdate;
}


PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Peripheral & p)
{
	(this->*updater)(p);
}

void PauseScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DxLib::DrawExtendGraph(50, 50, ssize.x - 50, ssize.y - 50, img, true);


	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}
