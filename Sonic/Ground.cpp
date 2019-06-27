#include "Ground.h"
#include <DxLib.h>
#include "Character/Player.h"


Ground::Ground(Player& player) : player(player)
{
	segment = Segment(Vector2f(0, 900), Vector2f(1000, 0));
}


Ground::~Ground()
{
}

int Ground::GetCurrentGroundY(const Vector2f& ppos) const
{
	float grad = (segment.posB.y - segment.posA.y) / (segment.posB.x - segment.posA.x);
	
	int MY = segment.posA.y + grad * (ppos.x - segment.posA.x);

	return MY;
}

void Ground::Draw(const Rect& offset)
{
	DxLib::DrawLine(segment.posA.x - offset.Left(), segment.posA.y, segment.posB.x - offset.Left(), segment.posB.y, 0x00ff00);
}
