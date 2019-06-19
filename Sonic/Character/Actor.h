#pragma once

class Peripheral;


// 自機や敵機の基底クラス
class Actor
{
protected:


public:
	Actor();
	virtual ~Actor();

	// 状態や座標の更新
	virtual void Update(const Peripheral& p) = 0;

	// 描画
	virtual void Draw() = 0;
};

