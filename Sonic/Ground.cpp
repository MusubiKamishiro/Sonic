#include "Ground.h"
#include <DxLib.h>
#include <algorithm>
#include "Character/Player.h"
#include "Game.h"


Ground::Ground(Player& player) : player(player)
{
	//segments.emplace_back(0, 500, 400, 300);

	//// サインカーブを作るよ
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

void Ground::AddSegment(const Segment & s, const EdgeType& type)
{
	segments.emplace_back(s, type);
}

void Ground::AddSegment(const Vector2f & lpos, const Vector2f & rpos, const EdgeType& type)
{
	segments.emplace_back(lpos, rpos, type);
}

int Ground::GetCurrentGroundY(float& grad) const
{
	auto ppos = player.GetPos();
	auto lambda = [ppos](Terrain t) { return (t.s.posA.x <= ppos.x) && (ppos.x <= t.s.posB.x); };

	// 自分のいる座標の地面を見つける
	auto it = std::find_if(segments.begin(), segments.end(), lambda);
	if (it == segments.end())
	{
		return INT_MIN;
	}

	int MY = 0;
	do
	{
		grad = (it->s.posB.y - it->s.posA.y) / (it->s.posB.x - it->s.posA.x);
		MY = it->s.posA.y + grad * (ppos.x - it->s.posA.x);
		if (MY >= (ppos.y - 100))
		{
			break;
		}
		it = std::find_if(it + 1, segments.end(), lambda);
	}
	while (it != segments.end());

	// 見つからなかったら落下させる命令をしてもらうために
	// あり得ない数値を返す
	if (it == segments.end())
	{
		return INT_MIN;
	}

	// 線分の端だったら平均を求める
	if (std::fabsf(ppos.x - it->s.posA.x) < 4.0f)
	{
		if (it == segments.begin())
		{
			return MY;
		}

		auto gradb = ((it-1)->s.posB.y - (it-1)->s.posA.y) / ((it-1)->s.posB.x - (it-1)->s.posA.x);
		grad = (grad + gradb) / 2;
	}
	else if (std::fabsf(ppos.x - it->s.posB.x) < 4.0f)
	{
		if (it == (segments.end() - 1))
		{
			return MY;
		}

		auto gradb = ((it+1)->s.posB.y - (it+1)->s.posA.y) / ((it+1)->s.posB.x - (it+1)->s.posA.x);
		grad = (grad + gradb) / 2;
	}
	
	return MY;
}

int Ground::GetCurrentDeadLine() const
{
	return 1000;
}

Segment Ground::GetCurrentSegment() const
{
	auto ppos = player.GetPos();
	auto lambda = [ppos](Terrain t) { return (t.s.posA.x <= ppos.x) && (ppos.x <= t.s.posB.x); };

	auto it = std::find_if(segments.begin(), segments.end(), lambda);
	if (it == segments.end())
	{
		return Segment((it-1)->s.posA, (it-1)->s.posB);
	}

	int MY = 0;
	auto height = player.GetRect().Height();
	do
	{
		int grad = (it->s.posB.y - it->s.posA.y) / (it->s.posB.x - it->s.posA.x);
		MY = it->s.posA.y + grad * (ppos.x - it->s.posA.x);
		if (MY >= (ppos.y - height / 2))
		{
			break;
		}
		it = std::find_if(it + 1, segments.end(), lambda);
	}
	while (it != segments.end());

	if (it == segments.end())
	{
		return Segment((it-1)->s.posA, (it-1)->s.posB);
	}

	return Segment(it->s.posA, it->s.posB);
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
		// 画面外であれば描画しない
		if (((s.s.posB.x - left) < 0) || ((s.s.posA.x - left) > ssize.x))
		{
			continue;
		}

		float l = s.s.posB.x - s.s.posA.x;
		float h = s.s.posB.y - s.s.posA.y;
		Vector2f count = Vector2f(l / imgSize.x, h / imgSize.y);
		Vector2 mod = Vector2((int)l % imgSize.x, (int)h % imgSize.y);
		Vector2f pos = Vector2f(0.0f, 0.0f);
		Vector2 imgPos = Vector2(0, 0);
		for (int i = 0; i < (int)count.x; ++i)
		{
			// タイプを見てずらす
			auto type = s.type;
			imgPos = Vector2(64, 64);
			if ((i == 0) && (type == EdgeType::left))
			{
				imgPos.x -= 32;
			}
			else if ((i == (count.x - 1)) && (mod.x == 0) && (type == EdgeType::right))
			{
				imgPos.x += 32;
			}
				
			pos.x = s.s.posA.x - left + imgSize.x * i;
			pos.y = s.s.posA.y - top + (h / count.x * i);
			float posYB = s.s.posA.y - top + (h / count.x * (i + 1));
			// 一番上(斜めもありえる)
			DxLib::DrawRectModiGraphF(pos.x, pos.y, pos.x + imgSize.x, posYB,
				pos.x + imgSize.x, posYB + imgSize.y, pos.x, pos.y + imgSize.y, imgPos.x, 32, 32, 32, img, true);

			auto maxY = max(pos.y + imgSize.y, posYB + imgSize.y);
			// 次層(台形底辺は横軸に平行)
			DxLib::DrawRectModiGraphF(pos.x, pos.y + imgSize.y, pos.x + imgSize.x, posYB + imgSize.y,
				pos.x + imgSize.x, maxY + imgSize.y, pos.x, maxY + imgSize.y, imgPos.x, 64, 32, 32, img, true);

			// それよりも下(普通の長方形)
			for (int y = (maxY + imgSize.y); y < ssize.y; y += imgSize.y)
			{
				DxLib::DrawRectExtendGraphF(pos.x, y, pos.x + imgSize.x, y + imgSize.y, imgPos.x, 64, 32, 32, img, true);
			}
		}

		imgPos = Vector2(64, 64);
		if ((s.type == EdgeType::right))
		{
			imgPos.x += 32;
		}

		// 残り端
		int last = (int)count.x;
		pos.x = s.s.posA.x - left + imgSize.x * last;
		pos.y = s.s.posA.y - top + (h / count.x * last);
		// 一番上(斜めもありえる)
		DxLib::DrawRectModiGraphF(pos.x, pos.y, s.s.posB.x - left, s.s.posB.y - top,
			s.s.posB.x - left, s.s.posB.y - top + imgSize.y, pos.x, pos.y + imgSize.y, imgPos.x, 32, 32, 32, img, true);

		auto maxY = max(pos.y + imgSize.y, s.s.posB.y - top + imgSize.y);
		// 次層(台形底辺は横軸に平行)
		DxLib::DrawRectModiGraphF(pos.x, pos.y + imgSize.y, s.s.posB.x - left, s.s.posB.y - top + imgSize.y,
			s.s.posB.x - left, maxY + imgSize.y, pos.x, maxY + imgSize.y, imgPos.x, 64, 32, 32, img, true);

		// それよりも下(普通の長方形)
		for (int y = (maxY + imgSize.y); y < ssize.y; y += imgSize.y)
		{
			DxLib::DrawRectExtendGraphF(pos.x, y, s.s.posB.x - left, y + imgSize.y, imgPos.x, 64, 32, 32, img, true);
		}

#ifdef _DEBUG
		DxLib::DrawLine(s.s.posA.x - left, s.s.posA.y - top, s.s.posB.x - left, s.s.posB.y - top, 0xff0000);
#endif // _DEBUG
	}
}
