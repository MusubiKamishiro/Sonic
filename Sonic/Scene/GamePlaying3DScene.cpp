#include "GamePlaying3DScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "ResultScene.h"


GamePlaying3DScene::GamePlaying3DScene()
{
	//model = DxLib::MV1LoadModel("3Dmodel/yayoi/yayoi.pmd");
	model = DxLib::MV1LoadModel("3Dmodel/ouja/�O���� ���ʃ��C�_�[����.pmx");
	DxLib::MV1SetPosition(model, DxLib::VGet(0, 0, 0));
	DxLib::SetCameraPositionAndTarget_UpVecY(DxLib::VGet(0, 15, -30), DxLib::VGet(0, 10, 0));	// �J�������W�ƃ^�[�Q�b�g���W
	DxLib::SetupCamera_Perspective(45.0f * DX_PI_F / 180.0f);	// ��p�̐ݒ�
	DxLib::SetCameraNearFar(0.5f, 300.0f);		// �N���b�s���O�ݒ�

	motion = DxLib::MV1AttachAnim(model, 0);
	totalTime = DxLib::MV1GetAttachAnimTotalTime(model, motion);

	time = 0;
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
	auto pos = DxLib::MV1GetPosition(model);

	if (p.IsPressing(0, "right"))
	{
		pos.x += 0.1f;
	}
	else if (p.IsPressing(0, "left"))
	{
		pos.x -= 0.1f;
	}
	else if (p.IsPressing(0, "up"))
	{
		pos.y += 0.1f;
	}
	else if (p.IsPressing(0, "down"))
	{
		pos.y -= 0.1f;
	}
	else if (p.IsPressing(0, "near"))
	{
		pos.z -= 0.1f;
	}
	else if (p.IsPressing(0, "far"))
	{
		pos.z += 0.1f;
	}

	DxLib::MV1SetPosition(model, pos);

	time += 0.5f;
	// �Đ����Ԃ���Ұ��݂̑��Đ����ԂɂȂ�����0�ɖ߂�
	if (time >= totalTime)
	{
		time = 0;
	}

	DxLib::MV1SetAttachAnimTime(model, motion, time);

	(this->*updater)(p);
}

void GamePlaying3DScene::Draw()
{
	DxLib::MV1DrawModel(model);
}