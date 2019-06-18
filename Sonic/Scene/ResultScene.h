#pragma once
#include "Scene.h"

class ResultScene : public Scene
{
private:
	void (ResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	int resultImage;


	std::unique_ptr<SceneManager> sceneManager;

public:
	ResultScene();
	~ResultScene();

	void Update(const Peripheral& p);
};

