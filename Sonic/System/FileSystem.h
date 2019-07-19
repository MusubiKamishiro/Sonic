#pragma once
#include <memory>

class Loader;
class Data;

class FileSystem
{
private:
	std::unique_ptr<Loader> imageLoader;
	std::unique_ptr<Loader> actionLoader;
	//std::unique_ptr<Loader> levelLoader;

public:
	FileSystem();
	~FileSystem();

	bool Load(const char* filePath, Data& data);
};

