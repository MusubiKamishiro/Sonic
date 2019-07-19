#include "Ant.h"
#include <DxLib.h>


Ant::Ant(Camera& camera, Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	ReadActionFile("action/ant.act");
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

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
