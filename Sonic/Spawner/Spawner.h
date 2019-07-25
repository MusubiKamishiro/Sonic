#pragma once
#include <memory>
#include <vector>

class Actor;
class Enemy;

///敵工場基底クラス
class Spawner
{
protected:
	std::shared_ptr<Enemy> original;	//プロトタイプ
	///最初に与えられたプロトタイプに基づくクローン生成する
	///派生クラスのSpawnやUpdateから呼び出す。
	std::shared_ptr<Enemy> CreateClone();

public:
	Spawner(std::shared_ptr<Enemy> org);
	virtual ~Spawner();
	virtual std::shared_ptr<Enemy> Spawn() = 0;
	virtual void Update(std::vector<std::shared_ptr<Actor>>& actors) = 0;
};

