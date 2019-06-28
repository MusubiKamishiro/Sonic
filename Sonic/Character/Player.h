#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;


class Player : public Actor
{
private:
	// ó‘Ô‘JˆÚ‚Ì‚½‚ß‚ÌÒİÊŞŠÖ”Îß²İÀ
	void (Player::*updater)(const Peripheral& p);

	bool Move(const Peripheral&p);

	void Idle(const Peripheral& p);
	void Run(const Peripheral& p);
	void Jump(const Peripheral& p);
	void Ground(const Peripheral& p);

	Vector2f vel;	// ˆÚ“®—Ê

public:
	Player(Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw();

	void AdjustY(float adjustY, float grad);
	void OnGround(const int groundY);

	// ‹ó’†ƒtƒ‰ƒO
	// @param true‚ª‹ó’†
	bool isAerial;
};

