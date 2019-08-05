#include "Player.h"
#include <DxLib.h>
#include <cmath>
#include "../Peripheral.h"


constexpr float jumpPower = -15.0f;

bool Player::Move(const Peripheral & p)
{
	vel.x *= 0.95;

	if (p.IsPressing(0, "right"))
	{
		accel += 0.1f;
		turnFlag = false;
	}
	else if (p.IsPressing(0, "left"))
	{
		accel -= 0.1f;
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

	JumpCheck(p);
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

		JumpCheck(p);
	}
}

void Player::Jump(const Peripheral & p)
{
	isAerial = true;
}

void Player::JumpCheck(const Peripheral & p)
{
	if (jumpButtonPressing > 0)
	{
		++jumpButtonPressing;
	}
	if (p.IsTrigger(0, "jump"))
	{
		jumpButtonPressing = 1;
	}
	if (p.IsReleased(0, "jump") || (jumpButtonPressing >= 1))
	{
		ChangeAction("jump");
		onflag = false;
		DxLib::PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK, true);
		updater = &Player::Jump;
		vel.y = jumpPower * (float)(jumpButtonPressing);
		isAerial = true;
		nowActionName = "jump";
		jumpButtonPressing = 0;
	}
}

void Player::Ground(const Peripheral & p)
{
	ChangeAction("idle");
	updater = &Player::Idle;
}

void Player::Dead(const Peripheral & p)
{
	deadflag = true;
	--respawnTime;
	if (respawnTime < 0)
	{
		respawnTime = 120;
		pos = Vector2f(500, 200);
		ChangeAction("idle");
		updater = &Player::Idle;
		deadflag = false;
	}
}

Player::Player(const Camera& camera) : Actor(camera)
{
	pos = Vector2f(500, 200);

	SetActor("action/player.act");

	jumpButtonPressing = 0;

	updater = &Player::Idle;

	jumpSound = DxLib::LoadSoundMem("se/jump.wav");
	deadSound = DxLib::LoadSoundMem("se/down.wav");

	onflag = false;

	respawnTime = 120;
}


Player::~Player()
{
}

void Player::Update(const Peripheral & p)
{
	ProceedAnimationFile();
	(this->*updater)(p);

	if (onflag)
	{
		vel.y = 0;
	}

	vel.x = min(vel.x, 50);
	pos += vel;

	// ãÛíÜÇ…Ç¢ÇÈÇ∆èdóÕî≠ìÆ
	if (isAerial)
	{
		vel.y += 0.5f;
	}
	
	// ïâÇÃê¢äEÇ…ÇÕÇ¢Ç©ÇπÇ»Ç¢ÇÊÇ§Ç…
	pos.x = max(pos.x, 0);
	pos.y = max(pos.y, 0);
}

void Player::Draw()
{
	Actor::Draw();
}


void Player::OnGround(const int groundY)
{
	if (updater != &Player::Dead)
	{
		isAerial = false;
		pos.y = groundY;
		vel.y = 0.0f;
		angle = 0.0f;

		ChangeAction("idle");
		updater = &Player::Idle;
	}
}

void Player::OnDead()
{
	if (updater != &Player::Dead)
	{
		vel = Vector2f(0, jumpPower / 2);
		ChangeAction("damage");
		DxLib::PlaySoundMem(deadSound, DX_PLAYTYPE_BACK, true);
		updater = &Player::Dead;
	}
}

Vector2f Player::GetVel() const
{
	return vel;
}

void Player::AdjustMove(Vector2f speed)
{
	pos += speed;
}

void Player::AdjustPos(const Vector2f & offset)
{
	pos.x = pos.x + offset.x;
	pos.y = pos.y + offset.y;
}

void Player::SetJumpPower()
{
	vel.y = jumpPower / 2;
}

