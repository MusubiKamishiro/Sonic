#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class Ground;
class Block;
class Spawner;
class Event;
class BlockFactory;
class SpawnerFactory;
class EventFactory;

class Player;
class Camera;

// �ð�ނ̏��
struct StageInfo
{
	unsigned int id;			// ̧�ق�ID
	unsigned int size;			// ͯ�ނ��������ް�����
	unsigned int mapWidth;		// ϯ�ߑS�̂̉���
	unsigned int mapHeight;		// ϯ�ߑS�̂̏c��
	unsigned char chipWidth;	// 1Ͻ�̉���
	unsigned char chipHeight;	// 1Ͻ�̏c��
	unsigned char layerCount;	// ڲ԰��
	unsigned char bitCount;		// ڲ԰�ް����ޯĶ���
};


class Stage
{
private:
	StageInfo stageInfo;
	std::vector<unsigned char> stageData;	// �X�e�[�W�̃f�[�^
	std::vector<std::shared_ptr<Block>> blockData;	// �u���b�N�̃f�[�^
	std::vector<std::shared_ptr<Spawner>> spawnerData;
	std::vector<std::shared_ptr<Event>> eventData;

	std::shared_ptr<BlockFactory> blockFactory;
	std::shared_ptr<SpawnerFactory> spawnerFactory;
	std::shared_ptr<EventFactory> eventFactory;

public:
	Stage();
	~Stage();

	// �X�e�[�W�̓ǂݍ���
	//@param stagePath �X�e�[�W�̃p�X
	void ReadStageFile(const char* stagePath, Ground& ground, Player& player, Camera& camera);

	std::vector<unsigned char> GetStageData()const;
	std::vector<std::shared_ptr<Block>> GetBlockData()const;
	std::vector<std::shared_ptr<Spawner>> GetSpawnerData()const;
	std::vector<std::shared_ptr<Event>> GetEventData()const;
};

