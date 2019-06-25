#include "Actor.h"
#include <DxLib.h>
#include <assert.h>

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
	std::string imgFilePath = "";
	int hData;
	DxLib::FileRead_read(&hData, sizeof(hData), handle);
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

	}

	// �t�@�C�������
	DxLib::FileRead_close(handle);
}

bool Actor::ProceedAnimationFile()
{
	return false;
}

Actor::Actor(Camera& camera) : camera(camera)
{
}


Actor::~Actor()
{
}

Vector2f Actor::GetPos() const
{
	return pos;
}
