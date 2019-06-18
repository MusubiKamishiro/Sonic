#pragma once
#include <memory>

class Scene;
class Peripheral;

class SceneManager
{
private:
	SceneManager();
	SceneManager(const SceneManager&);
	void operator=(const SceneManager&);


	std::unique_ptr<Scene> scene;

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


	void Update(Peripheral& p);
};

