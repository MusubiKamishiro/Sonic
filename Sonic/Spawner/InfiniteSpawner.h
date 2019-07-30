#pragma once
#include "Spawner.h"

class Camera;

///�����N���H��
class InfiniteSpawner : public Spawner
{
private:
	const Camera& camera;	// �J�����ւ̎Q��

	int count;

public:
	InfiniteSpawner(const Camera& camera, const Vector2f& pos, std::shared_ptr<Enemy> org);
	~InfiniteSpawner();

	//�X�|�[�i�[�G�ɓ�����܂��ɂ��̏���
	std::shared_ptr<Enemy> Spawn();

	///���t���[��1�x�Ăяo���܂��B�X�|�[�i�[�������Ă���Ċ����ł�
	///@param actors �A�N�V�����̏W����
	///@note ���̓n���ꂽ�A�N�V�����W���ɃX�|�[�i�[�������Y�ݕt����
	void Update(std::vector<std::shared_ptr<Enemy>>& enemies)override final;
};

