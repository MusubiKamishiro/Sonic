#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;
class GamePlayingScene;

class Player : public Actor
{
private:
	// ��ԑJ�ڂ̂��߂����ފ֐��߲��
	void (Player::*updater)(const Peripheral& p);

	bool Move(const Peripheral&p);

	void Idle(const Peripheral& p);		// �ҋ@
	void Run(const Peripheral& p);		// �ړ�
	void Jump(const Peripheral& p);		// �W�����v
	void Ground(const Peripheral& p);	// ���n
	void Damage(const Peripheral& p);	// ���S

	Vector2f vel;	// �ړ���

public:
	Player(Camera& camera);
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw();

	void AdjustY(float adjustY, float grad);
	void OnGround(const int groundY);
	void OnDead();

	// �󒆃t���O
	// @param true������
	bool isAerial;
};

