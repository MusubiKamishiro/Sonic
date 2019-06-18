#pragma once
#include <memory>

class SceneManager;
class Peripheral;

// (�������z�׽)
class Scene
{
private:
	

public:
	Scene();
	virtual ~Scene();

	// ��݂̍X�V���s��
	virtual void Update(const Peripheral& p) = 0;
	
	// �t�F�[�h�C���̏���������
	virtual void FadeinUpdate(const Peripheral& p) = 0;
	// �t�F�[�h�A�E�g�̏���������
	virtual void FadeoutUpdate(const Peripheral& p) = 0;

	// �`��u�����h���[�h�̃p�����[�^(0~255)
	int pal;
};

