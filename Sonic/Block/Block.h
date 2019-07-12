#pragma once
#include "../Geometry.h"

class Camera;

class Block
{
protected:
	Block(const Rect& rect, const Camera& camera);

	int img;
	Rect rect;

private:

public:
	// ブロック座標とか状態を更新
	virtual void Update() = 0;

	// ブロック表示
	virtual void Draw() = 0;

	// 矩形の取得
	Rect GetCollider()const;
};

