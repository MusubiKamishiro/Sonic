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
#include "../Block/Block.h"
#include "../Block/BlockFactory.h"
#include "../Collider.h"

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
	collider.reset(new Collider());
	stage->ReadStageFile("stage/level1.fmf", *ground, *blockFactory);
	
	camera->AddPlayer(player);

	bg->AddParts("img/bg.jpg", Vector2(0, 0), 1.0f, false, LayoutType::repeat);
	bg->AddParts("img/bg2.png", Vector2(30, 400), 0.7f, true, LayoutType::repeat);

	time = 0;
	seg = Segment(0, 0, 0, 0);
	oldseg = Segment(0, 0, 0, 0);

	updater = &GamePlayingScene::FadeinUpdate;
	flag = false;

	groundy = 0;
	breakSound = DxLib::LoadSoundMem("se/hit.wav");
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	flag = false;

	float grad = 0.0f;
	//groundy = player->isAerial ? ground->GetCurrentGroundY(grad) : groundy;
	groundy = ground->GetCurrentGroundY(grad);


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

	// �����蔻�蒆
	HitCheck();
	
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
	for (auto& block : stage->GetBlockData())
	{
		block->Draw();
	}

	player->Draw();

#ifdef _DEBUG
	DebugDraw();
#endif // _DEBUG

	// �t�F�[�h�C��,�A�E�g�̂��߂̖�
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}

void GamePlayingScene::HitCheck()
{
	for (auto& prect : player->GetActRect())
	{
		for (auto& block : stage->GetBlockData())
		{
			if (prect.rt == RectType::damage)
			{
				Rect blockCol = block->GetCollider();

				// �߂荞�܂Ȃ��悤��
				if (collider->IsCollided(player->GetHitRect(prect.rect), blockCol))
				{
					Rect rc = Rect::CreateOverlappedRangeRect(player->GetHitRect(prect.rect), blockCol);
					Vector2f offset = Vector2f();

					if (rc.Width() < rc.Height())
					{
						offset = Vector2f((rc.Width()*((player->GetPos().x < blockCol.center.x) ? -1.0f : 1.0f)), 0);
						player->AdjustPos(offset);
					}
					else
					{
						if (player->GetHitRect(prect.rect).center.y < blockCol.center.y)
						{
							groundy = rc.Top();
							player->isAerial = false;
						}
						else
						{
							offset = Vector2f(0, (rc.Height()*((player->GetPos().y < blockCol.center.y) ? -1.0f : 1.0f)));
							player->AdjustPos(offset);
						}
					}

					flag = true;
				}
			}
			else if (prect.rt == RectType::adjust)
			{
				if (collider->IsCollided(player->GetHitRect(prect.rect), block->GetCollider()))
				{
					flag = true;
				}
			}
		}
	}
}

void GamePlayingScene::DebugDraw()
{
	if (flag)
	{
		DxLib::DrawFormatString(300, 0, 0xff0000, "������������");
	}
}