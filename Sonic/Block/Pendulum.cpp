#include "Pendulum.h"
#include <DxLib.h>
#include "../Camera.h"


Pendulum::Pendulum(const Vector2& pos, const Camera& camera, unsigned int runLength) : Block(pos, camera, runLength), camera(camera)
{
	this->pos.x = (float)rect.center.x;
	this->pos.y = (float)rect.center.y;

	pivot.x = (float)pos.x - runLength*blockSize;
	pivot.y = (float)pos.y;

	v = 0;
}


Pendulum::~Pendulum()
{
}

void Pendulum::Update()
{
	auto tensionVec = rect.center - pivot;				// 支点→ブロックベクトル
	float theta = atan2f(tensionVec.y, tensionVec.x);	// 角度を計算
	float a = 0.5f * 0.5 * cos(theta);					// 推進力(推進加速度)別にベクトルで計算しても可
	v += a;		// 加速

	vel.x = -v * std::sin(theta);
	vel.y = v * std::cos(theta);

	rect.center.x += (int)vel.x;
	rect.center.y += (int)vel.y;


	speed = vel;
}

void Pendulum::Draw()
{
	auto& offset = camera.GetViewRange();

	auto right = rect.Right();
	for (int left = rect.Left(); left < right; left += blockSize)
	{
		DxLib::DrawRectExtendGraph(left - offset.Left(), rect.Top() - offset.Top(),
			left + blockSize - offset.Left(), rect.Bottom() - offset.Top(), 48, 96, 16, 16, img, true);
	}

	DxLib::DrawLine(pivot.x - offset.Left(), pivot.y - offset.Top(), rect.center.x - offset.Left(), rect.center.y - offset.Top(), 0xff0000);
}
