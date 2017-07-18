#include "Player.h"


Player::Player()
{
	this->s.cName[0] = 0;
	this->sp.cPass[0] = 0;
}


Player::~Player()
{
}


Player::Player(const char* str, const char* pas)
{
	strcpy_s(this->s.cName, IName, str);
	strcpy_s(this->sp.cPass, IName, pas);
}


void Player::LoadFile(void)//look BaseAccount
{
	if (!this->s.cName[0])
		throw std::exception("Empty name!");
	if (!this->sp.cPass[0])
		throw std::exception("Password must be not null!");
	char cBuf[IBuf] = "players\\";
	strcat_s(cBuf, IBuf, this->s.cName);
	strcat_s(cBuf, IBuf, ".spa");//spa = save player account 

	FILE* f = nullptr;

	if (!fopen_s(&f, cBuf, "rb"))
	{
		fread(&this->s, sizeof(this->s), 1, f);
		fread(&this->sp, sizeof(Player::StorePlayer), 1, f);
		fclose(f);
	}
	else
		WriteFile();
}

const void Player::WriteFile(void) const
{
	char cBuf[IBuf] = "players\\";
	strcat_s(cBuf, IBuf, this->s.cName);
	strcat_s(cBuf, IBuf, ".spa");

	FILE* f = nullptr;

	if (!fopen_s(&f, cBuf, "wb"))
	{
		fwrite(&this->s, sizeof(this->s), 1, f);
		fwrite(&this->sp, sizeof(this->sp), 1, f);
		fclose(f);
	}
	else
		throw std::exception("No acces to dir \"players\"");
}


const bool Player::ComparePassword(const char* pas)const
{
	if (strlen(pas) != strlen(this->sp.cPass))//if diffrent size
		return 0;
	for (auto i = std::size_t(0); i <= strlen(pas); i++)
	{
		if (pas[i] != this->sp.cPass[i])
			return 0;
	}
	return 1;
}


char* Player::ReturnArr(void)
{
	char *tmp = new char[3];
	for (auto i = std::size_t(0); i < ISav; i++)
	{
		tmp[i] = this->sp.cSav[i];
	}
	return tmp;
}


void Player::WriteArr(char tmp[])
{
	if (tmp[0] == 0)//if array empty
		std::exception("Empty array of save!");
	for (auto i = std::size_t(0); i < ISav; i++)
	{
		this->sp.cSav[i] = tmp[i];
	}
}