#pragma once
#include "Actor.h"

class Player;

///�G���N���X
class Enemy : public Actor
{
private:
	int deadSE;

protected:
	const Player& player;
public:
	Enemy(Camera& camera, Player& player, Vector2f& pos);
	~Enemy();

	virtual void Update(const Peripheral& p) = 0;

	virtual void Draw() = 0;

	// �Փ˃C�x���g
	// @param actor ����A�N�^�[�I�u�W�F�N�g
	virtual void OnCollision(Actor& actor);
};

