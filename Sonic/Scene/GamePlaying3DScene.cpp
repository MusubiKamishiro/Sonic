#include "GamePlaying3DScene.h"
#include "../Peripheral.h"
#include "SceneManager.h"
#include "ResultScene.h"


GamePlaying3DScene::GamePlaying3DScene()
{
	stage = DxLib::MV1LoadModel("3Dmodel/table/�w�Z���v��01.pmx");
	loadImg = DxLib::LoadGraph("img/yokyou.png");
	loadTime = 0;

	DxLib::SetUseASyncLoadFlag(true);
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/ouja/�O���� ���ʃ��C�_�[����.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/�s�[�|����/�s�[�|����.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/�͂Ƃނː�y/�͂Ƃނː�y.pmd"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/PPK/�|�v�q.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/sonic/sonic.pmx"));

	time = 0;
	music = DxLib::LoadSoundMem("3Dmodel/music.mp3");
	stoptime = -80;

	cameraPos = DxLib::VGet(0, 15, -50);
	targetPos = DxLib::VGet(0, 10, 0);
	DxLib::SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);	// �J�������W�ƃ^�[�Q�b�g���W
	DxLib::SetupCamera_Perspective(45.0f * DX_PI_F / 180.0f);		// ��p�̐ݒ�
	DxLib::SetCameraNearFar(0.5f, 300.0f);		// �N���b�s���O�ݒ�

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
					DxLib::DrawExtendGraph(0, 0, 1024, 576, loadImg, true);
					if (loadTime / 30 % 2 == 0)
					{
						DxLib:DrawString(5, 560, "Now Loading...", 0xff0000);
					}
					++loadTime;
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
	DxLib::SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);	// �J�������W�ƃ^�[�Q�b�g���W

	if (loadFlag)
	{
		DxLib::PlaySoundMem(music, DX_PLAYTYPE_BACK, false);
		stoptime += 0.5f;
		if (stoptime >= 0)
		{
			time += 0.5f;
		}
	}
	// �Đ����Ԃ���Ұ��݂̑��Đ����ԂɂȂ�����0�ɖ߂�
	if (time >= totalTime)
	{
		time = totalTime-0.5f;
	}

	for (auto& model : models)
	{
		DxLib::MV1SetAttachAnimTime(model, motion, time);
	}

	(this->*updater)(p);
}

void GamePlaying3DScene::Draw()
{
	if (loadFlag)
	{
		for (auto& model : models)
		{
			DxLib::MV1DrawModel(model);
		}
	}
	DxLib::MV1DrawModel(stage);
}