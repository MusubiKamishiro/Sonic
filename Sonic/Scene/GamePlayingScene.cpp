#include "GamePlayingScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "../Camera.h"
#include "../BackGround.h"
#include "../Ground.h"
#include "../Stage.h"
#include "../Block/Block.h"
#include "../Collider.h"

#include "SceneManager.h"
#include "ResultScene.h"
#include "PauseScene.h"

#include "../Actor/Player.h"
#include "../Actor/Enemy.h"

#include "../Spawner/Spawner.h"


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
	collider.reset(new Collider());
	stage->ReadStageFile("stage/level1.fmf", *ground, *player, *camera);

	camera->AddPlayer(player);

	bg->AddParts("img/bg.jpg", Vector2(0, 0), 1.0f, false, LayoutType::repeat);
	bg->AddParts("img/bg2.png", Vector2(30, 400), 0.7f, true, LayoutType::repeat);

	time = 0;
	seg = Segment(0, 0, 0, 0);
	oldseg = Segment(0, 0, 0, 0);

	updater = &GamePlayingScene::FadeinUpdate;
	
	groundy = 0;
	breakSound = DxLib::LoadSoundMem("se/hit.wav");
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	float grad = 0.0f;
	
	if (!player->onflag)
	{
		groundy = ground->GetCurrentGroundY(grad);
	}
	
	for (auto& block : stage->GetBlockData())
	{
		block->Update();
	}
	player->Update(p);

	// �����Ȃ��Ȃ�����󒆂�
	oldseg = seg;
	seg = ground->GetCurrentSegment();
	if (seg != oldseg)
	{
		if (!((oldseg.posA == seg.posB) || (seg.posA == oldseg.posB)))
		{
			player->isAerial = true;
			player->onflag = false;
		}
	}

	// �n�ʂ��Ȃ�������󒆂�
	if (groundy == INT_MIN)
	{
		player->isAerial = true;
		player->onflag = false;
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

	for (auto& spawner : stage->GetSpawnerData())
	{
		spawner->Update(enemies);
	}

	for (auto& enemy : enemies)
	{
		enemy->Update(p);
	}

	// �n�ʂ�P�̓����蔻�蒆
	HitCheck();

	// �G��P�̓����蔻��
	for (auto& enemy : enemies)
	{
		// ��ʊO�Ȃ���Ȃ��Ă悵
		/*if ()
		{
			continue;
		}*/

		for (auto& prect : player->GetActRect())
		{
			for (auto& erect : enemy->GetActRect())
			{
				// ��������
				if (collider->IsCollided(player->GetHitRect(prect.rect), enemy->GetHitRect(erect.rect)))
				{
					player->OnDead();
				}
			}
		}
	}
	
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

	for (auto& enemy : enemies)
	{
		auto pos = enemy->GetPos();
		auto& range = camera->GetViewRange();

		if ((pos.x > range.Left()) && (pos.x < range.Right()))
		{
			enemy->Draw();
		}
	}

#ifdef _DEBUG
	DebugDraw();
#endif // _DEBUG

	// �t�F�[�h�C��,�A�E�g�̂��߂̖�
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}

void GamePlayingScene::HitCheck()
{
	player->onflag = false;
	for (auto& prect : player->GetActRect())
	{
		for (auto& block : stage->GetBlockData())
		{
			Rect blockCol = block->GetCollider();
			auto ppos = player->GetPos();

			// ���肷��͈͂����肷��
			if ((std::abs(blockCol.center.x - ppos.x) <= 50) || (std::abs(blockCol.center.y - ppos.y) <= 50))
			{
				if (prect.rt == RectType::attack)
				{
					// �߂荞�܂Ȃ��悤��
					if (collider->IsCollided(player->GetHitRect(prect.rect), blockCol))
					{
						Rect rc = Rect::CreateOverlappedRangeRect(player->GetHitRect(prect.rect), blockCol);
						Vector2f offset = Vector2f();

						// �߂荞�ݗʂ̏������ق��ɉ����Ԃ�
						if (rc.Width() < rc.Height())
						{
							offset = Vector2f((rc.Width()*((player->GetPos().x < blockCol.center.x) ? -1.0f : 1.0f)), 0);
							player->AdjustPos(offset);
						}
						else
						{
							if (player->GetHitRect(prect.rect).center.y < blockCol.center.y)
							{
								if (player->onflag)
								{
									player->OnGround(groundy);
								}
								groundy = rc.Top();
								player->onflag = true;
								
							}
							else
							{
								offset = Vector2f(0, (rc.Height()*((player->GetPos().y < blockCol.center.y) ? -1.0f : 1.0f)));
								player->AdjustPos(offset);
							}
						}
					}
				}
			}
		}
	}
}

void GamePlayingScene::DebugDraw()
{
}