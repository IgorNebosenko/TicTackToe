#include "BaseAccount.h"


BaseAccount::BaseAccount()
{
	this->s.cName[0] = 0;
}

BaseAccount::~BaseAccount()
{
}


BaseAccount::BaseAccount(const char* cName)
{
	strcpy_s(this->s.cName, 128, cName);
}


void BaseAccount::LoadFile(void)//load structure from file
{
	if (!s.cName[0])
		std::runtime_error("Empty name!");
	char buf[IBuf] = "players\\";//make string with way
	strcat_s(buf, IBuf, this->s.cName);//add to way name account
	strcat_s(buf, IBuf, ".sba");//sba = save base account 

	FILE* f = nullptr;

	if (!fopen_s(&f, buf, "rb"))//if opened for read
	{
		fread(&this->s, sizeof(this->s), 1, f);
		fclose(f);
	}
	else // if file not found - try create this file
		WriteFile(); // for don't write code 2
}


const void BaseAccount::WriteFile(void) const//write in file current info
{
	if (!s.cName[0])
		std::runtime_error("empty name!");
	char buf[IBuf] = "players\\";//make string with way
	strcat_s(buf, IBuf, this->s.cName);//add to way name account
	strcat_s(buf, IBuf, ".sba");//sba = save base account 
	
	FILE* f = nullptr;

	if (!fopen_s(&f, buf, "wb"))
	{
		fwrite(&this->s, sizeof(this->s), 1, f);
		fclose(f);
	}
	else
		throw std::runtime_error("No acces to dir \"players\"");
}


void BaseAccount::ClearGuest(void)
{
	this->s.iWin = 0;
	this->s.iLose = 0;
	this->s.iDraws = 0;
	this->WriteFile();
}
