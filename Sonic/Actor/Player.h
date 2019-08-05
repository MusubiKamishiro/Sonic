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
	void JumpCheck(const Peripheral& p);// �W�����v�`�F�b�N
	void Ground(const Peripheral& p);	// ���n
	void Dead(const Peripheral& p);	// ���S

	int jumpButtonPressing;	// �W�����v�{�^����������Ă鎞��

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

	// �u���b�N�̏�ɂ��邩�ǂ����̔���
	// @param true��������Ă�
	bool onflag;

	void AdjustPos(const Vector2f& offset);

	void SetJumpPower();

	bool deadflag = false;
};

