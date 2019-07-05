#pragma once
#include <memory>
#include "../Geometry.h"

// ステージに設置するブロックの種類
enum BlockType
{
	brick,		// 固定ブロック
	lift,		// 上下に移動する奴
	slide,		// 左右に移動する奴
	pendulum,	// 振り子で移動する奴
	broken,		// 乗ったら崩壊する奴(もしくは落ちるやつ)
};

class Actor;
class Camera;
class BlockCollider;
class Block;


class BlockFactory
{
private:
	

public:
	BlockFactory(const Camera& camera);
	~BlockFactory();

	// ブロックを生成する
	// @param type どの種別のブロックを生成するか
	// @param pos どこに生成するか
	std::unique_ptr<Block> Create(BlockType type, const Camera& camera, const Vector2& pos);
};

