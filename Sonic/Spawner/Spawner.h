#pragma once
#include <memory>
#include <vector>
#include "../Geometry.h"

class Actor;
class Enemy;

///�G�H����N���X
class Spawner
{
protected:
	std::shared_ptr<Enemy> original;	//�v���g�^�C�v
	bool isSpawned;		// �����t���O
	Vector2f pos;		// ���W

	///�ŏ��ɗ^����ꂽ�v���g�^�C�v�Ɋ�Â��N���[����������
	///�h���N���X��Spawn��Update����Ăяo���B
	std::shared_ptr<Enemy> CreateClone();

public:
	Spawner(std::shared_ptr<Enemy> org);
	virtual ~Spawner();
	virtual std::shared_ptr<Enemy> Spawn() = 0;
	virtual void Update(std::vector<std::shared_ptr<Enemy>>& enemies) = 0;

	Vector2f GetPos()const;
};

