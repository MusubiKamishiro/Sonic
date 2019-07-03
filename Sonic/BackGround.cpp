#include "BackGround.h"
#include <DxLib.h>
#include "Camera.h"

#include "Game.h"



BackGround::BackGround(const Camera& camera) : camera(camera)
{
	img = DxLib::LoadGraph("img/bg.jpg");
	ssize = Game::Instance().GetScreenSize();

	bgParts.resize(0);
}


BackGround::~BackGround()
{
}

void BackGround::AddParts(const char * filepath, const Vector2 & pos, float rate, bool fromBottom, LayoutType type, Size size, int repeatX)
{
	int handle = DxLib::LoadGraph(filepath);
	// ‰æ‘œ‚ÌƒTƒCƒYŽæ“¾
	int width, height;
	DxLib::GetGraphSize(handle, &width, &height);

	float scale = 1.0f;
	if (size.width > 0)
	{
		scale = size.width / width;
		width = size.width;
	}
	if (size.height > 0)
	{
		height = size.height;
	}
	else
	{
		height *= scale;
	}

	if (repeatX == -1)
	{
		repeatX = width;
	}

	auto p = pos;
	if (fromBottom)
	{
		p.y = ssize.y - pos.y - height;
	}
	bgParts.emplace_back(handle, pos, rate, type, repeatX, Size(width, height));
}

void BackGround::Draw()
{
	auto range = camera.GetViewRange();
	for (auto& bg : bgParts)
	{
		//auto poffset = range.size.height * bg.rate;
		auto pos = bg.pos - Vector2((int)(range.Left() * bg.rate) % bg.repeatX, range.Top());

		DxLib::DrawExtendGraph(pos.x, pos.y, pos.x + bg.size.width, pos.y + bg.size.height, bg.handle, true);
		DxLib::DrawExtendGraph(pos.x + bg.repeatX, pos.y, pos.x + bg.size.width + bg.repeatX, pos.y + bg.size.height, bg.handle, true);
	}

}
