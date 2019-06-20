#include "Camera.h"
#include "Character/Player.h"


Camera::Camera()
{
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
	// プレイヤーの座標にあわせる
	pos = player.at(0)->GetPos();
}

Vector2f Camera::GetPos() const
{
	return pos;
}

const Rect & Camera::GetViewRange() const
{
	return Rect();
}
