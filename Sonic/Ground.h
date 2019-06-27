#pragma once
#include "Geometry.h"

class Player;

class Ground
{
private:
	Player& player;
	Segment segment;


public:
	Ground(Player& player);
	~Ground();

	// 現在のプレイヤー位置での「あるべき地面」の高さを返す。
	int GetCurrentGroundY(const Vector2f& ppos)const;

	void Draw(const Rect& offset);
};

