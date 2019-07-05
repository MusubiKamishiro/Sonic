#include "GamePlayingScene.h"
#include <DxLib.h>
#include <memory>
#include "../Peripheral.h"
#include "../Game.h"
#include "../Character/Player.h"
#include "../Camera.h"
#include "../BackGround.h"
#include "../Ground.h"
#include "../Stage.h"
#include "../Block/BlockFactory.h"

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
	stage.reset(new Stage());
	blockFactory.reset(new BlockFactory(*camera));
	stage->ReadStageFile("stage/level1.fmf", *ground);
	
	camera->AddPlayer(player);

	bg->AddParts("img/bg.jpg", Vector2(0, 0), 1.0f, false, LayoutType::repeat);
	bg->AddParts("img/bg2.png", Vector2(30, 400), 0.7f, true, LayoutType::repeat);

	time = 0;
	seg = Segment(0, 0, 0, 0);
	oldseg = Segment(0, 0, 0, 0);

	updater = &GamePlayingScene::FadeinUpdate;
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	float grad = 0.0f;
	int groundy = ground->GetCurrentGroundY(grad);

	player->Update(p);

	// �����Ȃ��Ȃ�����󒆂�
	oldseg = seg;
	seg = ground->GetCurrentSegment();
	if (seg != oldseg)
	{
		if (!((oldseg.posA == seg.posB) || (seg.posA == oldseg.posB)))
		{
			player->isAerial = true;
		}
	}

	// �n�ʂ��Ȃ�������󒆂�
	if ((groundy == INT_MIN))
	{
		player->isAerial = true;
	}

	if (!player->isAerial)
	{
		player->AdjustY(groundy, grad);
	}
	else
	{
		if (player->GetPos().y > ground->GetCurrentDeadLine())
		{
			player->OnDead();
		}

		// y�̈ړ��ʂ��v���X(������)�̂Ƃ�����
		if (player->GetVel().y > 0)
		{
			// �n�ʂ𒴂��Ă��璅�n������
			if ((player->GetPos().y > groundy) && (groundy != INT_MIN))
			{
				player->OnGround(groundy);
			}
		}
	}

	camera->Update();
	ground->Updade(time);

	// �|�[�Y�{�^�������ꂽ��|�[�Y��
	if (p.IsTrigger(0, "pause"))
	{
		SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
	}

	++time;
	(this->*updater)(p);
}

void GamePlayingScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	
	bg->Draw();
	ground->Draw(camera->GetViewRange());
	/*for (auto& block : blockFactory)
	{
		block->Draw();
	}*/

	player->Draw();
	
	// �t�F�[�h�C��,�A�E�g�̂��߂̖�
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}

