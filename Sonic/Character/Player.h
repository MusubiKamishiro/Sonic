#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;


class Player : public Actor
{
private:
	// ��ԑJ�ڂ̂��߂����ފ֐��߲��
	void (Player::*updater)(const Peripheral& p);

	bool Move(const Peripheral&p);

	void Idle(const Peripheral& p);
	void Run(const Peripheral& p);
	void Jump(const Peripheral& p);
	void Ground(const Peripheral& p);

	Vector2f vel;	// �ړ���(�W�����v�Ȃǂ̍ۂɎg��)

public:
	Player(Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw();

	void AdjustY(float adjustY);
	void OnGround(const int groundY);

	// �󒆃t���O
	// @param true������
	bool isAerial;
};

