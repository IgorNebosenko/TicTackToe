#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "BaseAccount.h"
#include <string.h>
#include <io.h>
#include <Windows.h>
#include <time.h>

const int WIDTH = 1024;
const int HEIGHT = 576;
const std::size_t IButtonMenu = 6;
const std::size_t ITextMenu = 7;
const int ISizeButton = 256;
const int IIntervalWindow = 25;
const int ISizeChar = 9;
const float FSizeText = 0.8f;
const std::size_t ITextSelect = 9;
const std::size_t IButtonSelect = 6;
const std::size_t ISizeLabel = 10;

int DrawMenu(void); //Draws menu and returns iStatus
int ComparePvP(const Player& player, const Player& enemy);//compares account players. Returns iStatus
int DrawMessage(const char* message, bool sw, int secRet = 1);//Draws same message. Dool - draw buttons yes/no or not
int ComparePvCPU(const Player& player);//compare account player
int SelectPlayer(Player& player, Player& enemy);//function for player autorize
int Help(void);//draw help about game
int DrawLog(void);//draw log who plays with who
//additional functions
int CountPlayers(void);//count number of players
BaseAccount::Store* LabelOfPlayers(void);//returns structure whith same parametrs size - from previous f()
void LoadAccount(Player& user, Player& second, BaseAccount::Store* list);
void CreateAccount(BaseAccount::Store* list);
void WriteLog(std::string& str);//write to log
//game windows
int PvP(Player& player, Player& enemy);//normal pvp
int PvP(Player& player, BaseAccount& guest);//player vs guest
int PvCPU(Player& player, BaseAccount& CPU);//normal PvCPU
int PvCPU(BaseAccount& Guest, BaseAccount& CPU);//Guest vs CPU
//game scripts
bool EditCell(char* cArray, sf::Vector2i& iMousePos, bool bStep);//return true if edit
bool WinCell(char* cArray, bool bStep);//check win
int CountArr(char* cArray);//counts number of rmpty cells
bool SelectDifficult(void);//show menu with switch difficult with pc
void LogicCPU(char* cGame, bool bDifficult, bool bStep);//logic of PC