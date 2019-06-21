#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class Player;

class Camera
{
private:
	Vector2f initPos;	// カメラの初期座標
	Vector2f pos;		// カメラの座標
	Vector2 ssize;
	std::vector<std::shared_ptr<Player>> player;

	// カメラの初期座標の確定
	void SubmitPos();

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

	// カメラの初期座標からオフセットを返す
	const Vector2& GetOffset()const;

	// カメラの撮影範囲を返す
	const Rect GetViewRange()const;
};

