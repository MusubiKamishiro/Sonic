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

	// ���݂̃v���C���[�ʒu�ł́u����ׂ��n�ʁv�̍�����Ԃ��B
	int GetCurrentGroundY(const Vector2f& ppos)const;

	void Draw(const Rect& offset);
};

