#pragma once
#include "Scene.h"


class GamePlaying3DScene : public Scene
{
private:
	void (GamePlaying3DScene::*updater)(const Peripheral& p);

	// フェードインの処理を書く
	void FadeinUpdate(const Peripheral& p);
	// フェードアウトの処理を書く
	void FadeoutUpdate(const Peripheral& p);
	// 待機中の処理を書く
	void WaitUpdate(const Peripheral& p);

	int model;
	int motion;
	float time, totalTime;

public:
	GamePlaying3DScene();
	~GamePlaying3DScene();

	// シーンの更新を行う
	void Update(const Peripheral& p);
	// シーンの描画
	void Draw();
};

