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

	// �V��
	int tileNum;
	std::vector<int> tiles;
	std::vector<int> rand;
	std::vector<Vector2> tileSize;


public:
	Ground(Player& player);
	~Ground();

	// ���݂̃v���C���[�ʒu�ł́u����ׂ��n�ʁv�̍�����Ԃ��B
	int GetCurrentGroundY(const Vector2f& ppos, float& grad)const;

	void Updade(const int& time);
	void Draw(const Rect& offset);
};

