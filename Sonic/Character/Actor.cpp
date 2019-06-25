#include "Actor.h"
#include <DxLib.h>
#include <assert.h>

constexpr float nowVersion = 1.01f;	// ActonTool.exeのバージョン

void Actor::ReadActionFile()
{
	std::string filePath = "action/player.act";

	// ファイル読み込み
	int handle = DxLib::FileRead_open(filePath.c_str(), false);
	
	// バージョンチェック(違ったら警告吐くよ)
	float version;
	DxLib::FileRead_read(&version, sizeof(version), handle);
	assert(version == nowVersion);

	// 画像ファイルの読み込み
	std::string imgFilePath = "";
	int hData;
	DxLib::FileRead_read(&hData, sizeof(hData), handle);
	imgFilePath.resize(hData);
	DxLib::FileRead_read(&imgFilePath[0], hData, handle);
	auto ipos = filePath.find_last_of('/') + 1;
	actData.imgFilePath = filePath.substr(0, ipos) + imgFilePath;

	// アクション数取得
	int actcount = 0;
	DxLib::FileRead_read(&actcount, sizeof(actcount), handle);
	// アクション読み込み(アクション数分繰り返す)
	for (int i = 0; i < actcount; ++i)
	{

	}

	// ファイルを閉じる
	DxLib::FileRead_close(handle);
}

bool Actor::ProceedAnimationFile()
{
	return false;
}

Actor::Actor(Camera& camera) : camera(camera)
{
}


Actor::~Actor()
{
}

Vector2f Actor::GetPos() const
{
	return pos;
}
