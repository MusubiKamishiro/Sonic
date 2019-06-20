#pragma once
#include <memory>

class Peripheral;

// (�������z�׽)
class Scene
{
protected:
	// �`��u�����h���[�h�̃p�����[�^(0~255)
	int pal;

public:
	Scene();
	virtual ~Scene();

	// �V�[���̍X�V���s��
	virtual void Update(const Peripheral& p) = 0;
	// �V�[���̕`��
	virtual void Draw() = 0;
	
	// �t�F�[�h�C���̏���������
	virtual void FadeinUpdate(const Peripheral& p) = 0;
	// �t�F�[�h�A�E�g�̏���������
	virtual void FadeoutUpdate(const Peripheral& p) = 0;
	// �ҋ@���̏���������
	virtual void WaitUpdate(const Peripheral& p) = 0;
};

