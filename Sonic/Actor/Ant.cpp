#include "Ant.h"
#include <DxLib.h>


Ant::Ant(const Camera& camera, const Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	SetActor("action/ant.act");
	
	this->pos = pos;
}


Ant::~Ant()
{
}

std::shared_ptr<Enemy> Ant::MakeClone()
{
	return std::make_shared<Ant>(*this);
}

void Ant::Update(const Peripheral & p)
{
	ProceedAnimationFile();

	pos.x += 5;
}

void Ant::Draw()
{
	Actor::Draw();
}

void Ant::OnDead()
{
}
