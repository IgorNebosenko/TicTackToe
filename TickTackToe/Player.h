#pragma once
#include "BaseAccount.h"

const int ISav = 9;

class Player :
	public BaseAccount
{
public:
	struct StorePlayer
	{
		char cPass[IName];//password
		char cSav[ISav];//Save of array game as 1d arr
		bool bCross = false;//Symbol of player crosses or 0
		char cLastEnemy[IName];//last player with who plays player
		bool bFirst = true;//player go first or second?
	};
	StorePlayer sp;
public:
	Player();
	~Player();
	explicit Player(const char*, const char*);
	void LoadFile(void);
	const void WriteFile(void) const;
	const bool ComparePassword(const char*)const;//function for compare password
	char* ReturnArr(void);
	void WriteArr(char[]);
};

