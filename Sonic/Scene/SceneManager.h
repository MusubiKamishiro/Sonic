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

	// @param newScene 新しいシーン
	// 基本的に古いシーンは自動的に削除される
	void ChangeScene(std::unique_ptr<Scene> newScene);

	// シーンを積み上げる
	// ゲーム中のポーズなどで使う
	// 積み上げられたシーンは戻り先のシーンを知る必要がない
	void PushScene(std::unique_ptr<Scene> newScene);

	// シーンを取り出す
	// PushSceneで積み上げたシーンの中で使用する
	void PopScene();


	void Update(Peripheral& p);

	void Draw();
};

