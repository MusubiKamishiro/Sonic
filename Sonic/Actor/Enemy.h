#pragma once
#include <memory>
#include "Actor.h"

class Player;
class Spawner;

///�G���N���X
class Enemy : public Actor
{
	friend Spawner;
private:
	

protected:
	///�����̃N���[����Ԃ�
	virtual std::shared_ptr<Enemy> MakeClone() = 0;

	const Player& player;

	///�v���C���[�̈ʒu��m��
	void AimPlayer();

	bool isAvailable = true;
	int deadSE;

public:
	Enemy(const Camera& camera, const Player& player, const Vector2f& pos);
	~Enemy();

	virtual void Update(const Peripheral& p) = 0;

	virtual void Draw() = 0;

	// �Փ˃C�x���g
	// @param actor ����A�N�^�[�I�u�W�F�N�g
	virtual void OnCollision(Actor& actor);

	bool GetIsAvailable();
};

