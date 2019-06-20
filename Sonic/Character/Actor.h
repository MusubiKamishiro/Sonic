#pragma once
#include "../Geometry.h"

class Peripheral;
class Camera;


// 自機や敵機の基底クラス
class Actor
{
protected:
	Vector2f pos;	// 座標
	int img;		// 画像
	bool turnFlag;	// 反転フラグ

public:
	Actor(Camera& camera);
	virtual ~Actor();

	// 状態や座標の更新
	virtual void Update(const Peripheral& p) = 0;

	// 描画
	virtual void Draw() = 0;

	// 座標の取得
	Vector2f GetPos()const;
};

