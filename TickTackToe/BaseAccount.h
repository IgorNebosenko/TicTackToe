#pragma once
#include <iostream>
#include <exception>
//works correct

const std::size_t IName = 128;
const std::size_t IBuf = 256;

class BaseAccount//base account for CPU and guest
{
public://need for write in menu
	struct Store
	{
		char cName[IName];//name
		int iWin = 0;//wins
		int iLose = 0;//Loses
		int iDraws = 0;//Draws
	};
protected:
	Store s;
public:
	BaseAccount();//standart constructor
	explicit BaseAccount(const char*);//constructor with name in parametr
	~BaseAccount();//standart destructor
	void LoadFile(void);//Load structure from file
	const void WriteFile(void) const;//write in file current structure
	const int ReturnWins(void) const throw()//returns number of wins
	{
		return this->s.iWin;
	}
	const int ReturnLoses(void) const throw()//returns number of losses
	{
		return this->s.iLose;
	}
	const int ReturnDraws(void) const throw()//return number of draws
	{
		return this->s.iDraws;
	}
	const char* ReturnName(void)const throw()//returns name
	{
		return this->s.cName;
	}
	void AddWin(void)//add 1 win
	{
		this->s.iWin++;
	}
	void AddLose(void)//add 1 lose
	{
		this->s.iLose++;
	}
	void AddDraw(void)//add 1 draw
	{
		this->s.iDraws++;
	}
	void ClearGuest(void);//Clears Base Account. For guest
};

