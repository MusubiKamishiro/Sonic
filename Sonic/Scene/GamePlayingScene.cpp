#include "GamePlayingScene.h"
#include <DxLib.h>

#include "../Peripheral.h"
#include "../Game.h"
#include "ResultScene.h"
//#include "TitleScene.h"


void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "attack"))
	{
		pal = 255;
		updater = &GamePlayingScene::FadeoutUpdate;
	}
	else
	{
		if(pal < 255)
		pal += 20;
	}
}

void GamePlayingScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Game::Instance().ChangeScene(new ResultScene());
	}
	else
	{
		pal -= 20;
	}
}


GamePlayingScene::GamePlayingScene()
{
	pos[2] = ( Vector2(0, 0),  Vector2(0, 0) );
	ssize = Game::Instance().GetScreenSize();

	bg1 = DxLib::LoadGraph("img/bg1.png");
	bg2 = DxLib::LoadGraph("img/bg2.png");

	updater = &GamePlayingScene::FadeinUpdate;
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	for (int i = 0; i < p.GetPlayerCount(); ++i)
	{
		if (p.IsPressing(i, "right"))
		{
			pos[i].x += 5;
		}
		if (p.IsPressing(i, "left"))
		{
			pos[i].x -= 5;
		}
		if (p.IsPressing(i, "up"))
		{
			pos[i].y -= 5;
		}
		if (p.IsPressing(i, "down"))
		{
			pos[i].y += 5;
		}
	}

	DxLib::DrawRectExtendGraph(pos[0].x, pos[0].y, 200 + pos[0].x, 200 + pos[0].y, pos[0].x, pos[0].y, 200, 200, bg2, true);
	DxLib::DrawRectExtendGraph(pos[1].x, pos[1].y, 100 + pos[1].x, 100 + pos[1].y, pos[1].x, pos[1].y, 100, 100, bg1, true);
	DxLib::DrawFormatString(0, 0, 0xff0000, "PADNUM：%d", p.GetPadCount());

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
	
	(this->*updater)(p);
}

