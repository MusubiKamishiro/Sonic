#pragma once
#include "Scene.h"


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

	int model;
	int motion;
	float time, totalTime;

public:
	GamePlaying3DScene();
	~GamePlaying3DScene();

	// �V�[���̍X�V���s��
	void Update(const Peripheral& p);
	// �V�[���̕`��
	void Draw();
};

