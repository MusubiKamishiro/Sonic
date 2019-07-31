#pragma once
#include <vector>
#include "Scene.h"
#include "../Geometry.h"

class Player;
class Camera;
class BackGround;
class Ground;
class Stage;
class Collider;

class OnetimeSpawner;
class Enemy;

class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p)override final;
	void FadeoutUpdate(const Peripheral& p)override final;
	void WaitUpdate(const Peripheral& p)override final;

	void HitCheck();
	void DebugDraw();

	Vector2 ssize;		// âÊñ ÉTÉCÉY

	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<BackGround> bg;
	std::shared_ptr<Ground> ground;
	std::shared_ptr<Stage> stage;
	std::shared_ptr<Collider> collider;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<OnetimeSpawner>> spawners;

	int time;
	Segment seg, oldseg;

	int groundy;
	int breakSound;
	Vector2f adjustSpeed;

public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p)override final;
	void Draw()override final;
};
