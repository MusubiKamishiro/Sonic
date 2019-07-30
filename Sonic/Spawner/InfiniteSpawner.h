#pragma once
#include "Spawner.h"

class Camera;

///無限湧き工場
class InfiniteSpawner : public Spawner
{
private:
	const Camera& camera;	// カメラへの参照

	int count;

public:
	InfiniteSpawner(const Camera& camera, const Vector2f& pos, std::shared_ptr<Enemy> org);
	~InfiniteSpawner();

	//スポーナー敵に当たるまさにその処理
	std::shared_ptr<Enemy> Spawn();

	///毎フレーム1度呼び出します。スポーナーも生きてるって感じです
	///@param actors アクションの集合体
	///@note この渡されたアクション集合にスポーナーが卵を産み付ける
	void Update(std::vector<std::shared_ptr<Enemy>>& enemies)override final;
};

