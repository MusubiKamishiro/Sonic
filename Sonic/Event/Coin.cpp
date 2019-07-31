#include "Coin.h"
#include "../Camera.h"


Coin::Coin(const Camera& camera, const Vector2f& pos) : Event(camera, pos)
{
	SetActor("action/acorn.act");
	this->pos = pos;
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

void Coin::OnCollision(Actor & actor, const Rect & col)
{
}

void Coin::OnDead()
{
}
