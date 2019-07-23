#include "ActionLoader.h"
#include <DxLib.h>


ActionLoader::ActionLoader()
{
}


ActionLoader::~ActionLoader()
{
}

bool ActionLoader::Load(const char * path, Data & data)
{
	ActionData& action = dynamic_cast<ActionData&>(data);

	auto it = table.find(path);
	if (it == table.end())
	{
		auto size = DxLib::FileRead_size(path);
		table[path].resize(size);
		auto h = DxLib::FileRead_open(path);

		// 読み込めなかった
		if (h == 0)
		{
			return false;
		}

		// まだ読み込んでなかったから読み込み
		DxLib::FileRead_read(table[path].data(), size, h);
		DxLib::FileRead_close(h);
		action.rawData = table[path];

		// テーブルに追加
		table.emplace(path, action.rawData);
		return true;
	}
	else
	{
		// 見つかったらハンドルを返す
		action.rawData = table[path];
		return true;
	}
	return false;
}

void ActionLoader::UnLoad(const char * path)
{
}

bool ActionData::IsAvailable()
{
	return false;
}

std::vector<char> ActionData::GetRawData() const
{
	return rawData;
}
