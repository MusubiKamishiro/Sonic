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

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	
	Vector2 ssize;		// ��ʃT�C�Y

	std::shared_ptr<Player> player;


	std::unique_ptr<SceneManager> sceneManager;
	
public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);
};
