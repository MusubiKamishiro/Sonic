#include "Stage.h"
#include <DxLib.h>
#include <map>
#include <algorithm>
#include "Ground.h"
#include "Block/BlockFactory.h"
#include "Spawner/SpawnerFactory.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::ReadStageFile(const char* stagePath, Ground& ground, Player& player, Camera& camera)
{
	// ファイル読み込み
	int handle = DxLib::FileRead_open(stagePath, false);
	DxLib::FileRead_read(&stageInfo, sizeof(stageInfo), handle);

	stageData.resize(stageInfo.mapHeight * stageInfo.mapWidth);

	// 地面の追加に関して
	std::vector<unsigned char> beforeReplaceData;
	beforeReplaceData.resize(stageData.size());
	DxLib::FileRead_read(&beforeReplaceData[0], beforeReplaceData.size(), handle);

	std::map<unsigned char, std::vector<Vector2f>> terraPositions;	// terra...ラテン語で大地
	// 点座標データに変換
	for (int i = 0; i < beforeReplaceData.size(); ++i)
	{
		auto no = beforeReplaceData[i];
		if (no > 0)
		{
			terraPositions[no].emplace_back((i % stageInfo.mapWidth) * stageInfo.chipWidth/* * 2*/, (i / stageInfo.mapWidth) * (stageInfo.chipHeight/* * 2*/));
		}
	}

	// ソート
	for (auto& terraPos : terraPositions)
	{
		std::sort(terraPos.second.begin(), terraPos.second.end(), [](const Vector2f& lpos, const Vector2f& rpos) { return lpos.x < rpos.x; });
	}

	// 地面追加
	for (auto& terra : terraPositions)
	{
		auto it = terra.second.begin();
		for (; (it + 1) != terra.second.end(); ++it) 
		{
			// 地面が端かどうかを調べて登録
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
	
	// ブロック(障害物など)の追加に関して
	blockFactory.reset(new BlockFactory(camera));
	std::vector<unsigned char> blockDatas;
	blockDatas.resize(stageData.size());
	DxLib::FileRead_read(&blockDatas[0], blockDatas.size(), handle);

	for(int idxY = 0; idxY < stageInfo.mapHeight; ++idxY)
	{
		for (int idxX = 0; idxX < stageInfo.mapWidth; ++idxX)
		{
			auto no = blockDatas[idxX + idxY * stageInfo.mapWidth];
			if (no > 1/*0*/)
			{
				unsigned int runLength = 1;
				if (no != 1)
				{
					for (idxX = ++idxX; idxX < stageInfo.mapWidth; ++idxX)
					{
						if (blockDatas[idxX + idxY * stageInfo.mapWidth] == no)
						{
							++runLength;
						}
						else
						{
							--idxX;
							break;
						}
					}
				}

				Vector2 pos = Vector2(idxX * stageInfo.chipWidth + stageInfo.chipWidth / 2, idxY * stageInfo.chipHeight + stageInfo.chipHeight / 2);
				blockData.push_back(blockFactory->Create(BlockType(no - 1), pos, runLength));
			}
		}
	}

	// 敵キャラの追加に関して
	// 敵ではなくスポナーを使うよ
	spawnerFactory.reset(new SpawnerFactory(camera, player));
	std::vector<unsigned char> enemyDatas;
	enemyDatas.resize(stageData.size());
	DxLib::FileRead_read(&enemyDatas[0], enemyDatas.size(), handle);
	for (int idxY = 0; idxY < stageInfo.mapHeight; ++idxY)
	{
		for (int idxX = 0; idxX < stageInfo.mapWidth; ++idxX)
		{
			auto no = enemyDatas[idxX + idxY * stageInfo.mapWidth];
			if ((no > 0) && (no < 3))
			{
				Vector2f pos = Vector2f(idxX * stageInfo.chipWidth + stageInfo.chipWidth / 2, idxY * stageInfo.chipHeight + stageInfo.chipHeight / 2);
				spawnerData.push_back(spawnerFactory->Create(SpawnerType(no - 1), pos));
			}
		}
	}

	// イベントの追加に関して
	// コインとかね
	std::vector<unsigned char> eventDatas;
	eventDatas.resize(stageData.size());
	DxLib::FileRead_read(&eventDatas[0], eventDatas.size(), handle);
	for (int idxY = 0; idxY < stageInfo.mapHeight; ++idxY)
	{
		for (int idxX = 0; idxX < stageInfo.mapWidth; ++idxX)
		{
			auto no = eventDatas[idxX + idxY * stageInfo.mapWidth];
			if ((no > 0) && (no < 3))
			{
				Vector2f pos = Vector2f(idxX * stageInfo.chipWidth + stageInfo.chipWidth / 2, idxY * stageInfo.chipHeight + stageInfo.chipHeight / 2);
				//spawnerData.push_back(spawnerFactory->Create(SpawnerType(no - 1), pos));
			}
		}
	}


	// 最後はファイルを閉じようね
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

std::vector<std::shared_ptr<Spawner>> Stage::GetSpawnerData() const
{
	return spawnerData;
}
