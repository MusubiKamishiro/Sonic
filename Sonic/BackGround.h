#pragma once
#include <vector>
#include "Geometry.h"

class Camera;

enum class LayoutType 
{
	norepeat,	// ��񂱃b����p�[�c
	repeat,		// ��苗�����ƂɌJ��Ԃ�
};

// �w�i�̃p�[�c
struct BGObject
{
	int handle;			// �w�i�p�[�c�摜�n���h��
	Vector2 pos;		// ���W
	float rate;			// �ړ����[�g(�������قǓ����Ȃ�)
	LayoutType type;	// �w�i�̔z�u�^�C�v
	int repeatX;		// �J��Ԃ�����
	Size size;			// �g���̃T�C�Y

	BGObject() {}
	BGObject(int h, const Vector2& p, float r, LayoutType lt, int repX, Size s) : handle(h), pos(p), rate(r), type(lt), repeatX(repX), size(s) {}
};

class BackGround
{
private:
	const Camera& camera;
	int img;
	Vector2 ssize;

	std::vector<BGObject> bgParts;

public:
	BackGround(const Camera& camera);
	~BackGround();

	// �w�i�p�[�c��o�^����
	// @param filapath �摜�t�@�C���̃p�X
	// @param pos �������W
	// @param rate ���d�X�N���[���p�̈ړ����[�g
	// @param fromBottom ��������W�v�Z����(�u�[���^)
	// @param type �J��Ԃ��^�C�v
	// @param size �T�C�Y(�f�t�H���g�Ȃ�-1,-1�ƂȂ�摜�̃T�C�Y������)
	// @param repeatX �J��Ԃ���(�f�t�H���g-1�̏ꍇ�摜�̃T�C�Y�ɂȂ�)
	// @remarks �o�^�������ɕ`�悳��܂��B
	// �Ŕw�ʂ͍ŏ��ɍőO�ʂ͍Ō�ɓo�^���Ă��������B
	void AddParts(const char* filepath, const Vector2& pos, float rate, bool fromBottom,
			LayoutType type, Size size = Size(-1, -1), int repeatX = -1);

	// �`��
	void Draw();
};

