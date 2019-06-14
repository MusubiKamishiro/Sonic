#pragma once
#include <vector>
#include <map>

struct PeripheralInfo
{
	PeripheralInfo() {};
	PeripheralInfo(int no, int c) : padNo(no), code(c) {};

	int padNo;	// �p�b�h�ԍ�
	int code;	// ���̓R�[�h
};

bool operator<(const PeripheralInfo& lval, const PeripheralInfo& rval);

// ���Ӌ@��(���ް��&�߯��)�̓��͂𐧌�
class Peripheral
{
private:
	char keyState[256];			// �L�[�{�[�h�̓��͏��
	char oldKeyState[256];
	std::vector<int> padState;	// �p�b�h�̓��͏��
	std::vector<int> oldPadState;

	// ���͑Ή��e�[�u��
	std::vector<std::multimap<std::string, PeripheralInfo>> inputTable;
	// ���͏��Ɨ��p���
	std::map<PeripheralInfo, std::pair<unsigned short, std::string>> inputMap;
	// ���݂̉������
	std::vector<std::map<std::string, bool>> currentInputState;

public:
	Peripheral();
	~Peripheral();

	// ���͏��̍X�V(���ڰ�)
	void Update();

	// ���݂̉�����Ԃ̌��o
	// @param keyid�@���ׂ������ԍ�
	// @pretval true �����Ă�, false �����ĂȂ�
	bool IsPressing(const unsigned short& pno, const char* cmd)const;

	// ���݂��ضް���(�������u��)�̌��o
	bool IsTrigger(const unsigned short& pno, const char* cmd)const;

	// �ڑ�����Ă�p�b�h����Ԃ�
	int GetPadCount()const;

	// �v���C���[��(�p�b�h���Ƃ͊֌W�Ȃ�)��ݒ�
	void SetPlayerCount(int count);
	int GetPlayerCount()const;

	// �R�}���h�ݒ�
	//@param pno	�v���C���[�ԍ�
	//@param cmd	�R�}���h������
	//@param preiNo	���͔ԍ�
	//@param code	���̓R�[�h
	void AddCommand(unsigned short pno, const char* cmd, int periNo, unsigned int code);

	// ���݂̉����󋵂�Ԃ�
	const std::vector<std::map<std::string, bool>>& GetCurrentState()const;
};

