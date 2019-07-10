#pragma once
#include <vector>
#include "Geometry.h"

class Player;

//�[�^�C�v
enum class EdgeType
{
	none,	// �[����Ȃ�
	left,	// ���[
	right,	// �E�[
	both,	// ����
};

//�n�`
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

	// ���݂̃v���C���[�ʒu�ł́u����ׂ��n�ʁv�̍�����Ԃ��B
	int GetCurrentGroundY(float& grad)const;

	int GetCurrentDeadLine()const;

	Segment GetCurrentSegment()const;

	void Updade(const int& time);
	void Draw(const Rect& offset);
};

