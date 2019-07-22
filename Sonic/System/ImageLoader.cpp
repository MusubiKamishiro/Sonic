#include "ImageLoader.h"
#include <DxLib.h>


ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}

bool ImageLoader::Load(const char * path, Data & data)
{
	ImageData& img = dynamic_cast<ImageData&>(data);

	// �f�[�^��������Ȃ�������ǂݍ���
	auto it = table.find(path);
	if (it == table.end())
	{
		img.handle = DxLib::LoadGraph(path);
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
		img.handle = table[path];
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
