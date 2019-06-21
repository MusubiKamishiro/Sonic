#include "Player.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Camera.h"


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

	pos.x = max(pos.x, 0);
	pos.y = max(pos.y, 0);
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
	auto offset = camera.GetViewRange();
	DxLib::DrawRectRotaGraph(pos.x - offset.Left(), pos.y - offset.Top(), 0, 0, 200, 200, 0.5f, 0, img, false, turnFlag);
}
