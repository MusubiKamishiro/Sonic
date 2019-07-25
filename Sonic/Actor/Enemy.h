#pragma once
#include "Actor.h"

class Player;
class Spawner;

///敵基底クラス
class Enemy : public Actor
{
	friend Spawner;
private:
	int deadSE;

protected:
	const Player& player;

public:
	Enemy(Camera& camera, Player& player, Vector2f& pos);
	~Enemy();

	virtual void Update(const Peripheral& p) = 0;

	virtual void Draw() = 0;

	// 衝突イベント
	// @param actor 相手アクターオブジェクト
	virtual void OnCollision(Actor& actor);
};

