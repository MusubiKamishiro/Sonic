#pragma once
#include <memory>
#include "../Geometry.h"

class Camera;
class Event;

// �X�e�[�W�ɐݒu����C�x���g�̎��
enum EventType
{
	coin,	// �R�C��
};

class EventFactory
{
private:
	const Camera& camera;

public:
	EventFactory(const Camera& camera);
	~EventFactory();

	std::shared_ptr<Event> Create(EventType type, const Vector2f& pos);
};

