#include "Actor.h"
#include <DxLib.h>
#include <assert.h>
#include "../Camera.h"
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"


constexpr float nowVersion = 1.01f;	// ActonTool.exeのバージョン
constexpr float charRate = 1.5f;	// キャラクターの拡大率

void Actor::ReadData(void* inDst, size_t byteNum, size_t& cursor, ActionData& act)
{
	char* dst = (char*)inDst;
	auto rawData = act.GetRawData();
	std::copy(rawData.begin() + cursor, rawData.begin() + cursor + byteNum, dst);
	cursor += byteNum;
}

void Actor::SetActorImage()
{
	ImageData data;
	Game::Instance().GetFileSystem()->Load(actData.imgFilePath.c_str(), data);
	img = data.GetHandle();
}

void Actor::SetActor(const std::string & filePath)
{
	ReadActionFile(filePath);
	SetActorImage();
}

void Actor::ReadActionFile(const std::string& filePath)
{
	size_t cursor = 0;

	// ファイル読み込み
	ActionData data;
	Game::Instance().GetFileSystem()->Load(filePath.c_str(), data);

	// バージョンチェック(違ったら警告吐くよ)
	float version = 0.0f;
	ReadData(&version, sizeof(version), cursor, data);
	assert(version == nowVersion);

	// 画像ファイルの読み込み
	int hData = 0;
	ReadData(&hData, sizeof(hData), cursor, data);
	std::string imgFilePath = "";
	imgFilePath.resize(hData);
	ReadData(&imgFilePath[0], hData, cursor, data);
	auto ipos = filePath.find_last_of('/') + 1;
	actData.imgFilePath = filePath.substr(0, ipos) + imgFilePath;

	// アクション数取得
	int actcount = 0;
	ReadData(&actcount, sizeof(actcount), cursor, data);
	// アクション読み込み(アクション数分繰り返す)
	for (int i = 0; i < actcount; ++i)
	{
		// アクション名の読み込み
		int actNameSize = 0;
		ReadData(&actNameSize, sizeof(actNameSize), cursor, data);
		std::string actName = "";
		actName.resize(actNameSize);
		ReadData(&actName[0], actNameSize, cursor, data);

		ActInfo actInfo;

		// ループするかを確認
		ReadData(&actInfo.isLoop, sizeof(actInfo.isLoop), cursor, data);

		// カットデータ数(コマ数)を取得
		int cutCount = 0;
		ReadData(&cutCount, sizeof(cutCount), cursor, data);
		actInfo.cutInfo.resize(cutCount);

		// カットデータ読み込み(カットデータ数分繰り返す)
		for (int j = 0; j < cutCount; ++j)
		{
			// まず当たり矩形以外を読み込む
			ReadData(&actInfo.cutInfo[j], (sizeof(actInfo.cutInfo[j]) - sizeof(actInfo.cutInfo[j].actRects)), cursor, data);

			// あたり矩形数取得
			int rectCount = 0;
			ReadData(&rectCount, sizeof(rectCount), cursor, data);

			// あたり矩形がなければ読み込みをスキップ
			if (rectCount == 0)
			{
				continue;
			}
			actInfo.cutInfo[j].actRects.resize(rectCount);
			ReadData(&actInfo.cutInfo[j].actRects[0], sizeof(ActRect) * rectCount, cursor, data);
		}

		// マップに登録
		actData.animInfo[actName] = actInfo;
	}
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

	DxLib::DrawRectRotaGraph2(pos.x - offset.Left(), pos.y - offset.Top(), nowAct.rect.Left(), nowAct.rect.Top(),
		nowAct.rect.Width(), nowAct.rect.Height(), centerX, nowAct.center.y, charRate, angle, img, true, turnFlag);

#ifdef _DEBUG
	DebugDraw();
#endif // _DEBUG

}

void Actor::DebugDraw()
{
	auto& cPos = camera.GetViewRange();
	auto left = cPos.Left();
	auto top = cPos.Top();

	auto& actrcInfo = actData.animInfo[nowActionName];
	auto& rcCut = actrcInfo.cutInfo[nowCutIndex];

	// 右側のものを左側の形に入れて最初から最後まで見る
	for (auto& i : rcCut.actRects)
	{
		auto& actRc = i;

		Rect rc = actRc.rect;
		rc.center.x = turnFlag ? -rc.center.x : rc.center.x;

		DxLib::DrawBox(rc.Left() * charRate + pos.x - left, rc.Top() * charRate + pos.y - top,
			rc.Right() * charRate + pos.x - left, rc.Bottom() * charRate + pos.y - top, 0xff0000, false);
	}
}

Actor::Actor(const Camera& camera) : camera(camera)
{
	ChangeAction("idle");
	angle = 0.0f;
	accel = 0.0f;
	turnFlag = false;
}


Actor::~Actor()
{
}

Vector2f Actor::GetPos() const
{
	return pos;
}

Rect Actor::GetRect()
{
	return actData.animInfo[nowActionName].cutInfo[nowCutIndex].rect;
}

std::vector<ActRect> Actor::GetActRect()
{
	return actData.animInfo[nowActionName].cutInfo[nowCutIndex].actRects;
}

Rect Actor::GetHitRect(Rect & rc)
{
	Rect rect = rc;

	rect.center.x = turnFlag ? -rect.center.x : rect.center.x;

	rect.center.x += pos.x;
	rect.center.y += pos.y;
	rect.size.height *= charRate;
	rect.size.width *= charRate;

	return rect;
}
