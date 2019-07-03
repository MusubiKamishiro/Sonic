#pragma once
#include <vector>
#include "Geometry.h"

class Player;

class Ground
{
private:
	Player& player;
	std::vector<Segment> segments;

	int img;
	Vector2 ssize;

public:
	Ground(Player& player);
	~Ground();

	void AddSegment(const Segment& s);
	void AddSegment(const Vector2f& lpos, const Vector2f& rpos);

	// 現在のプレイヤー位置での「あるべき地面」の高さを返す。
	int GetCurrentGroundY(float& grad)const;

	int GetCurrentDeadLine()const;

	void Updade(const int& time);
	void Draw(const Rect& offset);
};

