#pragma once
#include <memory>
#include <vector>
#include "Scene.h"
#include "../Geometry.h"

class Player;

class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p)override final;
	void FadeoutUpdate(const Peripheral& p)override final;
	void WaitUpdate(const Peripheral& p)override final;

	
	Vector2 ssize;		// 画面サイズ

	std::shared_ptr<Player> player;

public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p)override final;
};
