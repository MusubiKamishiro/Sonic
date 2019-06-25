#pragma once
#include <vector>
#include <map>
#include <string>
#include "../Geometry.h"

class Peripheral;
class Camera;

// ��`���
enum class RectType
{
	attack,		// �U��
	damage		// ����
};

// �A�N�V������`��`
struct ActRect
{
	RectType rt;	// ���
	Rect rect;		// �`
};

// �؂蔲�����
struct CutInfo
{
	Rect rect;		// �؂蔲����`
	Vector2 center;	// ���S�_
	int duration;	// �\������
	std::vector<ActRect> actRects;	// �A�N�V������`(1�Ƃ͌���Ȃ�)
};

// �A�N�V�������
struct ActInfo
{
	bool isLoop;	// ���[�v����Ȃ�true
	std::vector<CutInfo> cutInfo;	// �؂蔲�����(1�Ƃ͌���Ȃ�)
};

// �A�N�V�����f�[�^
struct ActionData
{
	std::string imgFilePath;	// �摜�̃t�@�C���p�X
	std::map<std::string, ActInfo> animInfo;	// �A�j���[�V�������
};

// ���@��G�@�̊��N���X
class Actor
{
protected:
	const Camera& camera;

	ActionData actData;

	Vector2f pos;	// ���W
	int img;		// �摜
	bool turnFlag;	// ���]�t���O

	// �t�@�C���ǂݍ���
	void ReadActionFile();

	// ��Ұ��݂��ڰт�1�i�߂�
	bool ProceedAnimationFile();

public:
	Actor(Camera& camera);
	virtual ~Actor();

	// ��Ԃ���W�̍X�V
	virtual void Update(const Peripheral& p) = 0;

	// �`��
	virtual void Draw() = 0;

	// ���W�̎擾
	Vector2f GetPos()const;
};

