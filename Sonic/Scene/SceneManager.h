#pragma once
#include <memory>

class Scene;
class Peripheral;

class SceneManager
{
private:
	std::unique_ptr<Scene> scene;

public:
	SceneManager();
	~SceneManager();

	// @param newScene �V�����V�[��
	// ��{�I�ɌÂ��V�[���͎����I�ɍ폜�����
	void ChangeScene(std::unique_ptr<Scene> newScene);


	void Update(Peripheral& p);
};

