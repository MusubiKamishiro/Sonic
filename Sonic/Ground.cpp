#include "Ground.h"
#include <DxLib.h>
#include <algorithm>
#include <random>
#include "Character/Player.h"
#include "Game.h"


Ground::Ground(Player& player) : player(player)
{
	segments.emplace_back(0, 500, 400, 300);

	// サインカーブを作るよ
	for (int i = 0; i < 765; ++i)
	{
		auto ax = i * 100;
		auto bx = (i + 1) * 100;
		auto ay = 300 - 200 * sin(DX_PI * (float)i / 8.0f);
		auto by = 300 - 200 * sin(DX_PI * (float)(i + 1) / 8.0f);
		segments.emplace_back(ax + 400, ay, bx + 400, by);
	}

	segment = Segment(Vector2f(0, 900), Vector2f(1000, 0));

	img = DxLib::LoadGraph("img/atlas0.png");
	ssize = Game::Instance().GetScreenSize();

	
	tileNum = 12;
	tileSize.resize(tileNum);
	rand.resize(tileNum * 5);
	for (int i = 0; i < tileNum; ++i)
	{
		std::string s = ("img/tile" + std::to_string((i + 1)) + ".jpg");
		tiles.emplace_back(DxLib::LoadGraph(s.c_str()));
		DxLib::GetGraphSize(tiles[i], &tileSize[i].x, &tileSize[i].y);
	}
}


Ground::~Ground()
{
}

int Ground::GetCurrentGroundY(const Vector2f& ppos, float& grad) const
{
	// 自分のいる座標の地面を見つける
	auto it = std::find_if(segments.begin(), segments.end(), [ppos](Segment s) { return (s.posA.x <= ppos.x) && (ppos.x <= s.posB.x); });

	// 見つからなかったら落下させる命令をしてもらうために
	// あり得ない数値を返す
	if (it == segments.end())
	{
		return INT_MIN;
	}

	grad = (it->posB.y - it->posA.y) / (it->posB.x - it->posA.x);
	int MY = it->posA.y + grad * (ppos.x - it->posA.x);

	// 線分の端だったら平均を求める
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

void Ground::Updade(const int & time)
{
	if ((time % 150) == 0)
	{
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());

		for (auto& r : rand)
		{
			r = engine() % tileNum;
		}
	}
}

void Ground::Draw(const Rect& offset)
{
	int cnt = 0;

	auto left = offset.Left();
	int height = 64;
	int width = 64;
	for (auto& s : segments)
	{
		float l = s.posB.x - s.posA.x;
		float h = s.posB.y - s.posA.y;
		Vector2f count = Vector2f(l / width, h / height);
		Vector2f pos = Vector2f(0.0f, 0.0f);
		for (int i = 0; i < (int)count.x; ++i)
		{
			pos.x = s.posA.x - left + width * i;
			pos.y = s.posA.y + (h / count.x * i);
			float posYB = s.posA.y + (h / count.x * (i + 1));
			// 一番上(斜めもありえる)
			DxLib::DrawRectModiGraphF(pos.x, pos.y, pos.x + width, posYB,
				pos.x + width, posYB + height, pos.x, pos.y + height, 64, 32, 32, 32, img, true);

			auto maxY = max(pos.y + height, posYB + height);

			// 次層(台形底辺は横軸に平行)
			DxLib::DrawRectModiGraphF(pos.x, pos.y + height, pos.x + width, posYB + height,
				pos.x + width, maxY + height, pos.x, maxY + height, 64, 64, 32, 32, img, true);

			// それよりも下(普通の長方形)
			for (int y = (maxY + height); y < ssize.y; y += height)
			{
				cnt %= rand.size();
				int num = rand.at(cnt);
				DxLib::DrawRectExtendGraph(pos.x, y, pos.x + width, y + height, 0, 0, tileSize[num].x, tileSize[num].y, tiles[num], true);
				++cnt;

				//DxLib::DrawRectExtendGraphF(pos.x, y, pos.x + width, y + height, 64, 64, 32, 32, img, true);
			}
		}

		// 残り端
		int last = (int)count.x;
		pos.x = s.posA.x - left + width * last;
		pos.y = s.posA.y + (h / count.x * last);
		// 一番上(斜めもありえる)
		DxLib::DrawRectModiGraphF(pos.x, s.posA.y + (h / count.x * last), s.posB.x - left, s.posB.y,
			s.posB.x - left, s.posB.y + height, pos.x, s.posA.y + (h / count.x * last) + height, 64, 32, 32, 32, img, true);

		auto maxY = max(pos.y + height, s.posB.y + height);

		// 次層(台形底辺は横軸に平行)
		DxLib::DrawRectModiGraphF(pos.x, pos.y + height, s.posB.x - left, s.posB.y + height,
			s.posB.x - left, maxY + height, pos.x, maxY + height, 64, 64, 32, 32, img, true);

		// それよりも下(普通の長方形)
		for (int y = (maxY + height); y < ssize.y; y += height)
		{
			cnt %= rand.size();
			int num = rand.at(cnt);
			//DxLib::DrawRectExtendGraph(pos.x, y, s.posB.x - left, y + height, 0, 0, tileSize[num].x, tileSize[num].y, tiles[num], true);
			++cnt;

			DxLib::DrawRectExtendGraphF(pos.x, y, s.posB.x - left, y + height, 64, 64, 32, 32, img, true);
		}
				
		DxLib::DrawLine(s.posA.x - left, s.posA.y, s.posB.x - left, s.posB.y, 0xff0000);
	}
}
