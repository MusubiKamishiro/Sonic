#pragma once
#include "Loader.h"
#include <map>


class ImageLoader : public Loader
{
private:
	std::map<const char*, int> table;

public:
	ImageLoader();
	~ImageLoader();

	bool Load(const char* path, Data& data)override final;

	void UnLoad(const char* path)override final;
};


class ImageData : public Data
{
	friend ImageLoader;
private:
	int handle;

public:
	int GetHandle()const;
};
