#pragma once
#include <vector>
#include <map>
#include <string>
#include "../Geometry.h"
#include "../System/ActionLoader.h"

class Peripheral;
class Camera;

// 矩形種別
enum class RectType
{
	adjust,		// 押し戻し調整
	attack,		// 攻撃
	damage,		// やられ
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
struct ActData
{
	std::string imgFilePath;	// 画像のファイルパス
	std::map<std::string, ActInfo> animInfo;	// アニメーション情報
};

// 自機や敵機の基底クラス
class Actor
{
private:
	///ReadActionFileの時に使う
	///@param inDst データの移動先
	///@param byteNum 今回読み込む範囲の大きさ
	///@param cursor カーソル, 今まで読み込んだ位置
	///@param act アクションデータ
	void ReadData(void* inDst, size_t byteNum, size_t& cursor, ActionData& act);

	// ファイル読み込み
	void ReadActionFile(const std::string& filePath);
	// キャラの画像を設定
	void SetActorImage();

protected:
	const Camera& camera;

	ActData actData;	// アクションデータ

	Vector2f pos;	// 座標
	int img;		// 画像
	bool turnFlag;	// 反転フラグ
	float angle;	// 回転率
	float accel;	// 加速度
	
	std::string nowActionName;	// 現在のアクション名
	int nowCutIndex;			// 現在のコマ(何番目のコマか)
	unsigned int frame;			// 経過フレーム

	// キャラを設定
	void SetActor(const std::string& filePath);

	// ｱﾆﾒｰｼｮﾝのﾌﾚｰﾑを1進める
	bool ProceedAnimationFile();

	// アクション切り替え
	void ChangeAction(const char* actname);

	// 描画
	void Draw();
	/// 当たり矩形を表示
	void DebugDraw();

public:
	Actor(Camera& camera);
	virtual ~Actor();

	// 状態や座標の更新
	virtual void Update(const Peripheral& p) = 0;

	// 座標の取得
	Vector2f GetPos()const;

	// 矩形の取得
	Rect GetRect();
	// あたり矩形の取得
	std::vector<ActRect> GetActRect();
	// 矩形の場所を合わせる
	Rect GetHitRect(Rect& rc);
};

