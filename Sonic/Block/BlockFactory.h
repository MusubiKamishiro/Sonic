#pragma once
#include <memory>
#include "../Geometry.h"

class Camera;
class Block;


// �X�e�[�W�ɐݒu����u���b�N�̎��
enum BlockType
{
	brick,		// �Œ�u���b�N
	slide,		// ���E�Ɉړ�����z
	lift,		// �㉺�Ɉړ�����z
	pendulum,	// �U��q�ňړ�����z
	broken,		// ���������󂷂�z(�������͗�������)
};


class BlockFactory
{
private:
	const Camera& camera;

public:
	BlockFactory(const Camera& camera);
	~BlockFactory();

	// �u���b�N�𐶐�����
	// @param type �ǂ̎�ʂ̃u���b�N�𐶐����邩
	// @param pos �ǂ��ɐ������邩
	std::shared_ptr<Block> Create(BlockType type, const Vector2& pos, unsigned int runLength);
};

