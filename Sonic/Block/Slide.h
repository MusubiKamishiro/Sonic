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

	// �u���b�N���W�Ƃ���Ԃ��X�V
	void Update()override;

	// �u���b�N�\��
	void Draw()override;
};

