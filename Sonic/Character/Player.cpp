#include "Player.h"
#include <DxLib.h>
#include "../Peripheral.h"


void Player::Move(const Peripheral & p)
{
	for (int i = 0; i < p.GetPlayerCount(); ++i)
	{
		if (p.IsPressing(i, "right"))
		{
			pos.x += 5;
			turnFlag = false;
		}
		if (p.IsPressing(i, "left"))
		{
			pos.x -= 5;
			turnFlag = true;
		}
		if (p.IsPressing(i, "up"))
		{
			pos.y -= 5;
		}
		if (p.IsPressing(i, "down"))
		{
			pos.y += 5;
		}
	}
}

Player::Player(Camera& camera) : Actor(camera)
{
	pos = Vector2f(500, 200);
	img = DxLib::LoadGraph("img/player.jpg");
}


Player::~Player()
{
}

void Player::Update(const Peripheral & p)
{
	Move(p);
}

void Player::Draw()
{
	DxLib::DrawRectRotaGraph(pos.x, pos.y, 0, 0, 200, 200, 0.5f, 0, img, false, turnFlag);
}
