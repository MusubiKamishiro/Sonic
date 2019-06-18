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

	// @param newScene 新しいシーン
	// 基本的に古いシーンは自動的に削除される
	void ChangeScene(std::unique_ptr<Scene> newScene);


	void Update(Peripheral& p);
};

