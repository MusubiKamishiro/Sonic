#pragma once
#include <vector>
#include "Geometry.h"

class Player;

class Ground
{
private:
	Player& player;
	Segment segment;
	std::vector<Segment> segments;

	int img;
	Vector2 ssize;

	// 遊び
	int tileNum;
	std::vector<int> tiles;
	std::vector<int> rand;
	std::vector<Vector2> tileSize;


public:
	Ground(Player& player);
	~Ground();

	// 現在のプレイヤー位置での「あるべき地面」の高さを返す。
	int GetCurrentGroundY(const Vector2f& ppos, float& grad)const;

	void Updade(const int& time);
	void Draw(const Rect& offset);
};

