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

	// ���݂̃v���C���[�ʒu�ł́u����ׂ��n�ʁv�̍�����Ԃ��B
	int GetCurrentGroundY(float& grad)const;

	int GetCurrentDeadLine()const;

	void Updade(const int& time);
	void Draw(const Rect& offset);
};

