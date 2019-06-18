#pragma once
#include <memory>
#include "Scene.h"
#include "../Geometry.h"

class PauseScene : public Scene
{
private:
	void (PauseScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
public:
	PauseScene();
	~PauseScene();

	void Update(const Peripheral& p);
};

