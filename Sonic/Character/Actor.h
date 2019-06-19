#pragma once
#include "../Geometry.h"

class Peripheral;



// ���@��G�@�̊��N���X
class Actor
{
protected:
	Vector2f pos;	// ���W
	int img;		// �摜
	bool turnFlag;	// ���]�t���O

public:
	Actor();
	virtual ~Actor();

	// ��Ԃ���W�̍X�V
	virtual void Update(const Peripheral& p) = 0;

	// �`��
	virtual void Draw() = 0;

	// ���W�̎擾
	Vector2f GetPos()const;
};

