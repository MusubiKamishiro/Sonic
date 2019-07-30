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
	// �u���b�N���W�Ƃ���Ԃ��X�V
	virtual void Update() = 0;

	// �u���b�N�\��
	virtual void Draw() = 0;

	// ��`�̎擾
	Rect GetCollider()const;

	Vector2f GetSpeed()const;
};

