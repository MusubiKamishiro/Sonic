#pragma once
#include "Scene.h"
#include "../Geometry.h"

class PauseScene : public Scene
{
private:
	void (PauseScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p)override final;
	void FadeoutUpdate(const Peripheral& p)override final;
	void WaitUpdate(const Peripheral& p)override final;

	int img;
	Vector2 ssize;

public:
	PauseScene();
	~PauseScene();

	void Update(const Peripheral& p)override final;
	void Draw()override final;
};

