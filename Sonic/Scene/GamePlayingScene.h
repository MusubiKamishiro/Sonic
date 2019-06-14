#pragma once
#include <memory>
#include <vector>
#include "Scene.h"
#include "../Geometry.h"


class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	
	Vector2 pos[2];
	Vector2 ssize;

	int bg1;
	int bg2;
	
public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);
};
