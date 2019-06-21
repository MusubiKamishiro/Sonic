#pragma once
#include "Geometry.h"

class Camera;

enum class LayoutType 
{
	norepeat,	// 一回こッきりパーツ
	repeat,		// 一定距離ごとに繰り返し
};

class BackGround
{
private:
	const Camera& camera;
	int img;
	Vector2 ssize;

	// 背景パーツを登録する
	// @param filapath 画像ファイルパス
	// @param pos 初期座標
	// @param rate 多重スクロール用移動レート
	// @param fromBottom 下から座標計算する(ブール型)
	// @param type 繰り返しタイプ
	// @param size サイズ(デフォルトなら-1,-1となり画像のサイズが入る)
	// @param repeatX 繰り返し幅(デフォルト-1の場合画像のサイズになる)
	// @remarks 登録した順に描画されます。
	// 最背面は最初に最前面は最後に登録してください。
	void AddParts(const char* filepath, const Vector2& pos, float rate, bool fromBottom, 
		LayoutType type, Size size = Size(-1, -1), int repeatX = -1);

public:
	BackGround(const Camera& camera);
	~BackGround();

	// 描画
	void Draw();
};

