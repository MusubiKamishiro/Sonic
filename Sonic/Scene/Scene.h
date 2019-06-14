#pragma once

class Peripheral;

// (�������z�׽)
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// ��݂̍X�V���s��
	virtual void Update(const Peripheral& p) = 0;
	
	virtual void FadeinUpdate(const Peripheral& p) = 0;
	virtual void FadeoutUpdate(const Peripheral& p) = 0;

	int pal;
};

