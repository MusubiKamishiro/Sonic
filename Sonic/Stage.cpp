#include "Stage.h"
#include <DxLib.h>
#include <map>
#include <algorithm>
#include "Ground.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::ReadStageFile(const char * stagePath, Ground& ground)
{
	// �t�@�C���ǂݍ���
	int handle = DxLib::FileRead_open(stagePath, false);
	DxLib::FileRead_read(&stageInfo, sizeof(stageInfo), handle);

	std::vector<unsigned char> beforeReplaceData;

	stageData.resize(stageInfo.mapHeight * stageInfo.mapWidth);
	beforeReplaceData.resize(stageData.size());
	DxLib::FileRead_read(&beforeReplaceData[0], beforeReplaceData.size(), handle);

	std::map<unsigned char, std::vector<Vector2f>> terraPositions;	// terra...���e����ő�n
	// �_���W�f�[�^�ɕϊ�
	for (int i = 0; i < beforeReplaceData.size(); ++i)
	{
		auto no = beforeReplaceData[i];
		if (no > 0)
		{
			terraPositions[no].emplace_back((i % stageInfo.mapWidth) * stageInfo.chipWidth, (i / stageInfo.mapWidth) * stageInfo.chipHeight);
		}
	}

	// �\�[�g
	for (auto& terraPos : terraPositions)
	{
		std::sort(terraPos.second.begin(), terraPos.second.end(), [](const Vector2f& lpos, const Vector2f& rpos) { return lpos.x < rpos.x; });
	}

	// �n�ʒǉ�
	for (auto& terra : terraPositions)
	{
		auto it = terra.second.begin();
		for (; (it + 1) != terra.second.end(); ++it) 
		{
			ground.AddSegment(*it, *(it + 1));
		}
		terra.second.clear();//�_�f�[�^�͂����K�v�Ȃ�
	}

	// �Ō�̓t�@�C������悤��
	DxLib::FileRead_close(handle);
}

std::vector<unsigned char> Stage::GetStageData() const
{
	return stageData;
}
