#pragma once

class Peripheral;


// ���@��G�@�̊��N���X
class Actor
{
protected:


public:
	Actor();
	virtual ~Actor();

	// ��Ԃ���W�̍X�V
	virtual void Update(const Peripheral& p) = 0;

	// �`��
	virtual void Draw() = 0;
};

