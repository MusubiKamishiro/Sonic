#pragma once
#include "Block.h"
#include "../Geometry.h"

class Camera;


class Slide : public Block
{
private:
	const Camera& camera;

	int moveCount;

public:
	Slide(const Vector2& pos, const Camera& camera);
	~Slide();

	// ブロック座標とか状態を更新
	void Update()override;

	// ブロック表示
	void Draw()override;
};

