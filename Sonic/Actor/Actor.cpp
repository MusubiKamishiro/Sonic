#include "Actor.h"
#include <DxLib.h>
#include <assert.h>
#include "../Camera.h"
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"


constexpr float nowVersion = 1.01f;	// ActonTool.exe�̃o�[�W����
constexpr float charRate = 1.5f;	// �L�����N�^�[�̊g�嗦

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

	// �t�@�C���ǂݍ���
	ActionData data;
	Game::Instance().GetFileSystem()->Load(filePath.c_str(), data);

	// �o�[�W�����`�F�b�N(�������x���f����)
	float version = 0.0f;
	ReadData(&version, sizeof(version), cursor, data);
	assert(version == nowVersion);

	// �摜�t�@�C���̓ǂݍ���
	int hData = 0;
	ReadData(&hData, sizeof(hData), cursor, data);
	std::string imgFilePath = "";
	imgFilePath.resize(hData);
	ReadData(&imgFilePath[0], hData, cursor, data);
	auto ipos = filePath.find_last_of('/') + 1;
	actData.imgFilePath = filePath.substr(0, ipos) + imgFilePath;

	// �A�N�V�������擾
	int actcount = 0;
	ReadData(&actcount, sizeof(actcount), cursor, data);
	// �A�N�V�����ǂݍ���(�A�N�V���������J��Ԃ�)
	for (int i = 0; i < actcount; ++i)
	{
		// �A�N�V�������̓ǂݍ���
		int actNameSize = 0;
		ReadData(&actNameSize, sizeof(actNameSize), cursor, data);
		std::string actName = "";
		actName.resize(actNameSize);
		ReadData(&actName[0], actNameSize, cursor, data);

		ActInfo actInfo;

		// ���[�v���邩���m�F
		ReadData(&actInfo.isLoop, sizeof(actInfo.isLoop), cursor, data);

		// �J�b�g�f�[�^��(�R�}��)���擾
		int cutCount = 0;
		ReadData(&cutCount, sizeof(cutCount), cursor, data);
		actInfo.cutInfo.resize(cutCount);

		// �J�b�g�f�[�^�ǂݍ���(�J�b�g�f�[�^�����J��Ԃ�)
		for (int j = 0; j < cutCount; ++j)
		{
			// �܂��������`�ȊO��ǂݍ���
			ReadData(&actInfo.cutInfo[j], (sizeof(actInfo.cutInfo[j]) - sizeof(actInfo.cutInfo[j].actRects)), cursor, data);

			// �������`���擾
			int rectCount = 0;
			ReadData(&rectCount, sizeof(rectCount), cursor, data);

			// �������`���Ȃ���Γǂݍ��݂��X�L�b�v
			if (rectCount == 0)
			{
				continue;
			}
			actInfo.cutInfo[j].actRects.resize(rectCount);
			ReadData(&actInfo.cutInfo[j].actRects[0], sizeof(ActRect) * rectCount, cursor, data);
		}

		// �}�b�v�ɓo�^
		actData.animInfo[actName] = actInfo;
	}
}

bool Actor::ProceedAnimationFile()
{
	// �\�����Ԃ𒴂��Ă�Ȃ玟�̃R�}��
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

	// ���]�����������S�����킹�邽��
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

	// �E���̂��̂������̌`�ɓ���čŏ�����Ō�܂Ō���
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
