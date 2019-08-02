#pragma once
#include "Scene.h"
#include <vector>
#include <DxLib.h>


class GamePlaying3DScene : public Scene
{
private:
	void (GamePlaying3DScene::*updater)(const Peripheral& p);

	// �t�F�[�h�C���̏���������
	void FadeinUpdate(const Peripheral& p);
	// �t�F�[�h�A�E�g�̏���������
	void FadeoutUpdate(const Peripheral& p);
	// �ҋ@���̏���������
	void WaitUpdate(const Peripheral& p);

	std::vector<int> models;
	DxLib::VECTOR cameraPos;	// �J�����̎��_
	DxLib::VECTOR targetPos;	// �^�[�Q�b�g�̍��W(�����_)
	int motion;
	float time, totalTime;

	bool loadFlag = false;
	int ddr = 0;

public:
	GamePlaying3DScene();
	~GamePlaying3DScene();

	// �V�[���̍X�V���s��
	void Update(const Peripheral& p);
	// �V�[���̕`��
	void Draw();
};

