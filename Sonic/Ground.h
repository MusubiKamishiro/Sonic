#pragma once
#include <vector>
#include "Geometry.h"

class Player;

//端タイプ
enum class EdgeType
{
	none,	// 端じゃない
	left,	// 左端
	right,	// 右端
	both,	// 両方
};

//地形
struct Terrain
{
	Segment s;
	EdgeType type;
	Terrain() {};
	Terrain(const Vector2f& posA, const Vector2f& posB, EdgeType t) : type(t), s(posA, posB) {}
	Terrain(const Segment& seg, EdgeType t) : type(t), s(seg) {}
};

class Ground
{
private:
	Player& player;
	std::vector<Terrain> segments;

	int img;
	Vector2 ssize;

public:
	Ground(Player& player);
	~Ground();

	void AddSegment(const Segment& s, const EdgeType& type);
	void AddSegment(const Vector2f& lpos, const Vector2f& rpos, const EdgeType& type);

	// 現在のプレイヤー位置での「あるべき地面」の高さを返す。
	int GetCurrentGroundY(float& grad)const;

	int GetCurrentDeadLine()const;

	Segment GetCurrentSegment()const;

	void Updade(const int& time);
	void Draw(const Rect& offset);
};

