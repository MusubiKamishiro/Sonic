#include "Actor.h"
#include <DxLib.h>
#include <assert.h>
#include "../Camera.h"

constexpr float nowVersion = 1.01f;	// ActonTool.exeのバージョン

void Actor::ReadActionFile()
{
	std::string filePath = "action/player.act";

	// ファイル読み込み
	int handle = DxLib::FileRead_open(filePath.c_str(), false);
	
	// バージョンチェック(違ったら警告吐くよ)
	float version;
	DxLib::FileRead_read(&version, sizeof(version), handle);
	assert(version == nowVersion);

	// 画像ファイルの読み込み
	int hData;
	DxLib::FileRead_read(&hData, sizeof(hData), handle);
	std::string imgFilePath = "";
	imgFilePath.resize(hData);
	DxLib::FileRead_read(&imgFilePath[0], hData, handle);
	auto ipos = filePath.find_last_of('/') + 1;
	actData.imgFilePath = filePath.substr(0, ipos) + imgFilePath;

	// アクション数取得
	int actcount = 0;
	DxLib::FileRead_read(&actcount, sizeof(actcount), handle);
	// アクション読み込み(アクション数分繰り返す)
	for (int i = 0; i < actcount; ++i)
	{
		// アクション名の読み込み
		int actNameSize = 0;
		DxLib::FileRead_read(&actNameSize, sizeof(actNameSize), handle);
		std::string actName = "";
		actName.resize(actNameSize);
		DxLib::FileRead_read(&actName[0], actNameSize, handle);

		ActInfo actInfo;

		// ループするかを確認
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), handle);

		// カットデータ数(コマ数)を取得
		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), handle);
		actInfo.cutInfo.resize(cutCount);

		// カットデータ読み込み(カットデータ数分繰り返す)
		for (int j = 0; j < cutCount; ++j)
		{
			// まず当たり矩形以外を読み込む
			DxLib::FileRead_read(&actInfo.cutInfo[j], (sizeof(actInfo.cutInfo[j]) - sizeof(actInfo.cutInfo[j].actRects)), handle);

			// あたり矩形数取得
			int rectCount = 0;
			DxLib::FileRead_read(&rectCount, sizeof(rectCount), handle);

			// あたり矩形がなければ読み込みをスキップ
			if (rectCount == 0)
			{
				continue;
			}
			actInfo.cutInfo[j].actRects.resize(rectCount);
			DxLib::FileRead_read(&actInfo.cutInfo[j].actRects, sizeof(ActRect) * rectCount, handle);
		}

		// マップに登録
		actData.animInfo[actName] = actInfo;
	}

	// 最後はファイルを閉じる
	DxLib::FileRead_close(handle);
}

bool Actor::ProceedAnimationFile()
{
	// 表示時間を超えてるなら次のコマへ
	if (frame < actData.animInfo[nowActionName].cutInfo[nowCutIndex].duration)
	{
		++frame;
	}
	else
	{
		frame = 0;
		if (nowCutIndex < (actData.animInfo[nowActionName].cutInfo.size() - 1))
		{
			++nowCutIndex;
		}
		else
		{
			nowCutIndex = 0;
		}
	}

	return false;
}

void Actor::ChangeAction(const char * actname)
{
	nowActionName = actname;
	nowCutIndex = 0;
	frame = 0;
}

void Actor::Draw()
{
	auto& offset = camera.GetViewRange();
	auto& nowAct = actData.animInfo[nowActionName].cutInfo[nowCutIndex];

	// 反転した時も中心を合わせるため
	int centerX = 0;
	centerX = turnFlag ? nowAct.rect.Width() - nowAct.center.x : nowAct.center.x;

	DxLib::DrawRectRotaGraph2(pos.x - offset.Left(), pos.y/* - offset.Top()*/, nowAct.rect.Left(), nowAct.rect.Top(),
		nowAct.rect.Width(), nowAct.rect.Height(), centerX, nowAct.center.y, 2.0f, turnFlag ? -angle : angle, img, true, turnFlag);
}

Actor::Actor(Camera& camera) : camera(camera)
{
	ChangeAction("idle");
	angle = 0.0f;
	accel = 0.0f;
}


Actor::~Actor()
{
}

Vector2f Actor::GetPos() const
{
	return pos;
}
