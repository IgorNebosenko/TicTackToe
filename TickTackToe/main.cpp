#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include "BaseAccount.h"
#include "Player.h"
#include "Functions.h"
#include <Windows.h>

//version 0.1.1 preAlpha

int main(void)
{
	try
	{
		BaseAccount CPU("CPU"), Guest("Guest");//inizilize account CPU and Guest
		Guest.ClearGuest();
		Player player;
		Player enemy;

		int iStatus = 1;
		while (iStatus)
		{
			if (iStatus == -1)//catch for abnoraly close game
				throw std::exception("Game anomaly closed!");
			switch (iStatus)
			{
			case 1://Draws menu, and return 
				iStatus = DrawMenu();
				break;
			case 2://Selects type of PvP 
				iStatus = ComparePvP(player, enemy);
				break;
			case 3://selects type of PvCPU
				iStatus = ComparePvCPU(player);
				break;
			case 4://select player
				iStatus = SelectPlayer(player, enemy);
				break;
			case 5://Help
				iStatus = Help();
				break;
				break;
			case 6://Logs
				iStatus = DrawLog();
				break;
			case 7://exit
				exit(0);
				break;
			case 10://Normal PvP
				iStatus = PvP(player, enemy);
				break;
			case 11://PvP with Player and Guest
				iStatus = PvP(player, Guest);
				break;
			case 12://Normal PvCPU
				iStatus = PvCPU(player, CPU);
				break;
			case 13:
				std::cout << "You find Easter egg) This is case 13" << std::endl;
				break;
			case 14://PvCRU witch player is guest 
				iStatus = PvCPU(Guest, CPU);
				break;
			}
			Sleep(300);//this need fornot pressed in more than 1 button
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unhandled exception" << std::endl;
	}
	system("pause");//for see exception
	return 0;
}