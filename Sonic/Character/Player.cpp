#include "Player.h"
#include <DxLib.h>
#include <cmath>
#include "../Peripheral.h"

constexpr int jumpPower = -15;

bool Player::Move(const Peripheral & p)
{
	vel.x *= 0.95;

	if (p.IsPressing(0, "right"))
	{
		accel += 0.1f;
		//vel.x = 5 + accel;
		turnFlag = false;
	}
	else if (p.IsPressing(0, "left"))
	{
		accel -= 0.1f;
		//vel.x = -(5 + accel);
		turnFlag = true;
	}
	else
	{
		accel = 0.0f;
		return false;
	}

	vel.x = 2 * accel;
	return true;
}

void Player::Idle(const Peripheral & p)
{
	vel.x *= 0.95;

	if (p.IsPressing(0, "right") || p.IsPressing(0, "left"))
	{
		ChangeAction("run");
		updater = &Player::Run;
	}

	if (p.IsTrigger(0, "jump"))
	{
		vel.y += jumpPower;
		ChangeAction("jump");
		updater = &Player::Jump;
	}
}

void Player::Run(const Peripheral & p)
{
	for (int i = 0; i < p.GetPlayerCount(); ++i)
	{
		if (!Move(p))
		{
			ChangeAction("idle");
			updater = &Player::Idle;
		}

		if (p.IsTrigger(i, "jump"))
		{
			vel.y += jumpPower;
			ChangeAction("jump");
			updater = &Player::Jump;
		}
	}
}

void Player::Jump(const Peripheral & p)
{
	isAerial = true;

	if (turnFlag)
	{
		angle -= 1.0f;
	}
	else
	{
		angle += 1.0f;
	}
	
	//Move(p);
}

void Player::Ground(const Peripheral & p)
{
	ChangeAction("idle");
	updater = &Player::Idle;
}

void Player::Damage(const Peripheral & p)
{
}

Player::Player(Camera& camera) : Actor(camera)
{
	pos = Vector2f(500, 200);
	isAerial = true;

	ReadActionFile();
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &Player::Idle;
}


Player::~Player()
{
}

void Player::Update(const Peripheral & p)
{
	ProceedAnimationFile();
	(this->*updater)(p);

	vel.x = min(vel.x, 50);
	pos += vel;

	// ‹ó’†‚É‚¢‚é‚Æd—Í”­“®
	if (isAerial)
	{
		vel.y += 0.5f;
	}
	

	// •‰‚Ì¢ŠE‚É‚Í‚¢‚©‚¹‚È‚¢‚æ‚¤‚É
	pos.x = max(pos.x, 0);
	pos.y = max(pos.y, 0);
}

void Player::Draw()
{
	Actor::Draw();
}

void Player::AdjustY(float adjustY, float grad)
{
	angle = atanf(grad);

	vel.x += grad / std::hypot(1, grad);

	if (adjustY > 0.0f)
	{
		pos.y = adjustY;
	}
}

void Player::OnGround(const int groundY)
{
	isAerial = false;
	pos.y = groundY;
	vel.y = 0.0f;
	angle = 0.0f;

	ChangeAction("idle");
	updater = &Player::Idle;
}

void Player::OnDead()
{
	ChangeAction("damage");
	updater = &Player::Damage;
}

