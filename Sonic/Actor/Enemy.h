#pragma once
#include <memory>
#include "Actor.h"

class Player;
class Spawner;

///敵基底クラス
class Enemy : public Actor
{
	friend Spawner;
private:
	

protected:
	///自分のクローンを返す
	virtual std::shared_ptr<Enemy> MakeClone() = 0;

	const Player& player;

	///プレイヤーの位置を知る
	void AimPlayer();

	bool isAvailable = true;
	int deadSE;

public:
	Enemy(const Camera& camera, const Player& player, const Vector2f& pos);
	~Enemy();

	virtual void Update(const Peripheral& p) = 0;

	virtual void Draw() = 0;

	// 衝突イベント
	// @param actor 相手アクターオブジェクト
	virtual void OnCollision(Actor& actor);

	bool GetIsAvailable();
};

