#pragma once
#include "Geometry.h"

class Peripheral;

class Player
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

	void Update(const Peripheral& p);

	void Draw();
};

