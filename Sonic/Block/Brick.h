#pragma once
#include "Block.h"
#include "../Geometry.h"

class Camera;

class Brick : public Block
{
private:
	const Camera& camera;

public:
	Brick(const Vector2& pos, const Camera& camera);
	~Brick();

	// �u���b�N���W�Ƃ���Ԃ��X�V
	void Update()override;

	// �u���b�N�\��
	void Draw()override;
};

