#pragma once
#include <vector>
#include "Geometry.h"

class Ground;

// �ð�ނ̏��
struct StageInfo
{
	unsigned int id;			// ̧�ق�ID
	unsigned int size;			// ͯ�ނ��������ް�����
	unsigned int mapWidth;		// ϯ�ߑS�̂̉���
	unsigned int mapHeight;		// ϯ�ߑS�̂̏c��
	unsigned char chipWidth;	// 1Ͻ�̉���
	unsigned char chipHeight;	// 1Ͻ�̏c��
	unsigned char layerCount;	// ڲ԰��
	unsigned char bitCount;		// ڲ԰�ް����ޯĶ���
};


class Stage
{
private:
	StageInfo stageInfo;
	std::vector<unsigned char> stageData;	// �X�e�[�W�̃f�[�^

public:
	Stage();
	~Stage();

	// �X�e�[�W�̓ǂݍ���
	//@param stagePath �X�e�[�W�̃p�X
	void ReadStageFile(const char* stagePath, Ground& ground);

	std::vector<unsigned char> GetStageData()const;
};

