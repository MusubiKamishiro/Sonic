#include "Peripheral.h"
#include <DxLib.h>
#include <assert.h>



Peripheral::Peripheral()
{
	padState.resize(DxLib::GetJoypadNum());
	oldPadState.resize(DxLib::GetJoypadNum());
}


Peripheral::~Peripheral()
{
}

void Peripheral::Update()
{
	std::copy(std::begin(keyState), std::end(keyState), oldKeyState);
	DxLib::GetHitKeyStateAll(keyState);
	for (int i = 0; i < DxLib::GetJoypadNum(); ++i)
	{
		oldPadState[i] = padState[i];
		padState[i] = DxLib::GetJoypadInputState(DX_INPUT_PAD1 + i);
	}
}

bool Peripheral::IsPressing(const unsigned short & pno, const char * cmd)const
{
	//auto range = inputTable[pno].equal_range(cmd);
	//if (range.first == range.second)
	//{
	//	return false;
	//}
	//for (auto i = range.first; i != range.second; ++i)
	//{
	//	if (i->second.padNo == 0)
	//	{
	//		if (keyState[i->second.code])
	//		{
	//			return keyState[i->second.code];
	//		}
	//		else
	//		{
	//			// パッドの場合
	//			return (padState[pno] & i->second.code);
	//		}
	//	}
	//	else
	//	{
	//		return (padState[pno - 1] & i->second.code);
	//	}
	//}
	//return false;

	auto it = inputTable[pno].find(cmd);
	if (it == inputTable[pno].end())
	{
		return false;
	}

	for (int i = 0; i < inputTable[pno].count(cmd); ++i)
	{
		// キーボードかパットか
		if (i)
		{
			++it;
		}

		// キーボードだった場合
		if (it->second.padNo == 0)
		{
			if (keyState[it->second.code])
			{
				return keyState[it->second.code];
			}
		}
		else
		{
			// パッドの場合
			return (padState[pno] & it->second.code);
		}
	}

	return false;
}


bool Peripheral::IsTrigger(const unsigned short & pno, const char * cmd) const
{
	auto it = inputTable[pno].find(cmd);
	if (it == inputTable[pno].end())
	{
		return false;
	}

	for (int i = 0; i < inputTable[pno].count(cmd); ++i)
	{
		// キーボードかパットか
		if (i)
		{
			++it;
		}

		// キーボードだった場合
		if (it->second.padNo == 0)
		{
			if (keyState[it->second.code])
			{
				return (!(oldKeyState[it->second.code]) && keyState[it->second.code]);
			}
		}
		else
		{
			// パッドの場合
			return (!(oldPadState[pno] & it->second.code) && (padState[pno] & it->second.code));
		}
	}

	return false;
}

bool Peripheral::IsReleased(const unsigned short & pno, const char * cmd) const
{
	auto it = inputTable[pno].find(cmd);
	if (it == inputTable[pno].end())
	{
		return false;
	}

	for (int i = 0; i < inputTable[pno].count(cmd); ++i)
	{
		// キーボードかパットか
		if (i)
		{
			++it;
		}

		// キーボードだった場合
		if (it->second.padNo == 0)
		{
			if (keyState[it->second.code])
			{
				return (oldKeyState[it->second.code] && (!keyState[it->second.code]));
			}
		}
		else
		{
			// パッドの場合
			return ((oldPadState[pno] & it->second.code) && (!(padState[pno] & it->second.code)));
		}
	}

	return false;
}

int Peripheral::GetPadCount() const
{
	return DxLib::GetJoypadNum();
}

void Peripheral::SetPlayerCount(int count)
{
	inputTable.resize(count);
}

int Peripheral::GetPlayerCount() const
{
	return inputTable.size();
}

void Peripheral::AddCommand(unsigned short pno, const char * cmd, int periNo, unsigned int code)
{
	assert(pno < inputTable.size());
	inputTable[pno].emplace(cmd, PeripheralInfo(periNo, code));
	inputMap.emplace(PeripheralInfo(periNo, code), std::make_pair(pno, cmd));
}

const std::vector<std::map<std::string, bool>>& Peripheral::GetCurrentState() const
{
	return currentInputState;
}

bool operator<(const PeripheralInfo & lval, const PeripheralInfo & rval)
{
	if (lval.padNo == rval.padNo)
	{
		return (lval.code < rval.code);
	}
	return (lval.padNo < rval.padNo);
}
