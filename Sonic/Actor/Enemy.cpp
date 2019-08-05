#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"


void Enemy::AimPlayer()
{
	if (pos.x < player.GetPos().x)
	{
		turnFlag = true;
		if (accel < 0)
		{
			accel *= -1;
		}
	}
	else
	{
		turnFlag = false;
		if (accel > 0)
		{
			accel *= -1;
		}
	}
}

Enemy::Enemy(const Camera& camera, const Player& player, const Vector2f& pos) : Actor(camera), player(player)
{
	deadSE = DxLib::LoadSoundMem("se/poko.wav");
}


Enemy::~Enemy()
{
}

void Enemy::OnCollision(Actor & actor)
{
	if (pos.y > actor.GetPos().y)
	{
		//auto v = actor.GetVelocity();
		DxLib::PlaySoundMem(deadSE, DX_PLAYTYPE_BACK);
		//actor.SetVelocity(Vector2f(v.x, -15.0f));
		this->OnDead();
	}
	else
	{
		actor.OnDead();
	}
}

bool Enemy::GetIsAvailable()
{
	return isAvailable;
}
