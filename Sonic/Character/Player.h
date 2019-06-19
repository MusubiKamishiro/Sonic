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

	// 遊びのテスト
	// 必ず消すこと
	int count;

public:
	Player();
	~Player();

	void Update(const Peripheral& p)override final;

	void Draw()override final;
};

