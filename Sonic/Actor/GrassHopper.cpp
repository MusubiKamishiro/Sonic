#include "GrassHopper.h"
#include <DxLib.h>



GrassHopper::GrassHopper(Camera& camera, Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	SetActor("action/mantis.act");
	this->pos = pos;
}


GrassHopper::~GrassHopper()
{
}

void GrassHopper::Update(const Peripheral & p)
{
	ProceedAnimationFile();
}

void GrassHopper::Draw()
{
	Actor::Draw();
}

void GrassHopper::OnDead()
{
}
