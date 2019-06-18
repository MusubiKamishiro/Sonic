#pragma once
#include <memory>
#include "Scene/Scene.h"
#include "Geometry.h"

class Peripheral;
class SceneManager;

class Game
{
private:
	// �V���O���g�����
	Game();
	Game(const Game&);
	void operator=(const Game&);

	const Vector2 screenSize;
	std::unique_ptr<Peripheral> p;
	std::unique_ptr<SceneManager> sceneManager;

public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}
	~Game();

	// ������
	// �ŏ��Ɉ�񂾂��Ă�
	void Initialize();

	void InitPeripheral();

	// �Q�[����
	// ���̒��Ƀ��[�v������
	void Run();

	// �㏈��
	// �Ō�̍Ō�Ɉ�񂾂��Ă�
	void Terminate();

	// ��ʃT�C�Y�̎擾
	const Vector2 GetScreenSize()const;
};

