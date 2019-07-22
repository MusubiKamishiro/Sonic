#include "FileSystem.h"
#include "Loader.h"
#include "ImageLoader.h"
#include "ActionLoader.h"


FileSystem::FileSystem()
{
	imageLoader.reset(new ImageLoader());
	actionLoader = std::unique_ptr<ActionLoader>();

	loaders["bmp"] = loaders["png"] = loaders["jpg"] = std::make_shared<ImageLoader>();
	loaders["act"] = std::make_shared<ActionLoader>();
}


FileSystem::~FileSystem()
{
}

std::string FileSystem::GetExtension(const char* path)
{
	std::string str = path;
	auto idx = str.rfind('.') + 1;
	return str.substr(idx, str.length() - idx);
}

bool FileSystem::Load(const char * filePath, Data & data)
{
	auto ext = GetExtension(filePath);
	return loaders[ext]->Load(filePath, data);
}
