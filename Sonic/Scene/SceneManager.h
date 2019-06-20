#pragma once
#include <memory>
#include <stack>

class Scene;
class Peripheral;

class SceneManager
{
private:
	SceneManager();
	SceneManager(const SceneManager&);
	void operator=(const SceneManager&);


	std::deque<std::unique_ptr<Scene>> scene;

public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
	~SceneManager();

	// @param newScene �V�����V�[��
	// ��{�I�ɌÂ��V�[���͎����I�ɍ폜�����
	void ChangeScene(std::unique_ptr<Scene> newScene);

	// �V�[����ςݏグ��
	// �Q�[�����̃|�[�Y�ȂǂŎg��
	// �ςݏグ��ꂽ�V�[���͖߂��̃V�[����m��K�v���Ȃ�
	void PushScene(std::unique_ptr<Scene> newScene);

	// �V�[�������o��
	// PushScene�Őςݏグ���V�[���̒��Ŏg�p����
	void PopScene();


	void Update(Peripheral& p);

	void Draw();
};

