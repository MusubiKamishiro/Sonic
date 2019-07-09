#pragma once
#include "../Geometry.h"

class Camera;

class Block
{
protected:
	Block(const Rect& rect, const Camera& camera);

	int img;
	Rect rect;

private:

public:
	// ブロック座標とか状態を更新
	virtual void Update() = 0;

	// ブロック表示
	virtual void Draw() = 0;

	// 衝突イベント
	// @param actor 相手方アクターオブジェクト
	// @param col 衝突したときの情報としてのコライダーオブジェクト
	//virtual void OnCollision(Actor* actor, const BlockCollider& col) = 0;

	// 自分が持ってるコライダーを返す
	//const BlockCollider& GetCollider()const;

	// 矩形の取得
	Rect GetCollider()const;
};

