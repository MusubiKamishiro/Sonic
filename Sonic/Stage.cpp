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
			terraPositions[no].emplace_back((i % stageInfo.mapWidth) * stageInfo.chipWidth, (i / stageInfo.mapWidth) * stageInfo.chipHeight);
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
	std::vector<unsigned char> blockData;
	blockData.resize(stageData.size());
	DxLib::FileRead_read(&blockData[0], blockData.size(), handle);

	std::vector<Vector2> blockPositions;
	// 点座標データに変換
	for (int i = 0; i < blockData.size(); ++i)
	{
		auto no = blockData[i];
		if (no > 0)
		{
			blockPositions.emplace_back((i % stageInfo.mapWidth) * stageInfo.chipWidth, (i / stageInfo.mapWidth) * stageInfo.chipHeight);
		}
	}
	// ソート
	std::sort(blockPositions.begin(), blockPositions.end(), [](const Vector2& lpos, const Vector2& rpos) { return lpos.x < rpos.x; });

	// 最後はファイルを閉じようね
	DxLib::FileRead_close(handle);
}

std::vector<unsigned char> Stage::GetStageData() const
{
	return stageData;
}
