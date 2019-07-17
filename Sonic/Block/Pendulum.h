#pragma once
#include "Block.h"
#include "../Geometry.h"

class Camera;


class Pendulum : public Block
{
private:
	const Camera& camera;

	Vector2f pos;	//現在座標
	float v;		//現在のスピード(絶対値)
	Vector2f vel;	//現在の速度ベクトル
	Vector2 pivot;	//支点(振り子の支点)

public:
	Pendulum(const Vector2& pos, const Camera& camera, unsigned int runLength = 1);
	~Pendulum();

	// ブロック座標とか状態を更新
	void Update()override;

	// ブロック表示
	void Draw()override;
};

