#include "Ant.h"
#include <DxLib.h>


Ant::Ant(const Camera& camera, const Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	SetActor("action/ant.act");
	
	this->pos = pos;
	accel = 3;

	count = 0;
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

	if ((count % 180) == 0)
	{
		AimPlayer();
	}
	pos.x += accel;
	
	++count;
}

void Ant::Draw()
{
	Actor::Draw();
}

void Ant::OnDead()
{
	angle = 180.0f;
}
