#pragma once
#include "Scene.h"
#include <memory>



class TitleScene : public Scene
{
private:
	int titleImage;	// ���ى摜

	void (TitleScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	int timeCount;	// Press 'A' Button ��_�ł����邽�߂̃J�E���g


	std::unique_ptr<SceneManager> sceneManager;

public:
	TitleScene();
	~TitleScene();

	void Update(const Peripheral& p);
};

