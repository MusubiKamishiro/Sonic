#pragma once
#include "Spawner.h"
#include "../Geometry.h"

class Camera;


///��x����̐����H��
class OnetimeSpawner : public Spawner
{
private:
	bool isSpawned = false;	// �����t���O
	const Camera& camera;	// �J�����ւ̎Q��
	Vector2f pos;			// ���W

	int count;

public:
	OnetimeSpawner(const Camera& camera, const Vector2f& pos, std::shared_ptr<Enemy> org);
	~OnetimeSpawner();

	//�X�|�[�i�[�G�ɓ�����܂��ɂ��̏���
	std::shared_ptr<Enemy> Spawn();

	///���t���[��1�x�Ăяo���܂��B�X�|�[�i�[�������Ă���Ċ����ł�
	///@param actors �A�N�V�����̏W����
	///@note ���̓n���ꂽ�A�N�V�����W���ɃX�|�[�i�[�������Y�ݕt����
	void Update(std::vector<std::shared_ptr<Enemy>>& enemies)override final;
};

