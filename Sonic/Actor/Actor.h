#pragma once
#include <vector>
#include <map>
#include <string>
#include "../Geometry.h"
#include "../System/ActionLoader.h"

class Peripheral;
class Camera;

// ��`���
enum class RectType
{
	adjust,		// �����߂�����
	attack,		// �U��
	damage,		// ����
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
struct ActData
{
	std::string imgFilePath;	// �摜�̃t�@�C���p�X
	std::map<std::string, ActInfo> animInfo;	// �A�j���[�V�������
};

// ���@��G�@�̊��N���X
class Actor
{
private:
	///ReadActionFile�̎��Ɏg��
	///@param inDst �f�[�^�̈ړ���
	///@param byteNum ����ǂݍ��ޔ͈͂̑傫��
	///@param cursor �J�[�\��, ���܂œǂݍ��񂾈ʒu
	///@param act �A�N�V�����f�[�^
	void ReadData(void* inDst, size_t byteNum, size_t& cursor, ActionData& act);

	// �t�@�C���ǂݍ���
	void ReadActionFile(const std::string& filePath);
	// �L�����̉摜��ݒ�
	void SetActorImage();

protected:
	const Camera& camera;

	ActData actData;	// �A�N�V�����f�[�^

	Vector2f pos;	// ���W
	int img;		// �摜
	bool turnFlag;	// ���]�t���O
	float angle;	// ��]��
	float accel;	// �����x
	
	std::string nowActionName;	// ���݂̃A�N�V������
	int nowCutIndex;			// ���݂̃R�}(���Ԗڂ̃R�}��)
	unsigned int frame;			// �o�߃t���[��

	// �L������ݒ�
	void SetActor(const std::string& filePath);

	// ��Ұ��݂��ڰт�1�i�߂�
	bool ProceedAnimationFile();

	// �A�N�V�����؂�ւ�
	void ChangeAction(const char* actname);

	// �`��
	void Draw();
	/// �������`��\��
	void DebugDraw();

public:
	Actor(Camera& camera);
	virtual ~Actor();

	// ��Ԃ���W�̍X�V
	virtual void Update(const Peripheral& p) = 0;

	// ���W�̎擾
	Vector2f GetPos()const;

	// ��`�̎擾
	Rect GetRect();
	// �������`�̎擾
	std::vector<ActRect> GetActRect();
	// ��`�̏ꏊ�����킹��
	Rect GetHitRect(Rect& rc);
};

