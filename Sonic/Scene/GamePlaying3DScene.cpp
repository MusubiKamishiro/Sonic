#include "GamePlaying3DScene.h"
#include "../Peripheral.h"
#include "SceneManager.h"
#include "ResultScene.h"


GamePlaying3DScene::GamePlaying3DScene()
{
	DxLib::SetUseASyncLoadFlag(true);
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/ouja/�O���� ���ʃ��C�_�[����.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/PPK/�|�v�q.pmx"));
	models.emplace_back(DxLib::MV1LoadModel("3Dmodel/sonic.pmx"));

	//models.emplace_back(DxLib::MV1LoadModel("3Dmodel/yayoi/yayoi.pmd"));
	//models.emplace_back(DxLib::MV1LoadModel("3Dmodel/hibari/�_��Ver1.10.pmd"));
	//models.emplace_back(DxLib::MV1LoadModel("3Dmodel/UMP45/UMP45_V080.pmx"));
	

	for (auto& model : models)
	{
		motion = DxLib::MV1AttachAnim(model, 1);
		totalTime = DxLib::MV1GetAttachAnimTotalTime(model, motion);
		DxLib::MV1SetPosition(model, DxLib::VGet(0, 0, 0));
	}
	time = 0;

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
				DxLib:DrawString(200, 200, "Now Loading...", 0xff0000);
				}
				else if (DxLib::CheckHandleASyncLoad(models[i]) == false)
				{
					++ddr;
					motion = DxLib::MV1AttachAnim(models[i], 1);
					totalTime = DxLib::MV1GetAttachAnimTotalTime(models[i], motion);
					DxLib::MV1SetPosition(models[i], DxLib::VGet(0, 0, 0));
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

	time += 0.5f;
	// �Đ����Ԃ���Ұ��݂̑��Đ����ԂɂȂ�����0�ɖ߂�
	if (time >= totalTime)
	{
		time = 0;
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