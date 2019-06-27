#include "Actor.h"
#include <DxLib.h>
#include <assert.h>
#include "../Camera.h"

constexpr float nowVersion = 1.01f;	// ActonTool.exe�̃o�[�W����

void Actor::ReadActionFile()
{
	std::string filePath = "action/player.act";

	// �t�@�C���ǂݍ���
	int handle = DxLib::FileRead_open(filePath.c_str(), false);
	
	// �o�[�W�����`�F�b�N(�������x���f����)
	float version;
	DxLib::FileRead_read(&version, sizeof(version), handle);
	assert(version == nowVersion);

	// �摜�t�@�C���̓ǂݍ���
	int hData;
	DxLib::FileRead_read(&hData, sizeof(hData), handle);
	std::string imgFilePath = "";
	imgFilePath.resize(hData);
	DxLib::FileRead_read(&imgFilePath[0], hData, handle);
	auto ipos = filePath.find_last_of('/') + 1;
	actData.imgFilePath = filePath.substr(0, ipos) + imgFilePath;

	// �A�N�V�������擾
	int actcount = 0;
	DxLib::FileRead_read(&actcount, sizeof(actcount), handle);
	// �A�N�V�����ǂݍ���(�A�N�V���������J��Ԃ�)
	for (int i = 0; i < actcount; ++i)
	{
		// �A�N�V�������̓ǂݍ���
		int actNameSize = 0;
		DxLib::FileRead_read(&actNameSize, sizeof(actNameSize), handle);
		std::string actName = "";
		actName.resize(actNameSize);
		DxLib::FileRead_read(&actName[0], actNameSize, handle);

		ActInfo actInfo;

		// ���[�v���邩���m�F
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), handle);

		// �J�b�g�f�[�^��(�R�}��)���擾
		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), handle);
		actInfo.cutInfo.resize(cutCount);

		// �J�b�g�f�[�^�ǂݍ���(�J�b�g�f�[�^�����J��Ԃ�)
		for (int j = 0; j < cutCount; ++j)
		{
			// �܂��������`�ȊO��ǂݍ���
			DxLib::FileRead_read(&actInfo.cutInfo[j], (sizeof(actInfo.cutInfo[j]) - sizeof(actInfo.cutInfo[j].actRects)), handle);

			// �������`���擾
			int rectCount = 0;
			DxLib::FileRead_read(&rectCount, sizeof(rectCount), handle);

			// �������`���Ȃ���Γǂݍ��݂��X�L�b�v
			if (rectCount == 0)
			{
				continue;
			}
			actInfo.cutInfo[j].actRects.resize(rectCount);
			DxLib::FileRead_read(&actInfo.cutInfo[j].actRects, sizeof(ActRect) * rectCount, handle);
		}

		// �}�b�v�ɓo�^
		actData.animInfo[actName] = actInfo;
	}

	// �Ō�̓t�@�C�������
	DxLib::FileRead_close(handle);
}

bool Actor::ProceedAnimationFile()
{
	// �\�����Ԃ𒴂��Ă�Ȃ玟�̃R�}��
	if (frame < actData.animInfo[nowActionName].cutInfo[nowCutIndex].duration)
	{
		++frame;
	}
	else
	{
		frame = 0;
		if (nowCutIndex < (actData.animInfo[nowActionName].cutInfo.size() - 1))
		{
			++nowCutIndex;
		}
		else
		{
			nowCutIndex = 0;
		}
	}

	return false;
}

void Actor::ChangeAction(const char * actname)
{
	nowActionName = actname;
	nowCutIndex = 0;
	frame = 0;
}

void Actor::Draw()
{
	auto& offset = camera.GetViewRange();
	auto& nowAct = actData.animInfo[nowActionName].cutInfo[nowCutIndex];

	// ���]�����������S�����킹�邽��
	int centerX = 0;
	centerX = turnFlag ? nowAct.rect.Width() - nowAct.center.x : nowAct.center.x;

	DxLib::DrawRectRotaGraph2(pos.x - offset.Left(), pos.y/* - offset.Top()*/, nowAct.rect.Left(), nowAct.rect.Top(),
		nowAct.rect.Width(), nowAct.rect.Height(), centerX, nowAct.center.y, 2.0f, turnFlag ? -angle : angle, img, true, turnFlag);
}

Actor::Actor(Camera& camera) : camera(camera)
{
	ChangeAction("idle");
	angle = 0.0f;
	accel = 0.0f;
}


Actor::~Actor()
{
}

Vector2f Actor::GetPos() const
{
	return pos;
}
