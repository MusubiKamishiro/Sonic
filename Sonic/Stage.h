#pragma once
#include <vector>
#include "Geometry.h"

class Ground;

// ｽﾃｰｼﾞの情報
struct StageInfo
{
	unsigned int id;			// ﾌｧｲﾙのID
	unsigned int size;			// ﾍｯﾀﾞを除いたﾃﾞｰﾀｻｲｽﾞ
	unsigned int mapWidth;		// ﾏｯﾌﾟ全体の横幅
	unsigned int mapHeight;		// ﾏｯﾌﾟ全体の縦幅
	unsigned char chipWidth;	// 1ﾏｽの横幅
	unsigned char chipHeight;	// 1ﾏｽの縦幅
	unsigned char layerCount;	// ﾚｲﾔｰ数
	unsigned char bitCount;		// ﾚｲﾔｰﾃﾞｰﾀのﾋﾞｯﾄｶｳﾝﾄ
};


class Stage
{
private:
	StageInfo stageInfo;
	std::vector<unsigned char> stageData;	// ステージのデータ

public:
	Stage();
	~Stage();

	// ステージの読み込み
	//@param stagePath ステージのパス
	void ReadStageFile(const char* stagePath, Ground& ground);

	std::vector<unsigned char> GetStageData()const;
};

