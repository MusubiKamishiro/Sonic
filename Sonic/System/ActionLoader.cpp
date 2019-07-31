#include "ActionLoader.h"
#include <DxLib.h>


ActionLoader::ActionLoader()
{
}


ActionLoader::~ActionLoader()
{
}

bool ActionLoader::Load(std::string path, Data & data)
{
	ActionData& action = dynamic_cast<ActionData&>(data);

	auto it = table.find(path.c_str());
	if (it == table.end())
	{
		auto size = DxLib::FileRead_size(path.c_str());
		table[path.c_str()].resize(size);
		auto h = DxLib::FileRead_open(path.c_str());

		// �ǂݍ��߂Ȃ�����
		if (h == 0)
		{
			return false;
		}

		// �܂��ǂݍ���łȂ���������ǂݍ���
		DxLib::FileRead_read(table[path.c_str()].data(), size, h);
		DxLib::FileRead_close(h);
		action.rawData = table[path.c_str()];

		// �e�[�u���ɒǉ�
		table.emplace(path, action.rawData);
		return true;
	}
	else
	{
		// ����������n���h����Ԃ�
		action.rawData = table[path.c_str()];
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
