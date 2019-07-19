#include "Camera.h"
#include "Actor/Player.h"
#include "Game.h"


Camera::Camera()
{
	ssize = Game::Instance().GetScreenSize();
}


Camera::~Camera()
{
}

void Camera::AddPlayer(std::shared_ptr<Player> addPlayer)
{
	player.push_back(addPlayer);
}

void Camera::RemovePlayer(std::shared_ptr<Player> removePayer)
{
	for (int i = 0; i < player.size(); ++i)
	{
		if (player.at(i) == removePayer)
		{
			player.erase(player.begin() + i);
			break;
		}
	}
}

void Camera::SetRange(const Size & stageSize)
{
}

void Camera::Update()
{
	// �v���C���[�̍��W�ɂ��킹��
	pos = player.at(0)->GetPos();

	// ��ʂ̌��E���W���ӂł���Γ����Ȃ��悤�ɂ���
	if (pos.x < (ssize.x / 2))
	{
		pos.x = ssize.x / 2;
	}
	if (pos.y < ssize.y / 2)
	{
		pos.y = ssize.y / 2;
	}
}


Vector2f Camera::GetPos() const
{
	return pos;
}

const Rect Camera::GetViewRange() const
{
	return Rect(pos.x, pos.y, ssize.x, ssize.y);
}
