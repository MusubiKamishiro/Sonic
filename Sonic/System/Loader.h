#pragma once
#include <string>

///�f�[�^���N���X
class Data
{
public:
	virtual ~Data() {};

	///�_�~�[�֐�
	virtual bool IsAvailable() = 0;
};

///���[�h���N���X
class Loader
{
public:
	Loader();
	virtual ~Loader();

	///���[�h
	///@param path �t�@�C���̃p�X
	///@param data �f�[�^�I�u�W�F�N�g�ւ̎Q��
	///@retval true ����
	///@retval false ���s
	virtual bool Load(std::string path, Data& data) = 0;

	///�f�[�^�̃A�����[�h
	///@attention	����Ŏw�肳�ꂽ�p�X�ɑΉ�����f�[�^�̓������ォ�疳���Ȃ�̂�
	///				�������g�p����Ƃ��̓X�g���[�W�A�N�Z�X�����������
	virtual void UnLoad(const char* path) = 0;
};

