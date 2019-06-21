#pragma once
#include "Geometry.h"

class Camera;

enum class LayoutType 
{
	norepeat,	// ��񂱃b����p�[�c
	repeat,		// ��苗�����ƂɌJ��Ԃ�
};

class BackGround
{
private:
	const Camera& camera;
	int img;
	Vector2 ssize;

	// �w�i�p�[�c��o�^����
	// @param filapath �摜�t�@�C���p�X
	// @param pos �������W
	// @param rate ���d�X�N���[���p�ړ����[�g
	// @param fromBottom ��������W�v�Z����(�u�[���^)
	// @param type �J��Ԃ��^�C�v
	// @param size �T�C�Y(�f�t�H���g�Ȃ�-1,-1�ƂȂ�摜�̃T�C�Y������)
	// @param repeatX �J��Ԃ���(�f�t�H���g-1�̏ꍇ�摜�̃T�C�Y�ɂȂ�)
	// @remarks �o�^�������ɕ`�悳��܂��B
	// �Ŕw�ʂ͍ŏ��ɍőO�ʂ͍Ō�ɓo�^���Ă��������B
	void AddParts(const char* filepath, const Vector2& pos, float rate, bool fromBottom, 
		LayoutType type, Size size = Size(-1, -1), int repeatX = -1);

public:
	BackGround(const Camera& camera);
	~BackGround();

	// �`��
	void Draw();
};

