#include "Ground.h"
#include <DxLib.h>
#include <algorithm>
#include "Character/Player.h"
#include "Game.h"


Ground::Ground(Player& player) : player(player)
{
	//segments.emplace_back(0, 500, 400, 300);

	//// �T�C���J�[�u������
	//for (int i = 0; i < 765; ++i)
	//{
	//	auto ax = i * 100;
	//	auto bx = (i + 1) * 100;
	//	auto ay = 300 - 200 * sin(DX_PI * (float)i / 8.0f);
	//	auto by = 300 - 200 * sin(DX_PI * (float)(i + 1) / 8.0f);
	//	segments.emplace_back(ax + 400, ay, bx + 400, by);
	//}

	img = DxLib::LoadGraph("img/atlas0.png");
	ssize = Game::Instance().GetScreenSize();
}


Ground::~Ground()
{
}

void Ground::AddSegment(const Segment & s)
{
	segments.emplace_back(s.posA, s.posB);
}

void Ground::AddSegment(const Vector2f & lpos, const Vector2f & rpos)
{
	segments.emplace_back(lpos, rpos);
}

int Ground::GetCurrentGroundY(float& grad) const
{
	auto ppos = player.GetPos();
	// �����̂�����W�̒n�ʂ�������
	auto it = std::find_if(segments.begin(), segments.end(), [ppos](Segment s) { return (s.posA.x <= ppos.x) && (ppos.x <= s.posB.x); });

	// ������Ȃ������痎�������閽�߂����Ă��炤���߂�
	// ���蓾�Ȃ����l��Ԃ�
	if (it == segments.end())
	{
		return INT_MIN;
	}

	grad = (it->posB.y - it->posA.y) / (it->posB.x - it->posA.x);
	int MY = it->posA.y + grad * (ppos.x - it->posA.x);

	// �����̒[�������畽�ς����߂�
	if (std::fabsf(ppos.x - it->posA.x) < 4.0f)
	{
		if (it == segments.begin())
		{
			return MY;
		}

		auto gradb = ((it-1)->posB.y - (it-1)->posA.y) / ((it-1)->posB.x - (it-1)->posA.x);
		grad = (grad + gradb) / 2;
	}
	else if (std::fabsf(ppos.x - it->posB.x) < 4.0f)
	{
		if (it == (segments.end() - 1))
		{
			return MY;
		}

		auto gradb = ((it+1)->posB.y - (it+1)->posA.y) / ((it+1)->posB.x - (it+1)->posA.x);
		grad = (grad + gradb) / 2;
	}
	
	return MY;
}

int Ground::GetCurrentDeadLine() const
{
	return 1000;
}

void Ground::Updade(const int & time)
{
	
}

void Ground::Draw(const Rect& offset)
{
	int cnt = 0;

	auto left = offset.Left();
	auto top = offset.Top();
	Vector2 imgSize = Vector2(64, 64);
	for (auto& s : segments)
	{
		// ��ʊO�ł���Ε`�悵�Ȃ�
		if (((s.posB.x - left) < 0) || ((s.posA.x - left) > ssize.x))
		{
			continue;
		}

		float l = s.posB.x - s.posA.x;
		float h = s.posB.y - s.posA.y;
		Vector2f count = Vector2f(l / imgSize.x, h / imgSize.y);
		Vector2f pos = Vector2f(0.0f, 0.0f);
		for (int i = 0; i < (int)count.x; ++i)
		{
			pos.x = s.posA.x - left + imgSize.x * i;
			pos.y = s.posA.y - top + (h / count.x * i);
			float posYB = s.posA.y - top + (h / count.x * (i + 1));
			// ��ԏ�(�΂߂����肦��)
			DxLib::DrawRectModiGraphF(pos.x, pos.y, pos.x + imgSize.x, posYB,
				pos.x + imgSize.x, posYB + imgSize.y, pos.x, pos.y + imgSize.y, 64, 32, 32, 32, img, true);

			auto maxY = max(pos.y + imgSize.y, posYB + imgSize.y);

			// ���w(��`��ӂ͉����ɕ��s)
			DxLib::DrawRectModiGraphF(pos.x, pos.y + imgSize.y, pos.x + imgSize.x, posYB + imgSize.y,
				pos.x + imgSize.x, maxY + imgSize.y, pos.x, maxY + imgSize.y, 64, 64, 32, 32, img, true);

			// ���������(���ʂ̒����`)
			for (int y = (maxY + imgSize.y); y < ssize.y; y += imgSize.y)
			{
				DxLib::DrawRectExtendGraphF(pos.x, y, pos.x + imgSize.x, y + imgSize.y, 64, 64, 32, 32, img, true);
			}
		}

		// �c��[
		int last = (int)count.x;
		pos.x = s.posA.x - left + imgSize.x * last;
		pos.y = s.posA.y - top + (h / count.x * last);
		// ��ԏ�(�΂߂����肦��)
		DxLib::DrawRectModiGraphF(pos.x, pos.y, s.posB.x - left, s.posB.y - top,
			s.posB.x - left, s.posB.y - top + imgSize.y, pos.x, pos.y + imgSize.y, 64, 32, 32, 32, img, true);

		auto maxY = max(pos.y + imgSize.y, s.posB.y - top + imgSize.y);

		// ���w(��`��ӂ͉����ɕ��s)
		DxLib::DrawRectModiGraphF(pos.x, pos.y + imgSize.y, s.posB.x - left, s.posB.y - top + imgSize.y,
			s.posB.x - left, maxY + imgSize.y, pos.x, maxY + imgSize.y, 64, 64, 32, 32, img, true);

		// ���������(���ʂ̒����`)
		for (int y = (maxY + imgSize.y); y < ssize.y; y += imgSize.y)
		{
			DxLib::DrawRectExtendGraphF(pos.x, y, s.posB.x - left, y + imgSize.y, 64, 64, 32, 32, img, true);
		}

#ifdef _DEBUG
		DxLib::DrawLine(s.posA.x - left, s.posA.y - top, s.posB.x - left, s.posB.y - top, 0xff0000);
#endif // _DEBUG
	}
}
