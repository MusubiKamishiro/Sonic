#include "Ant.h"
#include <DxLib.h>
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"


Ant::Ant(Camera& camera, Player& player, Vector2f pos) : Enemy(camera, player, pos)
{
	ImageData data;
	ReadActionFile("action/ant.act");
	Game::Instance().GetFileSystem()->Load(actData.imgFilePath.c_str(), data);
	img = data.GetHandle();

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
