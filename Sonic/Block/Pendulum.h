#pragma once
#include "Block.h"
#include "../Geometry.h"

class Camera;


class Pendulum : public Block
{
private:
	const Camera& camera;

	Vector2f pos;	//���ݍ��W
	float v;		//���݂̃X�s�[�h(��Βl)
	Vector2f vel;	//���݂̑��x�x�N�g��
	Vector2 pivot;	//�x�_(�U��q�̎x�_)

public:
	Pendulum(const Vector2& pos, const Camera& camera, unsigned int runLength = 1);
	~Pendulum();

	// �u���b�N���W�Ƃ���Ԃ��X�V
	void Update()override;

	// �u���b�N�\��
	void Draw()override;
};

