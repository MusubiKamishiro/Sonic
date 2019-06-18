#pragma once
#include <memory>
#include "Scene/Scene.h"
#include "Geometry.h"

class Peripheral;
class SceneManager;

class Game
{
private:
	// シングルトンやで
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

	// 初期化
	// 最初に一回だけ呼ぶ
	void Initialize();

	void InitPeripheral();

	// ゲーム中
	// この中にループがある
	void Run();

	// 後処理
	// 最後の最後に一回だけ呼ぶ
	void Terminate();

	// 画面サイズの取得
	const Vector2 GetScreenSize()const;
};

