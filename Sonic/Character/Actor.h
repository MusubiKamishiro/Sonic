#pragma once
#include <vector>
#include <map>
#include <string>
#include "../Geometry.h"

class Peripheral;
class Camera;

// 矩形種別
enum class RectType
{
	attack,		// 攻撃
	damage		// やられ
};

// アクション矩形定義
struct ActRect
{
	RectType rt;	// 種別
	Rect rect;		// 形
};

// 切り抜き情報
struct CutInfo
{
	Rect rect;		// 切り抜き矩形
	Vector2 center;	// 中心点
	int duration;	// 表示時間
	std::vector<ActRect> actRects;	// アクション矩形(1つとは限らない)
};

// アクション情報
struct ActInfo
{
	bool isLoop;	// ループするならtrue
	std::vector<CutInfo> cutInfo;	// 切り抜き情報(1つとは限らない)
};

// アクションデータ
struct ActionData
{
	std::string imgFilePath;	// 画像のファイルパス
	std::map<std::string, ActInfo> animInfo;	// アニメーション情報
};

// 自機や敵機の基底クラス
class Actor
{
protected:
	const Camera& camera;

	ActionData actData;

	Vector2f pos;	// 座標
	int img;		// 画像
	bool turnFlag;	// 反転フラグ

	// ファイル読み込み
	void ReadActionFile();

	// ｱﾆﾒｰｼｮﾝのﾌﾚｰﾑを1進める
	bool ProceedAnimationFile();

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

