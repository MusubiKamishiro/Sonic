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

	// @param newScene 新しいシーン
	// 基本的に古いシーンは自動的に削除される
	void ChangeScene(std::unique_ptr<Scene> newScene);


	void Update(Peripheral& p);
};

