#include "ImageLoader.h"
#include <DxLib.h>


ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}

bool ImageLoader::Load(std::string path, Data & data)
{
	ImageData& img = dynamic_cast<ImageData&>(data);

	// �f�[�^��������Ȃ�������ǂݍ���
	auto it = table.find(path.c_str());
	if (it == table.end())
	{
		img.handle = DxLib::LoadGraph(path.c_str());
		if (img.handle == -1)
		{
			return false;
		}
		else
		{
			table.emplace(path, img.handle);
			return true;
		}
	}
	else
	{
		// ����������n���h����Ԃ�
		img.handle = table[path.c_str()];
		return true;
	}
	return false;
}

void ImageLoader::UnLoad(const char * path)
{
}

bool ImageData::IsAvailable()
{
	return true;
}

int ImageData::GetHandle() const
{
	return handle;
}
