#include "GamePlayingScene.h"
#include <DxLib.h>
#include <memory>
#include "../Peripheral.h"
#include "../Game.h"
#include "../Character/Player.h"
#include "../Camera.h"
#include "../BackGround.h"
#include "../Ground.h"

#include "SceneManager.h"
#include "ResultScene.h"
#include "PauseScene.h"



void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "attack"))
	{
		pal = 255;
		updater = &GamePlayingScene::FadeoutUpdate;
	}
	else
	{
		if (pal < 255)
		{
			pal += 20;
		}
	}
}

void GamePlayingScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique<ResultScene>());
	}
	else
	{
		pal -= 20;
	}
}

void GamePlayingScene::WaitUpdate(const Peripheral & p)
{
}


GamePlayingScene::GamePlayingScene()
{
	ssize = Game::Instance().GetScreenSize();

	camera.reset(new Camera());
	player.reset(new Player(*camera));
	bg.reset(new BackGround(*camera));
	ground.reset(new Ground(*player));
	camera->AddPlayer(player);

	bg->AddParts("img/bg.jpg", Vector2(0, 0), 1.0f, false, LayoutType::repeat);
	bg->AddParts("img/bg2.png", Vector2(30, 400), 0.7f, false, LayoutType::repeat);

	updater = &GamePlayingScene::FadeinUpdate;
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	player->Update(p);

	int groundy = ground->GetCurrentGroundY(player->GetPos());

	if (!player->isAerial)
	{
		player->AdjustY(groundy);
	}
	else
	{
		// 地面を超えてたら着地させる
		if (player->GetPos().y > groundy)
		{
			player->OnGround(groundy);
		}
	}

	camera->Update();

	// ポーズボタン押されたらポーズへ
	if (p.IsTrigger(0, "pause"))
	{
		SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
	}


	(this->*updater)(p);
}

void GamePlayingScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	
	bg->Draw();
	player->Draw();
	
	ground->Draw(camera->GetViewRange());

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}

