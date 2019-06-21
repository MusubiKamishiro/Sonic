#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class Player;

class Camera
{
private:
	Vector2f initPos;	// �J�����̏������W
	Vector2f pos;		// �J�����̍��W
	Vector2 ssize;
	std::vector<std::shared_ptr<Player>> player;

	// �J�����̏������W�̊m��
	void SubmitPos();

public:
	Camera();
	~Camera();

	// �Ď��v���C���[�̒ǉ�
	// @param	addPlayer	�ǉ��������v���C���[
	void AddPlayer(std::shared_ptr<Player> addPlayer);

	// �Ď��v���C���[�̍폜
	// @param	removePlayer	�폜�������v���C���[
	void RemovePlayer(std::shared_ptr<Player> removePlayer);

	// �X�e�[�W�S�̂̃T�C�Y(�X�N���[���̌��E���W)���Z�b�g����
	// @param	stageSize	�X�e�[�W�S�̂̑傫��
	void SetRange(const Size& stageSize);

	// �J�����ʒu�̍X�V
	void Update();

	// �J�����̌��ݍ��W�̍X�V
	Vector2f GetPos()const;

	// �J�����̏������W����I�t�Z�b�g��Ԃ�
	const Vector2& GetOffset()const;

	// �J�����̎B�e�͈͂�Ԃ�
	const Rect GetViewRange()const;
};

