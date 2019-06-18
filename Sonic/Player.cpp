#include "Player.h"
#include "Peripheral.h"
#include <DxLib.h>


Player::Player()
{
	pos[2] = (Vector2(0, 0), Vector2(0, 0));

	bg1 = DxLib::LoadGraph("img/bg1.png");
	bg2 = DxLib::LoadGraph("img/bg2.png");

	count = 0;
}


Player::~Player()
{
}

void Player::Update(const Peripheral & p)
{
	count += 3;

	for (int i = 0; i < p.GetPlayerCount(); ++i)
	{
		if (p.IsPressing(i, "right"))
		{
			pos[i].x += 5;
		}
		if (p.IsPressing(i, "left"))
		{
			pos[i].x -= 5;
		}
		if (p.IsPressing(i, "up"))
		{
			pos[i].y -= 5;
		}
		if (p.IsPressing(i, "down"))
		{
			pos[i].y += 5;
		}
	}
}

void Player::Draw()
{
	//DxLib::DrawRectExtendGraph(pos[0].x, pos[0].y, 200 + pos[0].x, 200 + pos[0].y, pos[0].x, pos[0].y, 200, 200, bg2, true);
	//DxLib::DrawRectExtendGraph(pos[1].x, pos[1].y, 100 + pos[1].x, 100 + pos[1].y, pos[1].x, pos[1].y, 100, 100, bg1, true);

	DxLib::DrawRectExtendGraph(pos[0].x, pos[0].y, 200 + pos[0].x, 200 + pos[0].y, pos[0].x, pos[0].y, 200, 200, bg1, true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs((count % 512) - 255));
	DxLib::DrawRectExtendGraph(pos[0].x, pos[0].y, 200 + pos[0].x, 200 + pos[0].y, pos[0].x, pos[0].y, 200, 200, bg2, true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
