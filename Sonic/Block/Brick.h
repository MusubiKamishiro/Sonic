#pragma once
#include "Block.h"

class Camera;

class Brick : public Block
{
private:
	const Camera& camera;

public:
	Brick(const Camera& camera);
	~Brick();

	// ブロック座標とか状態を更新
	void Update()override;

	// ブロック表示
	void Draw()override;
};

