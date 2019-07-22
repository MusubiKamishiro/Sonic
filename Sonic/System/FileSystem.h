#pragma once
#include <memory>
#include <map>
#include <string>

class Loader;
class Data;

class FileSystem
{
private:
	std::unique_ptr<Loader> imageLoader;
	std::unique_ptr<Loader> actionLoader;
	//std::unique_ptr<Loader> levelLoader;

	std::map<std::string, std::shared_ptr<Loader>> loaders;

	///�g���q�̒��o
	///����𗘗p����,�ǂ�Load���g�p���邩�����肷��
	std::string GetExtension(const char* path);

public:
	FileSystem();
	~FileSystem();

	bool Load(const char* filePath, Data& data);
};

