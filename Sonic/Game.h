#pragma once
#include <memory>
#include "Scene/Scene.h"
#include "Geometry.h"

class Peripheral;

class Game
{
private:
	// シングルトンやで
	Game();
	Game(const Game&);
	void operator=(const Game&);

	const Vector2 screenSize;
	std::unique_ptr<Peripheral> p;

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

	// 現在実行中のｼｰﾝの管理
	std::shared_ptr<Scene> scene;

	// ｼｰﾝ入れ替え
	void ChangeScene(Scene* s);

	// 画面サイズの取得
	Vector2 GetScreenSize()const;
};

