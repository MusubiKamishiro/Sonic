#pragma once
#include "Scene.h"
#include <vector>
#include <DxLib.h>


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

	std::vector<int> models;
	DxLib::VECTOR cameraPos;	// カメラの視点
	DxLib::VECTOR targetPos;	// ターゲットの座標(注視点)
	int motion;
	float time, totalTime;

	bool loadFlag = false;
	int ddr = 0;

public:
	GamePlaying3DScene();
	~GamePlaying3DScene();

	// シーンの更新を行う
	void Update(const Peripheral& p);
	// シーンの描画
	void Draw();
};

