#pragma once
#include "Loader.h"
#include <vector>
#include <map>

class ActionLoader : public Loader
{
private:
	std::map<std::string, std::vector<char>> table;

public:
	ActionLoader();
	~ActionLoader();

	bool Load(std::string path, Data& data)override final;

	void UnLoad(const char* path)override final;
};

class ActionData : public Data
{
	friend ActionLoader;
private:
	std::vector<char> rawData;
	bool IsAvailable();

public:
	std::vector<char> GetRawData()const;
};
