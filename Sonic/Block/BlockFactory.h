#pragma once
#include <memory>
#include "../Geometry.h"

class Camera;
class Block;


// ステージに設置するブロックの種類
enum BlockType
{
	brick,		// 固定ブロック
	slide,		// 左右に移動する奴
	lift,		// 上下に移動する奴
	pendulum,	// 振り子で移動する奴
	broken,		// 乗ったら崩壊する奴(もしくは落ちるやつ)
};


class BlockFactory
{
private:
	const Camera& camera;

public:
	BlockFactory(const Camera& camera);
	~BlockFactory();

	// ブロックを生成する
	// @param type どの種別のブロックを生成するか
	// @param pos どこに生成するか
	std::shared_ptr<Block> Create(BlockType type, const Vector2& pos, unsigned int runLength);
};

