#pragma once
#include <memory>
#include "../Geometry.h"

class Player;
class Camera;
class Spawner;


// �X�e�[�W�ɐݒu����u���b�N�̎��
enum SpawnerType
{
	ant,
	grassHopper,
};

class SpawnerFactory
{
private:
	const Player& player;
	const Camera& camera;

public:
	SpawnerFactory(const Camera& camera, const Player& player);
	~SpawnerFactory();

	// �u���b�N�𐶐�����
	// @param type �ǂ̎�ʂ̃u���b�N�𐶐����邩
	// @param pos �ǂ��ɐ������邩
	std::shared_ptr<Spawner> Create(SpawnerType type, const Vector2f& pos);
};

