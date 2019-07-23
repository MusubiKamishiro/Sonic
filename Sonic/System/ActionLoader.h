#pragma once
#include "Loader.h"
#include <vector>
#include <map>

class ActionLoader : public Loader
{
private:
	std::map<const char*, std::vector<char>> table;

public:
	ActionLoader();
	~ActionLoader();

	bool Load(const char* path, Data& data)override final;

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
