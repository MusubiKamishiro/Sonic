#include "OnetimeSpawner.h"
#include "../Camera.h"


OnetimeSpawner::OnetimeSpawner(const Camera & camera, const Vector2f & pos, std::shared_ptr<Enemy> org) : Spawner(org), camera(camera)
{
	original = org;
	this->pos = pos;
}

OnetimeSpawner::~OnetimeSpawner()
{
}

std::shared_ptr<Enemy> OnetimeSpawner::Spawn()
{
	return CreateClone();
}

void OnetimeSpawner::Update(std::vector<std::shared_ptr<Enemy>>& enemies)
{
	// ��x�Y�񂾂�������܂Ȃ���
	if (isSpawned)
	{
		return;
	}

	// �J�����͈͓̔��ł���ΐ��ނ�
	auto& range = camera.GetViewRange();
	if ((pos.x > range.Left()) && (pos.x < range.Right()))
	{
		enemies.push_back(Spawn());
		isSpawned = true;
	}
}
