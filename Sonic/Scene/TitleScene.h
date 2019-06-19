#pragma once
#include "Scene.h"
#include <memory>


class TitleScene : public Scene
{
private:
	int titleImage;	// ﾀｲﾄﾙ画像

	void (TitleScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p)override final;
	void FadeoutUpdate(const Peripheral& p)override final;
	void WaitUpdate(const Peripheral& p)override final;

	int timeCount;	// Press 'A' Button を点滅させるためのカウント


public:
	TitleScene();
	~TitleScene();

	void Update(const Peripheral& p)override final;
};

