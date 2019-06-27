#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;


class Player : public Actor
{
private:
	// 状態遷移のためのﾒﾝﾊﾞ関数ﾎﾟｲﾝﾀ
	void (Player::*updater)(const Peripheral& p);

	bool Move(const Peripheral&p);

	void Idle(const Peripheral& p);
	void Run(const Peripheral& p);
	void Jump(const Peripheral& p);
	void Ground(const Peripheral& p);

	Vector2f vel;	// 移動量(ジャンプなどの際に使う)

public:
	Player(Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw();

	void AdjustY(float adjustY);
	void OnGround(const int groundY);

	// 空中フラグ
	// @param true時が空中
	bool isAerial;
};

