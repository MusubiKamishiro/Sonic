#pragma once
#include "Block.h"
#include "../Geometry.h"

class Camera;


class Lift : public Block
{
private:
	const Camera& camera;

	int moveCount;
	int speed;

public:
	Lift(const Vector2& pos, const Camera& camera, unsigned int runLength = 1);
	~Lift();

	// �u���b�N���W�Ƃ���Ԃ��X�V
	void Update()override;

	// �u���b�N�\��
	void Draw()override;
};

