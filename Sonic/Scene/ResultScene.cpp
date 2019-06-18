#include "ResultScene.h"
#include <DxLib.h>
#include <memory>
#include <string>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
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
		sceneManager->ChangeScene(std::make_unique<TitleScene>());
	}
	else
	{
		pal -= 20;
	}
}

ResultScene::ResultScene()
{
	updater = &ResultScene::FadeinUpdate;

	resultImage = DxLib::LoadGraph("img/result.png");
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Peripheral& p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, resultImage, true);
	
	
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);
	(this->*updater)(p);
}
