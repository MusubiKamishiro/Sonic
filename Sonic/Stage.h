#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class Ground;
class Block;
class BlockFactory;

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
	std::vector<std::shared_ptr<Block>> blockData;	// ブロックのデータ

public:
	Stage();
	~Stage();

	// ステージの読み込み
	//@param stagePath ステージのパス
	void ReadStageFile(const char* stagePath, Ground& ground, BlockFactory& blockFactory);

	std::vector<unsigned char> GetStageData()const;
	std::vector<std::shared_ptr<Block>> GetBlockData()const;
};

