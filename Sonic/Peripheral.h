#pragma once
#include <vector>
#include <map>

struct PeripheralInfo
{
	PeripheralInfo() {};
	PeripheralInfo(int no, int c) : padNo(no), code(c) {};

	int padNo;	// パッド番号
	int code;	// 入力コード
};

bool operator<(const PeripheralInfo& lval, const PeripheralInfo& rval);

// 周辺機器(ｷｰﾎﾞｰﾄﾞ&ﾊﾟｯﾄﾞ)の入力を制御
class Peripheral
{
private:
	char keyState[256];			// キーボードの入力情報
	char oldKeyState[256];
	std::vector<int> padState;	// パッドの入力情報
	std::vector<int> oldPadState;

	// 入力対応テーブル
	std::vector<std::multimap<std::string, PeripheralInfo>> inputTable;
	// 入力情報と利用情報
	std::map<PeripheralInfo, std::pair<unsigned short, std::string>> inputMap;
	// 現在の押下情報
	std::vector<std::map<std::string, bool>> currentInputState;

public:
	Peripheral();
	~Peripheral();

	// 入力情報の更新(毎ﾌﾚｰﾑ)
	void Update();

	// 現在の押下状態の検出
	// @param keyid　調べたいｷｰ番号
	// @pretval true 押してる, false 押してない
	bool IsPressing(const unsigned short& pno, const char* cmd)const;

	// 現在のﾄﾘｶﾞｰ状態(押した瞬間)の検出
	bool IsTrigger(const unsigned short& pno, const char* cmd)const;

	// 接続されてるパッド数を返す
	int GetPadCount()const;

	// プレイヤー数(パッド数とは関係ない)を設定
	void SetPlayerCount(int count);
	int GetPlayerCount()const;

	// コマンド設定
	//@param pno	プレイヤー番号
	//@param cmd	コマンド文字列
	//@param preiNo	入力番号
	//@param code	入力コード
	void AddCommand(unsigned short pno, const char* cmd, int periNo, unsigned int code);

	// 現在の押下状況を返す
	const std::vector<std::map<std::string, bool>>& GetCurrentState()const;
};

