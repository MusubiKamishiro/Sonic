#include "GamePlaying3DScene.h"
#include "../Peripheral.h"
#include "SceneManager.h"
#include "ResultScene.h"


GamePlaying3DScene::GamePlaying3DScene()
{
	DxLib::SetUseASyncLoadFlag(true);
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/ouja/三柱式 仮面ライダー王蛇.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/ピーポくん/ピーポくん.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/はとむね先輩/はとむね先輩.pmd"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/PPK/ポプ子.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/sonic.pmx"));

	time = 0;
	music = DxLib::LoadSoundMem("3Dmodel/music.mp3");
	stoptime = -80;

	cameraPos = DxLib::VGet(0, 15, -50);
	targetPos = DxLib::VGet(0, 10, 0);
	DxLib::SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);	// カメラ座標とターゲット座標
	DxLib::SetupCamera_Perspective(45.0f * DX_PI_F / 180.0f);		// 画角の設定
	DxLib::SetCameraNearFar(0.5f, 300.0f);		// クリッピング設定

	updater = &GamePlaying3DScene::FadeinUpdate;
}


GamePlaying3DScene::~GamePlaying3DScene()
{
}

void GamePlaying3DScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "attack"))
	{
		pal = 255;
		updater = &GamePlaying3DScene::FadeoutUpdate;
	}
	else
	{
		if (pal < 255)
		{
			pal += 20;
		}
	}
}

void GamePlaying3DScene::FadeoutUpdate(const Peripheral & p)
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

void GamePlaying3DScene::WaitUpdate(const Peripheral & p)
{
}

void GamePlaying3DScene::Update(const Peripheral & p)
{
	if (!loadFlag)
	{
		for (int i = 0; i < models.size(); ++i)
		{
			if (ddr == i)
			{
				if (DxLib::CheckHandleASyncLoad(models[i]) == true)
				{
					DxLib:DrawString(200, 200, "Now Loading...", 0xff0000);
				}
				else if (DxLib::CheckHandleASyncLoad(models[i]) == false)
				{
					++ddr;
					motion = DxLib::MV1AttachAnim(models[i], 1);
					totalTime = DxLib::MV1GetAttachAnimTotalTime(models[i], motion);
					DxLib::MV1SetPosition(models[i], DxLib::VGet(0, 0, 0));
					//DxLib::MV1PhysicsResetState(models[i]);
				}
			}

			if (ddr == models.size())
			{
				loadFlag = true;
			}
		}
	}

	for (auto& model : models)
	{
		auto pos = DxLib::MV1GetPosition(model);
	}


	if (p.IsPressing(0, "right"))
	{
		cameraPos.x += 0.5f;
		targetPos.x += 0.5f;
	}
	else if (p.IsPressing(0, "left"))
	{
		cameraPos.x -= 0.5f;
		targetPos.x -= 0.5f;
	}
	else if (p.IsPressing(0, "up"))
	{
		cameraPos.y += 0.5f;
		targetPos.y += 0.5f;
	}
	else if (p.IsPressing(0, "down"))
	{
		cameraPos.y -= 0.5f;
		targetPos.y -= 0.5f;
	}
	//else if (p.IsPressing(0, "near"))
	//{
	//	pos.z -= 0.1f;
	//}
	//else if (p.IsPressing(0, "far"))
	//{
	//	pos.z += 0.1f;
	//}

	//DxLib::MV1SetPosition(models, pos);
	DxLib::SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);	// カメラ座標とターゲット座標

	if (loadFlag)
	{
		DxLib::PlaySoundMem(music, DX_PLAYTYPE_BACK, false);
		stoptime += 0.25f;
		if (stoptime >= 0)
		{
			time += 0.25f;
		}
	}
	// 再生時間がｱﾆﾒｰｼｮﾝの総再生時間になったら0に戻す
	if (time >= totalTime)
	{
		time = totalTime;
	}

	for (auto& model : models)
	{
		DxLib::MV1SetAttachAnimTime(model, motion, time);
	}

	(this->*updater)(p);
}

void GamePlaying3DScene::Draw()
{
	for (auto& model : models)
	{
		DxLib::MV1DrawModel(model);
	}
}