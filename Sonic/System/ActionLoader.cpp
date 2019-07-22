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

	auto size = DxLib::FileRead_size(path);
	table[path].resize(size);
	auto h = DxLib::FileRead_open(path);

	if (h == 0)
	{
		return false;
	}

	DxLib::FileRead_read(table[path].data(), size, h);
	DxLib::FileRead_close(h);
	action.rawData = table[path];

	return true;
}

void ActionLoader::UnLoad(const char * path)
{
}

std::vector<char> ActionData::GetRawData() const
{
	return rawData;
}
