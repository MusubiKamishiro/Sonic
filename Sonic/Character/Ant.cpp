#include "Ant.h"
#include <DxLib.h>


Ant::Ant(Camera& camera, Player& player) : Enemy(camera, player)
{
	ReadActionFile("action/ant.act");
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	pos = Vector2f(100, 210);
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
