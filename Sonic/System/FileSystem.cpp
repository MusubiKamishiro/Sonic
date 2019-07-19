#include "FileSystem.h"
#include "ImageLoader.h"
#include "ActionLoader.h"


FileSystem::FileSystem()
{
	imageLoader = std::unique_ptr<ImageLoader>();
	actionLoader = std::unique_ptr<ActionLoader>();
}


FileSystem::~FileSystem()
{
}

bool FileSystem::Load(const char * filePath, Data & data)
{
	return imageLoader->Load(filePath, data);
}
