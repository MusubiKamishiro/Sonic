#pragma once
#include "Actor.h"
#include "../Geometry.h"

class Peripheral;

class Player : public Actor
{
private:
	Vector2 pos[2];

	int bg1;
	int bg2;

	// �V�т̃e�X�g
	// �K����������
	int count;

public:
	Player();
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw()override final;
};

