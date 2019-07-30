#include "GrassHopper.h"
#include <DxLib.h>



GrassHopper::GrassHopper(const Camera& camera, const Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	SetActor("action/mantis.act");
	this->pos = pos;
}


GrassHopper::~GrassHopper()
{
}

std::shared_ptr<Enemy> GrassHopper::MakeClone()
{
	return std::make_shared<GrassHopper>(*this);
}

void GrassHopper::Update(const Peripheral & p)
{
	ProceedAnimationFile();
	pos.x += 5;
	turnFlag = true;
}

void GrassHopper::Draw()
{
	Actor::Draw();
}

void GrassHopper::OnDead()
{
}
