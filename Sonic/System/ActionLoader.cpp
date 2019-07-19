#include "ActionLoader.h"



ActionLoader::ActionLoader()
{
}


ActionLoader::~ActionLoader()
{
}

bool ActionLoader::Load(const char * path, Data & data)
{
	return false;
}

void ActionLoader::UnLoad(const char * path)
{
}

std::vector<char> ActionData::GetHandle() const
{
	return handle;
}
