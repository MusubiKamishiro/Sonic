#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class Player;

class Camera
{
private:
	Vector2f pos;	// カメラの座標
	std::vector<std::shared_ptr<Player>> player;

public:
	Camera();
	~Camera();

	// 監視プレイヤーの追加
	// @param	addPlayer	追加したいプレイヤー
	void AddPlayer(std::shared_ptr<Player> addPlayer);

	// 監視プレイヤーの削除
	// @param	removePlayer	削除したいプレイヤー
	void RemovePlayer(std::shared_ptr<Player> removePlayer);

	// ステージ全体のサイズ(スクロールの限界座標)をセットする
	// @param	stageSize	ステージ全体の大きさ
	void SetRange(const Size& stageSize);

	// カメラ位置の更新
	void Update();

	// カメラの現在座標の更新
	Vector2f GetPos()const;

	// カメラの撮影範囲を返す
	const Rect& GetViewRange()const;
};

