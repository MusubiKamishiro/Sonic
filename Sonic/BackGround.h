#pragma once
#include <vector>
#include "Geometry.h"

class Camera;

enum class LayoutType 
{
	norepeat,	// 一回こッきりパーツ
	repeat,		// 一定距離ごとに繰り返し
};

// 背景のパーツ
struct BGObject
{
	int handle;			// 背景パーツ画像ハンドル
	Vector2 pos;		// 座標
	float rate;			// 移動レート(小さいほど動かない)
	LayoutType type;	// 背景の配置タイプ
	int repeatX;		// 繰り返し距離
	Size size;			// 拡大後のサイズ

	BGObject() {}
	BGObject(int h, const Vector2& p, float r, LayoutType lt, int repX, Size s) : handle(h), pos(p), rate(r), type(lt), repeatX(repX), size(s) {}
};

class BackGround
{
private:
	const Camera& camera;
	int img;
	Vector2 ssize;

	std::vector<BGObject> bgParts;

public:
	BackGround(const Camera& camera);
	~BackGround();

	// 背景パーツを登録する
	// @param filapath 画像ファイルのパス
	// @param pos 初期座標
	// @param rate 多重スクロール用の移動レート
	// @param fromBottom 下から座標計算する(ブール型)
	// @param type 繰り返しタイプ
	// @param size サイズ(デフォルトなら-1,-1となり画像のサイズが入る)
	// @param repeatX 繰り返し幅(デフォルト-1の場合画像のサイズになる)
	// @remarks 登録した順に描画されます。
	// 最背面は最初に最前面は最後に登録してください。
	void AddParts(const char* filepath, const Vector2& pos, float rate, bool fromBottom,
			LayoutType type, Size size = Size(-1, -1), int repeatX = -1);

	// 描画
	void Draw();
};

