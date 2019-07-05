#pragma once
#include <memory>
#include "../Geometry.h"

// �X�e�[�W�ɐݒu����u���b�N�̎��
enum BlockType
{
	brick,		// �Œ�u���b�N
	lift,		// �㉺�Ɉړ�����z
	slide,		// ���E�Ɉړ�����z
	pendulum,	// �U��q�ňړ�����z
	broken,		// ���������󂷂�z(�������͗�������)
};

class Actor;
class Camera;
class BlockCollider;
class Block;


class BlockFactory
{
private:
	

public:
	BlockFactory(const Camera& camera);
	~BlockFactory();

	// �u���b�N�𐶐�����
	// @param type �ǂ̎�ʂ̃u���b�N�𐶐����邩
	// @param pos �ǂ��ɐ������邩
	std::unique_ptr<Block> Create(BlockType type, const Camera& camera, const Vector2& pos);
};

