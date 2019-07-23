#include "Ant.h"
#include <DxLib.h>


Ant::Ant(Camera& camera, Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	SetActor("action/ant.act");
	
	this->pos = pos;
}


Ant::~Ant()
{
}

void Ant::Update(const Peripheral & p)
{
	ProceedAnimationFile();
}

void Ant::Draw()
{
	Actor::Draw();
}
