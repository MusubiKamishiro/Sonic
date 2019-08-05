#pragma once
class HUD
{
private:
	int score;
	int img;

public:
	HUD();
	~HUD();

	void AddScore(int inscore);

	void Update();

	void Draw();
};

