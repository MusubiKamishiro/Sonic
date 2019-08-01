#include "Coin.h"
#include <DxLib.h>
#include "../Camera.h"


Coin::Coin(const Camera& camera, const Vector2f& pos) : Event(camera, pos)
{
	SetActor("action/acorn.act");
	this->pos = pos;

	coinSound = DxLib::LoadSoundMem("se/coin.wav");
}


Coin::~Coin()
{
}

void Coin::Update(const Peripheral& p)
{
	ProceedAnimationFile();
}

void Coin::Draw()
{
	Actor::Draw();
}

void Coin::OnDead()
{
	isAvailable = false;
	DxLib::PlaySoundMem(coinSound, DX_PLAYTYPE_BACK);
}
