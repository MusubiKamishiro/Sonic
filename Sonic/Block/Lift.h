#pragma once
#include "Block.h"

class Camera;


class Lift : public Block
{
private:
	const Camera& camera;

	int moveCount;

public:
	Lift(const Vector2& pos, const Camera& camera, unsigned int runLength = 1);
	~Lift();

	// ブロック座標とか状態を更新
	void Update()override;

	// ブロック表示
	void Draw()override;
};

