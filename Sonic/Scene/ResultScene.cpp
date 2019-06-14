#include "ResultScene.h"
#include <DxLib.h>
#include <string>
#include "../Peripheral.h"
#include "../Game.h"
#include "TitleScene.h"


void ResultScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "attack"))
	{
		pal = 255;
		updater = &ResultScene::FadeoutUpdate;
	}
	
	if (pal >= 255)
	{
		pal = 255;
	}
	else
	{
		pal +=20;
	}
}

void ResultScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Game::Instance().ChangeScene(new TitleScene());
	}
	else
	{
		pal -= 20;
	}
}

ResultScene::ResultScene()
{
	updater = &ResultScene::FadeinUpdate;

	resultImage = DxLib::LoadGraph("img/tresult.png");
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Peripheral& p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, resultImage, true);
	DxLib::DrawString(50, 50, "ResultScene", 0x000000);

	(this->*updater)(p);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);
}
