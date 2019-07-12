#include "Stage.h"
#include <DxLib.h>
#include <map>
#include <algorithm>
#include "Ground.h"
#include "Block/Block.h"
#include "Block/BlockFactory.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::ReadStageFile(const char * stagePath, Ground& ground, BlockFactory& blockFactory)
{
	// �t�@�C���ǂݍ���
	int handle = DxLib::FileRead_open(stagePath, false);
	DxLib::FileRead_read(&stageInfo, sizeof(stageInfo), handle);

	stageData.resize(stageInfo.mapHeight * stageInfo.mapWidth);

	// �n�ʂ̒ǉ��Ɋւ���
	std::vector<unsigned char> beforeReplaceData;
	beforeReplaceData.resize(stageData.size());
	DxLib::FileRead_read(&beforeReplaceData[0], beforeReplaceData.size(), handle);

	std::map<unsigned char, std::vector<Vector2f>> terraPositions;	// terra...���e����ő�n
	// �_���W�f�[�^�ɕϊ�
	for (int i = 0; i < beforeReplaceData.size(); ++i)
	{
		auto no = beforeReplaceData[i];
		if (no > 0)
		{
			terraPositions[no].emplace_back((i % stageInfo.mapWidth) * stageInfo.chipWidth, (i / stageInfo.mapWidth) * (stageInfo.chipHeight));
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
			// �n�ʂ��[���ǂ����𒲂ׂēo�^
			auto type = EdgeType::none;
			if (it == terra.second.begin())
			{
				type = EdgeType::left;
			}
			else if (it + 2 == terra.second.end())
			{
				type = EdgeType::right;
			}
			ground.AddSegment(*it, *(it + 1), type);
		}
	}
	
	// �u���b�N(��Q���Ȃ�)�̒ǉ��Ɋւ���
	std::vector<unsigned char> blockDatas;
	blockDatas.resize(stageData.size());
	DxLib::FileRead_read(&blockDatas[0], blockDatas.size(), handle);

	for (int i = 0; i < blockDatas.size(); ++i)
	{
		auto no = blockDatas[i];
		if (no > 0)
		{
			Vector2 pos = Vector2((i % stageInfo.mapWidth) * stageInfo.chipWidth + stageInfo.chipWidth / 2, (i / stageInfo.mapWidth) * stageInfo.chipHeight + stageInfo.chipHeight / 2);
			blockData.push_back(blockFactory.Create(BlockType(no-1), pos));
		}
	}

	// �Ō�̓t�@�C������悤��
	DxLib::FileRead_close(handle);
}

std::vector<unsigned char> Stage::GetStageData() const
{
	return stageData;
}

std::vector<std::shared_ptr<Block>> Stage::GetBlockData() const
{
	return blockData;
}
