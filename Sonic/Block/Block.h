#pragma once
#include "../Geometry.h"

class Camera;

class Block
{
protected:
	Block(const Vector2& pos, const Camera& camera, int count = 1);

	int img;
	Rect rect;
	const int blockSize;
	Vector2f speed;

public:
	// ブロック座標とか状態を更新
	virtual void Update() = 0;

	// ブロック表示
	virtual void Draw() = 0;

	// 矩形の取得
	Rect GetCollider()const;

	Vector2f GetSpeed()const;
};

