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
	// �u���b�N���W�Ƃ���Ԃ��X�V
	virtual void Update() = 0;

	// �u���b�N�\��
	virtual void Draw() = 0;

	// �Փ˃C�x���g
	// @param actor ������A�N�^�[�I�u�W�F�N�g
	// @param col �Փ˂����Ƃ��̏��Ƃ��ẴR���C�_�[�I�u�W�F�N�g
	//virtual void OnCollision(Actor* actor, const BlockCollider& col) = 0;

	// �����������Ă�R���C�_�[��Ԃ�
	//const BlockCollider& GetCollider()const;

	// ��`�̎擾
	Rect GetCollider()const;
};

