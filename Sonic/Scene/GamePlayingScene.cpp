#include "GamePlayingScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "../Camera.h"
#include "../BackGround.h"
#include "../Ground.h"
#include "../Stage.h"
#include "../HUD.h"
#include "../Block/Block.h"
#include "../Collider.h"

#include "SceneManager.h"
#include "GamePlaying3DScene.h"
#include "PauseScene.h"

#include "../Actor/Player.h"
#include "../Actor/Enemy.h"

#include "../Spawner/Spawner.h"
#include "../Event/Event.h"


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
		SceneManager::Instance().ChangeScene(std::make_unique<GamePlaying3DScene>());
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
	DxLib::SetUseASyncLoadFlag(false);
	ssize = Game::Instance().GetScreenSize();

	camera.reset(new Camera());
	player.reset(new Player(*camera));
	bg.reset(new BackGround(*camera));
	ground.reset(new Ground(*player));
	stage.reset(new Stage());
	hud.reset(new HUD());
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

	adjustSpeed = Vector2f(0, 0);
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	float grad = 0.0f;
	
	if (!player->onflag)
	{
		groundy = ground->GetCurrentGroundY(*player, grad);
	}
	
	for (auto& block : stage->GetBlockData())
	{
		block->Update();
	}
	player->Update(p);

	// 道がなくなったら空中に
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

	// 地面がなかったら空中に
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

		// yの移動量がプラス(下向き)のときだけ
		if (player->GetVel().y > 0)
		{
			// 地面を超えてたら着地させる
			if ((player->GetPos().y > groundy) && (groundy != INT_MIN))
			{
				player->OnGround(groundy);
			}
		}
	}

	if (!player->deadflag)
	{
		camera->Update();
	}
	ground->Updade(time);

	for (auto& spawner : stage->GetSpawnerData())
	{
		spawner->Update(enemies);
	}

	for (auto& enemy : enemies)
	{
		enemy->Update(p);

		int eGroundy = ground->GetCurrentGroundY(*enemy, grad);
		enemy->AdjustY(eGroundy, grad);
	}

	for (auto& e : stage->GetEventData())
	{
		e->Update(p);
	}

	// 地面とPの当たり判定中
	HitCheck();

	// 敵とPの当たり判定
	for (auto& enemy : enemies)
	{
		// 画面外ならやらなくてよし
		auto pos = enemy->GetPos();
		auto& range = camera->GetViewRange();
		if ((pos.x < range.Left()) || (pos.x > range.Right()))
		{
			continue;
		}

		for (auto& prect : player->GetActRect())
		{
			for (auto& erect : enemy->GetActRect())
			{
				if (!enemy->GetIsAvailable())
				{
					continue;
				}

				// 当たった
				if (collider->IsCollided(player->GetHitRect(prect.rect), enemy->GetHitRect(erect.rect)))
				{
					Rect rc = Rect::CreateOverlappedRangeRect(player->GetHitRect(prect.rect), enemy->GetHitRect(erect.rect));

					// 上から当たったら敵を殺す
					if (rc.Width() > rc.Height())
					{
						if (player->GetHitRect(prect.rect).center.y < enemy->GetHitRect(erect.rect).center.y)
						{
							enemy->OnDead();
							player->SetJumpPower();
							hud->AddScore(200);
						}
					}
					else
					{
						player->OnDead();
					}
				}
			}
		}
	}

	// コインとか
	for (auto& e : stage->GetEventData())
	{
		if (!e->GetIsAvailable())
		{
			continue;
		}

		// 画面外ならやらなくてよし
		auto pos = e->GetPos();
		auto& range = camera->GetViewRange();
		if ((pos.x < range.Left()) || (pos.x > range.Right()))
		{
			continue;
		}

		for (auto& prect : player->GetActRect())
		{
			for (auto& erect : e->GetActRect())
			{
				// 当たった
				if (collider->IsCollided(player->GetHitRect(prect.rect), e->GetHitRect(erect.rect)))
				{
					e->OnDead();
					hud->AddScore(100);
				}
			}
		}
	}

	hud->Update();
	
	// ポーズボタン押されたらポーズへ
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

	for (auto& e : stage->GetEventData())
	{
		if (!e->GetIsAvailable())
		{
			continue;
		}

		e->Draw();
	}

	for (auto& enemy : enemies)
	{
		if (!enemy->GetIsAvailable())
		{
			continue;
		}

		auto pos = enemy->GetPos();
		auto& range = camera->GetViewRange();

		if ((pos.x > range.Left()) && (pos.x < range.Right()))
		{
			enemy->Draw();
		}
	}

	hud->Draw();

#ifdef _DEBUG
	DebugDraw();
#endif // _DEBUG

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}

void GamePlayingScene::HitCheck()
{
	adjustSpeed = Vector2f(0, 0);
	player->onflag = false;
	for (auto& prect : player->GetActRect())
	{
		for (auto& block : stage->GetBlockData())
		{
			Rect blockCol = block->GetCollider();
			auto ppos = player->GetPos();

			// 判定する範囲を限定する
			if ((std::abs(blockCol.center.x - ppos.x) <= 50) || (std::abs(blockCol.center.y - ppos.y) <= 50))
			{
				if (prect.rt == RectType::attack)
				{
					// めり込まないように
					if (collider->IsCollided(player->GetHitRect(prect.rect), blockCol))
					{
						Rect rc = Rect::CreateOverlappedRangeRect(player->GetHitRect(prect.rect), blockCol);
						Vector2f offset = Vector2f();

						// めり込み量の小さいほうに押し返す
						if (rc.Width() < rc.Height())
						{
							offset = Vector2f((rc.Width()*((player->GetPos().x < blockCol.center.x) ? -1.0f : 1.0f)), 0);
							player->AdjustPos(offset);
						}
						else
						{
							if (player->GetHitRect(prect.rect).center.y < blockCol.center.y)
							{
								groundy = rc.Top() + 2;
								if (player->onflag)
								{
									player->OnGround(groundy);
								}
								player->onflag = true;
								adjustSpeed = block->GetSpeed();
							}
							else
							{
								offset = Vector2f(0, (rc.Height()*((player->GetPos().y < blockCol.center.y) ? -1.0f : 1.0f)));
								player->AdjustPos(offset);
							}
						}
						break;
					}
				}
			}
		}
	}

	player->AdjustMove(adjustSpeed);
}

void GamePlayingScene::DebugDraw()
{
}