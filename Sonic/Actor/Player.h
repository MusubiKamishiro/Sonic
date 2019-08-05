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
	void JumpCheck(const Peripheral& p);// ジャンプチェック
	void Ground(const Peripheral& p);	// 着地
	void Dead(const Peripheral& p);	// 死亡

	int jumpButtonPressing;	// ジャンプボタンが押されてる時間

	int jumpSound;
	int deadSound;
	int respawnTime;
	
public:
	Player(const Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw();

	void OnGround(const int groundY);
	void OnDead();

	Vector2f GetVel()const;
	void AdjustMove(Vector2f speed);

	// ブロックの上にいるかどうかの判定
	// @param true時が乗ってる
	bool onflag;

	void AdjustPos(const Vector2f& offset);

	void SetJumpPower();

	bool deadflag = false;
};

