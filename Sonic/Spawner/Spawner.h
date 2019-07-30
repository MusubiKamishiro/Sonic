#pragma once
#include <memory>
#include <vector>
#include "../Geometry.h"

class Actor;
class Enemy;

///敵工場基底クラス
class Spawner
{
protected:
	std::shared_ptr<Enemy> original;	//プロトタイプ
	bool isSpawned;		// 生成フラグ
	Vector2f pos;		// 座標

	///最初に与えられたプロトタイプに基づくクローン生成する
	///派生クラスのSpawnやUpdateから呼び出す。
	std::shared_ptr<Enemy> CreateClone();

public:
	Spawner(std::shared_ptr<Enemy> org);
	virtual ~Spawner();
	virtual std::shared_ptr<Enemy> Spawn() = 0;
	virtual void Update(std::vector<std::shared_ptr<Enemy>>& enemies) = 0;

	Vector2f GetPos()const;
};

