#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;
class GamePlayingScene;

class Player : public Actor
{
private:
	// 状態遷移のためのﾒﾝﾊﾞ関数ﾎﾟｲﾝﾀ
	void (Player::*updater)(const Peripheral& p);

	bool Move(const Peripheral&p);

	void Idle(const Peripheral& p);		// 待機
	void Run(const Peripheral& p);		// 移動
	void Jump(const Peripheral& p);		// ジャンプ
	void Ground(const Peripheral& p);	// 着地
	void Damage(const Peripheral& p);	// 死亡

	Vector2f vel;	// 移動量

public:
	Player(Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw();

	void AdjustY(float adjustY, float grad);
	void OnGround(const int groundY);
	void OnDead();

	// 空中フラグ
	// @param true時が空中
	bool isAerial;
};

