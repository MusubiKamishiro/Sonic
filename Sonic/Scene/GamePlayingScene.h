#pragma once
#include <memory>
#include <vector>
#include "Scene.h"
#include "../Geometry.h"

class Player;
class Camera;
class BackGround;
class Ground;
class Stage;

class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p)override final;
	void FadeoutUpdate(const Peripheral& p)override final;
	void WaitUpdate(const Peripheral& p)override final;

	
	Vector2 ssize;		// 画面サイズ

	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<BackGround> bg;
	std::shared_ptr<Ground> ground;
	std::shared_ptr<Stage> stage;

	int time;
	Segment seg, oldseg;

public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p)override final;
	void Draw()override final;
};
