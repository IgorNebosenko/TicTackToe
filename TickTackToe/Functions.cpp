#include "Functions.h"
int DrawMenu(void)
{
	const std::string STextMenu[ITextMenu] =
		{"\t\t\tМеню",
		"Игрок против игрока",
		"\tИгрок против ПК",
		"\t\tВыбор игроков",
		"\t\t\tПомощь",
		"\t\t\tЛоги игр",
		"\t\t \tВыход"};//text of menu


	const float FSizeText = 0.8f;
	sf::Vector2i iMousePos;//gets position of mouse
	//This Vector ned to see position of mouse, and return iStatus if pressed "Button"
	//Updates in while

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::RenderWindow wMenu(sf::VideoMode(WIDTH, HEIGHT), "Tick-Tack-Toe", sf::Style::Close);
	//renders window of Menu

	sf::Event eClose;//event for test pressed button "cross"

	while (wMenu.isOpen())//wile opened menu window
	{
		while (wMenu.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wMenu.close();//close this window

			iMousePos = sf::Mouse::getPosition(wMenu);//get position of mouse on display

			float fPosYButton = 100.f;//set first position of button
			const float FIntervalY = 65.f;//interval betwen buttons;
			const float FPosXButton = WIDTH / 2 - ISizeButton / 2;//set position of buttons
			for (auto i = std::size_t(0); i < IButtonMenu; i++)//cycle of draw buttons
			{
				sButton.setPosition(FPosXButton, fPosYButton);//seet position
				fPosYButton += FIntervalY;//edit position in OY
				wMenu.draw(sButton);//draw button
			}
			fPosYButton = 100.f;

			float fPosYText = 50.f;//set first position of text
			//interval of Text == interval of Buttons
			const float FPosXText = FPosXButton + 20;//equals button 
			//But has same space from ends of button
			for (auto i = std::size_t(0); i < ITextMenu; i++)//cycle of draw text
				//Must be after Buttons, else text draws under buttons
			{
				tText.setString(STextMenu[i]);//set text from string
				tText.setPosition(FPosXText, fPosYText);//set position
				fPosYText += FIntervalY;
				wMenu.draw(tText);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) //if presed left mouse button
				&& iMousePos.x >= FPosXButton && iMousePos.x <= FPosXButton + ISizeButton)
				//if click in position OX where sprite-buttons
			{
				for (auto i = std::size_t(0); i < IButtonMenu; i++)
				{
					if (iMousePos.y >= fPosYButton + i * FIntervalY//if more or equal from top button
						&& iMousePos.y < fPosYButton + (i + 1) * FIntervalY)//and less than bottom
					return i + 2;//return iStatus
				}
			}

			wMenu.display();
			wMenu.clear();
		}
	}
	return -1;
}


int ComparePvP(const Player& player, const Player& enemy)
{
	//if players not load - their name are empty
	//so if first char in they names is '\0' - this players not load
	if (player.ReturnName()[0] != 0 && enemy.ReturnName()[0] != 0)
	//if players are loaded
		return 10;//return normal PvP
	//no messages in this if

	if (player.ReturnName()[0] != 0 && enemy.ReturnName()[0] == 0)
		//if first player logged in, but secong not loged in
		return DrawMessage("2 игрок не вошёл. Продолжить?", true, 11);//returns message with switch

	else//if first player not loged in. Logged in second - not matter
		return DrawMessage("1 игрок должен войти!", false);
		//No switch. Returns to menu
}


int DrawMessage(const char* message, bool sw, int secReturn)
{
	//first at all need has lenth of window. for this - compares minimal size and size string
	int ISizeY = 200;
	int iSizeX = 0;//lenth
	if (sw)//if 2 buttons
		iSizeX = ISizeButton * 2 > strlen(message) * ISizeChar ? //what size is biggest
		(ISizeButton + IIntervalWindow) * 2 : strlen(message) * ISizeChar + 2 * IIntervalWindow;
	//and add 25px interval
	else // if 1 button
		iSizeX = ISizeButton > strlen(message) * ISizeChar ?
		ISizeButton + 2 * IIntervalWindow : strlen(message) * ISizeChar + 2 * IIntervalWindow;

	sf::Vector2i iMousePos;//gets position of mouse

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px
	sf::Text tBuf = tText;
	std::string str(message);//for text SFML used standart string
	tText.setString(str);//set text
	tText.setPosition(float(IIntervalWindow), float(IIntervalWindow));//sets position of text

	sf::RenderWindow wMessage(sf::VideoMode(iSizeX, ISizeY), "Warning!", sf::Style::Close);
	//makes window message

	sf::Event eClose;//event for test pressed button "cross"


	std::string sBuf[2] = { "В меню", "Продолжить" };
	while (wMessage.isOpen())//wile opened menu window
	{
		while (wMessage.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wMessage.close();//close this window


			sButton.setPosition(float(IIntervalWindow), 128.f);//set position for sprite of button
			wMessage.draw(sButton);//draws button

			tBuf.setString(sBuf[0]);//swt string for text on button
			tBuf.setPosition(float(2 * IIntervalWindow), 144.f);//set position
			wMessage.draw(tBuf);//draw text button

			if (sw)//if second button
			{
				sButton.setPosition(IIntervalWindow + ISizeButton + 1, 128.f);//set position second button
				wMessage.draw(sButton);//draw second button

				tBuf.setString(sBuf[1]);//swt string for text on button
				tBuf.setPosition(float(2 * IIntervalWindow + ISizeButton), 144.f);//set position
				wMessage.draw(tBuf);//draw text button
			}

			iMousePos = sf::Mouse::getPosition(wMessage);//get position of mouse on display
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) //if presed left mouse button
				&& iMousePos.y >= 128 && iMousePos.y <= 192)
			{
				if (iMousePos.x >= IIntervalWindow && iMousePos.x < IIntervalWindow + ISizeButton)
					return 1;//return to menu
				if (sw && iMousePos.x >= IIntervalWindow + ISizeButton &&
					iMousePos.x < IIntervalWindow + 2 * ISizeButton)
					return secReturn;//return PvP vs guest
			}

			wMessage.draw(tText);//draws message
			wMessage.display();//display window
			wMessage.clear();
		}
	}
	return -1;//abnormaly close
}


int ComparePvCPU(const Player& player)
{
	//analogical ComparePvP, but for one player
	if (player.ReturnName()[0] != 0)
		return 12;
	else
		return DrawMessage("Вы не вошли. Продолжить игру как гость?", true, 14);
}


int SelectPlayer(Player& player, Player& enemy)//нужно написать функцию
{
	const float FButtonNavigation = 32.f;
	const float FButtonMove = 512.f;
	const float FTextNavigation = 72.f;
	const float FTextMove = 530.f;
	int iCurrPage = 1;
	int iMaxPage = CountPlayers() / 10  + 1;
	char num[16] = { 0 };
	const float FFistLabel = 150.f;
	const float FIntervalLabel = 30.f;
	const float FPosWin = WIDTH / 3 * 2;
	const float FPosLoses = FPosWin + 100;
	const float FPosDraws = FPosLoses + 130;
	BaseAccount::Store *spp = new BaseAccount::Store[CountPlayers()];
	sf::Vector2i iMousePos;//gets position of mouse
	spp = LabelOfPlayers();

	std::string buf;//need for output on window

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::RenderWindow wSelect(sf::VideoMode(WIDTH, HEIGHT), "SelectPlayer", sf::Style::Close);

	sf::Event eClose;//event for test pressed button "cross"

	while (wSelect.isOpen())//wile opened menu window
	{
		while (wSelect.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wSelect.close();//close this window

			for (auto i = std::size_t(0); i < IButtonSelect; i++)
			{
				if (i < 4)
				{
					sButton.setPosition(float(ISizeButton * i),
						float(IIntervalWindow + FButtonNavigation));
				}
				else if (i == 4)//button previous
				{
					sButton.setPosition(float(IIntervalWindow), FButtonMove);
				}
				else//button next
				{
					sButton.setPosition(float(WIDTH - IIntervalWindow - ISizeButton), FButtonMove);
				}
				
				wSelect.draw(sButton);
			}
			

			for (auto i = std::size_t(0); i < ITextSelect; i++)//draw text
			{
				if (i == 0)//if names of players
				{
					if (player.ReturnName()[0] == 0)//if player not loged in
						buf = "Пусто";
					else//else load him name
						buf = player.ReturnName();
					
					tText.setPosition(float(IIntervalWindow * 3), float(IIntervalWindow));
				}
				else if (i == 1)
				{
					if (enemy.ReturnName()[0] == 0)//if player not loged in
						buf = "Пусто";
					else//else load kim name
						buf = enemy.ReturnName();

					tText.setPosition(WIDTH - 7 * IIntervalWindow, float(IIntervalWindow));
				}
				else if (i < 6)
				{
					if (i == 2 || i == 5)//if under names of player
						buf = "Вход / смена игрока";
					if (i == 3)//create new account
						buf = "Создать аккаунт";
					if (i == 4)//goto menu
						buf = "В меню";

					tText.setPosition(float(IIntervalWindow + (i - 2) * ISizeButton), FTextNavigation);
				}
				else if (i < 8)
				{
					if (i == 7)
					{
						buf = "<< Назад";
						tText.setPosition(float(2 * IIntervalWindow), FTextMove);
					}
					else
					{
						buf = "Вперёд>>";
						tText.setPosition(WIDTH - ISizeButton + 4 * IIntervalWindow, FTextMove);
					}
				}
				else //text about numeber of lists
				{
					buf = "страница ";
					_itoa_s(iCurrPage, num, 16, 10);//make current page to string
					buf += num;
					buf += " / ";
					_itoa_s(iMaxPage, num, 16, 10);//make max page to string
					buf += num;
					tText.setPosition(WIDTH/2 - 50, FTextMove);
				}

				tText.setString(buf);
				wSelect.draw(tText);
			}

			iMaxPage = CountPlayers() / 10 + 1;//Update

			for (auto i = std::size_t(0); i < ISizeLabel; i++)//draws label with list players
			{
				if (i == 0)//header
				{
					buf = "# Игрок:";
					tText.setString(buf);
					tText.setPosition(float(IIntervalWindow), FFistLabel - FIntervalLabel);
					wSelect.draw(tText);
					buf = "Побед";
					tText.setString(buf);
					tText.setPosition(FPosWin, FFistLabel - FIntervalLabel);
					wSelect.draw(tText);
					buf = "Поражений";
					tText.setString(buf);
					tText.setPosition(FPosLoses, FFistLabel - FIntervalLabel);
					wSelect.draw(tText);
					buf = "Ничьих";
					tText.setString(buf);
					tText.setPosition(FPosDraws, FFistLabel - FIntervalLabel);
					wSelect.draw(tText);
				}
				_itoa_s(i + 1 + (iCurrPage - 1) * 10, num, 16, 10);
				buf = num;
				buf += "\t";
				////
				if ((iCurrPage - 1) * 10 + int(i) < CountPlayers())//if players not end
				{
					buf += spp[i + (iCurrPage - 1) * 10].cName;
					tText.setString(buf);
					tText.setPosition(float(IIntervalWindow), FFistLabel + (i * FIntervalLabel));
					wSelect.draw(tText);
					_itoa_s(spp[i + (iCurrPage - 1) * 10].iWin, num, 16, 10);
					buf = num;
					tText.setString(buf);
					tText.setPosition(FPosWin, FFistLabel + (i * FIntervalLabel));
					wSelect.draw(tText);
					_itoa_s(spp[i + (iCurrPage - 1) * 10].iLose, num, 16, 10);
					buf = num;
					tText.setString(buf);
					tText.setPosition(FPosLoses, FFistLabel + (i * FIntervalLabel));
					wSelect.draw(tText);
					_itoa_s(spp[i + (iCurrPage - 1) * 10].iDraws, num, 16, 10);
					buf = num;
					tText.setString(buf);
					tText.setPosition(FPosDraws, FFistLabel + (i * FIntervalLabel));
					wSelect.draw(tText);
				}
			}
			iMousePos = sf::Mouse::getPosition(wSelect);//get position of mouse on display

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.y >= IIntervalWindow + FButtonNavigation &&
				iMousePos.y <= 3 * FButtonNavigation + IIntervalWindow)
			{
				if (iMousePos.x <= ISizeButton)
					LoadAccount(player, enemy, spp);//need to reload write
				else if (iMousePos.x <= 2 * ISizeButton)
					CreateAccount(spp);//create account
				else if (iMousePos.x <= 3 * ISizeButton)
					return 1;
				else//load account for enemy
					LoadAccount(enemy, player, spp);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.y >= FButtonMove &&
				iMousePos.y <= FButtonMove + 2 * FButtonNavigation)
			{
				if (iMousePos.x >= IIntervalWindow && iMousePos.x <= IIntervalWindow + ISizeButton
					&& iCurrPage > 1) //if pree prev
					iCurrPage--;
				if (iMousePos.x <= WIDTH - IIntervalWindow
					&& iMousePos.x >= WIDTH - IIntervalWindow - ISizeButton &&
					iCurrPage < iMaxPage)
					iCurrPage++;
			}

			wSelect.display();
			wSelect.clear();
		}
	}
	return -1;//if pressed x
}


int Help(void)
{
	const std::size_t size_text = 12;
	const float FPosFirst = IIntervalWindow;
	const float FInterval = 30.f;
	std::string sText[size_text] = //draws text
	{
		"Крестики-нолики это логическая игра между двумя противниками в поле 3х3.",
		"У одного из игроков - символ \"крестики\", у второго - \"нолики\"",
		"Правила игры: игроки по очереди ставят свой символ в пустую клетку, побеждает тот,",
		"кто сможет сделать линию из 3 своих символов, первее противника. Если до",
		"заполнения поля полностью никто не составил линию - то результат засчитываеться",
		"как \"Ничья\" для обоих игроков.",
		"Для игры игрок против игрока - нужно чтобы хотя бы первый игрок вошёл в свой  аккаунт",
		"через пункт меню \"Выбор игроков\".",
		"Для игры против ПК вход не объязателен, но игра уведомит вас о том что вы не вошли",
		"Аккаунт \"Guest\" - сбрасывает статистику при входе, а\"CPU\" - может использовать только ПК.",
		"При обнаружении ошибок писать на электронную почту igor.nebosenko@gmail.com",
		"Разработчик: Игорь Небосенко (с) 2017, использование в коммерческих целях запрещено!"
	};
	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button
	sButton.setPosition((WIDTH - ISizeButton) / 2, HEIGHT - 3 * IIntervalWindow);

	std::string sMenu("В меню");

	sf::Vector2i iMousePos;//gets position of mouse

	sf::RenderWindow wHelp(sf::VideoMode(WIDTH, HEIGHT), "Manual", sf::Style::Close);

	sf::Event eClose;//event for test pressed button "cross"

	while (wHelp.isOpen())//wile opened menu window
	{
		while (wHelp.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wHelp.close();//close this window

			for (auto i = std::size_t(0); i < size_text; i++)
			{
				tText.setString(sText[i]);
				tText.setPosition(float(IIntervalWindow), FPosFirst + i * FInterval);
				wHelp.draw(tText);
			}

			tText.setString(sMenu);
			tText.setPosition((WIDTH - ISizeButton) / 2 + 4 * IIntervalWindow,
				HEIGHT - 2 * IIntervalWindow);

			iMousePos = sf::Mouse::getPosition(wHelp);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x >= (WIDTH - ISizeButton) / 2 &&
				iMousePos.x <= (WIDTH - ISizeButton) / 2 + ISizeButton &&
				iMousePos.y >= HEIGHT - 3 * IIntervalWindow &&
				iMousePos.y <= HEIGHT - 3 * IIntervalWindow + 64)
				return 1;//go to menu

			wHelp.draw(sButton);
			wHelp.draw(tText);
			wHelp.display();
			wHelp.clear();
		}
	}
	return -1;
}


int DrawLog(void)
{
	const float FPosFirst = IIntervalWindow;
	const float FInterval = 30.f;
	std::size_t iSize = 0;
	char buf[300] = {0};
	std::string sBuf;


	FILE* f = nullptr;
	if (fopen_s(&f, "stat.log", "r"))
		throw std::runtime_error("Not found log file!");
	//count number of strings
	while (!feof(f))
	{
		fgets(buf, 300, f);
		iSize++;
	}
	fclose(f);

	std::string *str = new std::string[iSize];

	if (fopen_s(&f, "stat.log", "r"))
		throw std::runtime_error("Not found log file!");
	//count number of strings
	for (auto i = std::size_t(0); i < iSize; i++)
	{
		fgets(buf, 300, f);
		str[i] = buf;
	}
	fclose(f);

	int iCurrPage = 1;
	int iMaxPage = iSize / 10 + 1;


	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button
	sButton.setPosition((WIDTH - ISizeButton) / 2, HEIGHT - 3 * IIntervalWindow);

	std::string sMenu("В меню");

	sf::Vector2i iMousePos;//gets position of mouse

	sf::RenderWindow wLog(sf::VideoMode(WIDTH, HEIGHT), "Log", sf::Style::Close);

	sf::Event eClose;//event for test pressed button "cross"

	while (wLog.isOpen())//wile opened menu window
	{
		while (wLog.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wLog.close();//close this window

			sButton.setPosition(0, HEIGHT - 64);
			wLog.draw(sButton);
			sButton.setPosition(WIDTH / 2 - ISizeButton / 2, HEIGHT - 64);
			wLog.draw(sButton);
			sButton.setPosition(WIDTH - ISizeButton, HEIGHT - 64);
			wLog.draw(sButton);

			sBuf = "<<Назад";
			tText.setString(sBuf);
			tText.setPosition(1. * IIntervalWindow, HEIGHT - 40);
			wLog.draw(tText);
			sBuf = "В меню";
			tText.setString(sBuf);
			tText.setPosition(WIDTH / 2 - ISizeButton / 2 + 1. * IIntervalWindow, HEIGHT - 40);
			wLog.draw(tText);
			sBuf = "Вперёд>>";
			tText.setString(sBuf);
			tText.setPosition(WIDTH - ISizeButton + 1. * IIntervalWindow, HEIGHT - 40);
			wLog.draw(tText);

			const float FPosX = 30.f;
			const float FInterval = 35.f;
			for (auto i = std::size_t(0); i < std::size_t(10) && i < iSize - (iCurrPage - 1) * 10; i++)
			{
				tText.setString(str[i + (iCurrPage - 1) * 10]);
				tText.setPosition(IIntervalWindow * 2., FPosX + FInterval * i);
				wLog.draw(tText);
			}
			
			iMousePos = sf::Mouse::getPosition(wLog);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.y >= HEIGHT - 64 && iMousePos.y <= HEIGHT)
			{
				if (iMousePos.x >= 0 && iMousePos.x <= ISizeButton * 1.
					&& iCurrPage > 1)
					iCurrPage--;
				if (iMousePos.x >= WIDTH / 2 - ISizeButton / 2
					&& iMousePos.x <= WIDTH / 2 + ISizeButton / 2)
				{
					delete[] str;
					return 1;
				}
				if (iMousePos.x >= WIDTH - ISizeButton
					&& iMousePos.x <= WIDTH && iCurrPage < iMaxPage)
					iCurrPage++;
			}
			
			wLog.display();
			wLog.clear();
		}
	}
	delete[] str;
	return -1;
}


int CountPlayers(void)
{
	int iResult = 0;//inizilize size
	struct _finddata_t file;//make structure
	intptr_t hFile;

	if ((hFile = _findfirst("players\\*.spa", &file)) == -1L)
	{
		return 0;//if directory empty or not found
	}
	else
	{
		do
		{
			iResult++;
		} 
		while (_findnext(hFile, &file) == 0);//while can find new files
		_findclose(hFile);//close directory
	}
	return iResult;//return result
}


BaseAccount::Store* LabelOfPlayers(void)
{
	int iSize = CountPlayers();//size of array
	int iCount = 0;//counts nummer of struct
	BaseAccount::Store *p = new BaseAccount::Store[iSize];

	struct _finddata_t file;
	intptr_t hFile;

	if ((hFile = _findfirst("players\\*.spa", &file)) == -1L)
	{

	}
	else
	{
		
		do
		{
			FILE* f = nullptr;
			char str[IBuf] = "players\\";
			strcat_s(str, 256, file.name);
			if (!fopen_s(&f, str, "rb"))
			{
				fread(&p[iCount], sizeof(p[iCount]), 1, f);
				iCount++;
				fclose(f);
			}
			else
				throw std::exception("No access to directory with accounts");
		} 
		while (_findnext(hFile, &file) == 0);
		_findclose(hFile);
	}
	return p;
}

void WriteLog(std::string& str)
{
	FILE* f = nullptr;
	if (fopen_s(&f, "stat.log", "a"))//add
		throw std::runtime_error("Not found log file!");
	fputc('\n', f);
	fputs(str.c_str(), f);
	fclose(f);
}


void LoadAccount(Player& user, Player& second, BaseAccount::Store* list)
{
	char buf[128] = { 0 };
	std::cout << "Write name:" << std::endl;
	std::cin >> buf;
	if (!strcmp(buf, second.ReturnName()))
		std::cout << "There is account diffrent player!"<<std::endl;
	std::size_t size = CountPlayers();
	for (auto i = std::size_t(0); i < size; i++)
	{
		if (strcmp(buf, list[i].cName) == 0 && strcmp(buf, second.ReturnName()) != 0)//if found
		{
			Player tmp(buf, " ");
			tmp.LoadFile();
			std::cout << "Write password" << std::endl;
			std::cin >> buf;
			if (tmp.ComparePassword(buf))
				user = tmp;
			else
				std::cout << "Error of password!" << std::endl;
		}
	}
}


void CreateAccount(BaseAccount::Store* list)
{
	char buf[128] = { 0 };
	char cPas[128] = { 0 };
	std::cout << "Set name:" << std::endl;
	std::cin >> buf;
	std::size_t size = CountPlayers();
	bool bNew = true;
	for (auto i = std::size_t(0); i < size; i++)
	{
		if (!strcmp(list[i].cName, buf))//if player found
			bNew = false;
	}
	if (bNew)
	{
		std::cout << "Set password" << std::endl;
		std::cin >> cPas;
		Player tmp(buf, cPas);
		tmp.WriteFile();
	}
	else
	{
		std::cout << "A player with this name already created" << std::endl;
	}
}


int PvP(Player& player, Player& enemy)
{
	const std::size_t IArr = 9;
	const int ISizeT = 192;
	const float FPosPlayer = 600.f;
	const float FPosEnemy = 875.f;
	char* cGame = new char[IArr];

	bool bStep = true;//which symbol is now
	bool bPlayerFirst = true;//defines who move first
	player.LoadFile();
	enemy.LoadFile();

	if (!strcmp(player.sp.cLastEnemy, enemy.ReturnName()))//if save
	{
		player.LoadFile();
		enemy.LoadFile();
		if (player.sp.bFirst)//if 1st player move second in file
		{
			bPlayerFirst = false;
			bStep = false;
		}
		for (auto i = std::size_t(0); i < IArr; i++)
		{
			cGame[i] = player.ReturnArr()[i];
		}
	}
	else
	{
		memset(cGame, 'E', IArr);
	}
	int iStep = CountArr(cGame);//number of step

	std::string str;//string-buffer

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Vector2i iMousePos;//gets position of mouse

	sf::RenderWindow wPvP(sf::VideoMode(WIDTH, HEIGHT), "Tick-tack-toe", sf::Style::Close);
	//renders window of PvP

	sf::Event eClose;//event for test pressed button "cross"

	sf::Texture title;//tiles with xoe
	if(!title.loadFromFile("src/tileset.png"))//load tiles
		throw std::runtime_error("Not found texture tiles in \"src\" directory!");

	sf::Sprite Empty;//make empty sprite
	Empty.setTexture(title);
	Empty.setTextureRect(sf::IntRect(0, 0, ISizeT, ISizeT * 2));

	sf::Sprite X;//make sprite with X
	X.setTexture(title);
	X.setTextureRect(sf::IntRect(ISizeT * 2, 0, ISizeT, ISizeT));

	sf::Sprite O;//make sprite with 0
	O.setTexture(title);
	O.setTextureRect(sf::IntRect(ISizeT, 0, ISizeT, ISizeT));

	sf::Sprite sTitle;//for draw

	while (wPvP.isOpen())//wile opened menu window
	{
		while (wPvP.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wPvP.close();//close this window

			if (WinCell(cGame, !bStep))
			{
				Sleep(1200);
				memset(cGame, 'E', IArr);
			}
			else if (iStep == IArr)
			{
				memset(cGame, 'E', IArr);
				player.AddDraw();
				enemy.AddDraw();
				player.WriteFile();
				enemy.WriteFile();
				iStep = 0;

				std::string tmp(player.ReturnName());
				tmp += " vs ";
				tmp += enemy.ReturnName();
				tmp += ". Draw";
				WriteLog(tmp);

				Sleep(1200);
			}

			str = player.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosPlayer, float(IIntervalWindow));
			wPvP.draw(tText);
			str = enemy.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosEnemy, float(IIntervalWindow));
			wPvP.draw(tText);
			if (bStep)//bstep
				str = "Ходит первый игрок";
			else
				str = "Ходит второй игрок";
			tText.setString(str);
			tText.setPosition(FPosPlayer, 5. * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 6 * IIntervalWindow);//save
			wPvP.draw(sButton);

			str = "Сохранить игру";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 5 * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 3 * IIntervalWindow);
			wPvP.draw(sButton);

			str = "Выход";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 2 * IIntervalWindow);
			wPvP.draw(tText);

			iMousePos = sf::Mouse::getPosition(wPvP);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x <= 3 * 192 && iMousePos.y <= 3*192 &&
				EditCell(cGame, iMousePos, bStep))
			{
				iStep++;
				bStep = !bStep;
				Sleep(200);
			}

			for (auto i = std::size_t(0); i < IArr; i++)//draws cells
			{
				if (cGame[i] == 'E')
					sTitle = Empty;
				else if (cGame[i] == 'X')
					sTitle = X;
				else
					sTitle = O;

				sTitle.setPosition(float(i % 3 * ISizeT), float(i / 3 * ISizeT));
				wPvP.draw(sTitle);
			}

			if (WinCell(cGame, !bStep))//if someone win
			{
				//bStep is inverted!
				// 0 - player
				// 1 - enemy
				if (!bStep)//if win player 1
				{
					player.AddWin();
					enemy.AddLose();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += player.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "1 игрок выигрывает раунд!";
				}
				else
				{
					player.AddLose();
					enemy.AddWin();

					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += enemy.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "2 игрок выигрывает раунд!";
				}
				player.WriteFile();
				enemy.WriteFile();
				tText.setString(str);
				tText.setPosition(FPosPlayer, 9. *IIntervalWindow);
				wPvP.draw(tText);
				iStep = 0;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x >= FPosPlayer && iMousePos.x <= FPosPlayer + ISizeButton)
				//if in interval buttons winth save & quit
			{
				if (iMousePos.y >= HEIGHT - 5 * IIntervalWindow &&
					iMousePos.y <= HEIGHT - 5 * IIntervalWindow + 64)
					//if pressed save;
				{
					strcpy_s(player.sp.cLastEnemy, 128, enemy.ReturnName());
					strcpy_s(enemy.sp.cLastEnemy, 128, player.ReturnName());
					player.WriteArr(cGame);
					enemy.WriteArr(cGame);
					player.sp.bCross = true;
					enemy.sp.bCross = false;
					player.sp.bFirst = !bPlayerFirst;
					enemy.sp.bFirst = bPlayerFirst;
					if (!bStep)
					{
						player.sp.bFirst = true;
						enemy.sp.bFirst = false;
					}
					else
					{
						player.sp.bFirst = false;
						enemy.sp.bFirst = true;
					}
					player.WriteFile();
					enemy.WriteFile();
				}
					if (iMousePos.y >= HEIGHT - 3 * IIntervalWindow &&
						iMousePos.y <= HEIGHT - 3 * IIntervalWindow + 64)
					{
						delete[] cGame;
						exit(0);
					}
			}

			wPvP.display();
			wPvP.clear();
		}

		//
	}
	delete[] cGame;
	return -1;
}

int PvP(Player& player, BaseAccount& enemy)
{
	const std::size_t IArr = 9;
	const int ISizeT = 192;
	const float FPosPlayer = 600.f;
	const float FPosEnemy = 875.f;
	char* cGame = new char[IArr];

	bool bStep = true;//which symbol is now
	bool bPlayerFirst = true;//defines who move first
	player.LoadFile();
	enemy.LoadFile();

	if (!strcmp(player.sp.cLastEnemy, enemy.ReturnName()))//if save
	{
		player.LoadFile();
		enemy.LoadFile();
		if (player.sp.bFirst)//if 1st player move second in file
		{
			bPlayerFirst = false;
			bStep = false;
		}
		for (auto i = std::size_t(0); i < IArr; i++)
		{
			cGame[i] = player.ReturnArr()[i];
		}
	}
	else
	{
		memset(cGame, 'E', IArr);
	}
	int iStep = CountArr(cGame);//number of step

	std::string str;//string-buffer

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Vector2i iMousePos;//gets position of mouse

	sf::RenderWindow wPvP(sf::VideoMode(WIDTH, HEIGHT), "Tick-tack-toe", sf::Style::Close);
	//renders window of PvP

	sf::Event eClose;//event for test pressed button "cross"

	sf::Texture title;//tiles with xoe
	if (!title.loadFromFile("src/tileset.png"))//load tiles
		throw std::runtime_error("Not found texture tiles in \"src\" directory!");

	sf::Sprite Empty;//make empty sprite
	Empty.setTexture(title);
	Empty.setTextureRect(sf::IntRect(0, 0, ISizeT, ISizeT * 2));

	sf::Sprite X;//make sprite with X
	X.setTexture(title);
	X.setTextureRect(sf::IntRect(ISizeT * 2, 0, ISizeT, ISizeT));

	sf::Sprite O;//make sprite with 0
	O.setTexture(title);
	O.setTextureRect(sf::IntRect(ISizeT, 0, ISizeT, ISizeT));

	sf::Sprite sTitle;//for draw

	while (wPvP.isOpen())//wile opened menu window
	{
		while (wPvP.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wPvP.close();//close this window

			if (WinCell(cGame, !bStep))
			{
				Sleep(1200);
				memset(cGame, 'E', IArr);
			}
			else if (iStep == IArr)
			{
				memset(cGame, 'E', IArr);
				player.AddDraw();
				enemy.AddDraw();
				player.WriteFile();
				enemy.WriteFile();
				iStep = 0;

				std::string tmp(player.ReturnName());
				tmp += " vs ";
				tmp += enemy.ReturnName();
				tmp += ". Draw";
				WriteLog(tmp);

				Sleep(1200);
			}

			str = player.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosPlayer, float(IIntervalWindow));
			wPvP.draw(tText);
			str = enemy.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosEnemy, float(IIntervalWindow));
			wPvP.draw(tText);
			if (bStep)//bstep
				str = "Ходит первый игрок";
			else
				str = "Ходит второй игрок";
			tText.setString(str);
			tText.setPosition(FPosPlayer, 5. * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 6 * IIntervalWindow);//save
			wPvP.draw(sButton);

			str = "Сохранить игру";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 5 * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 3 * IIntervalWindow);
			wPvP.draw(sButton);

			str = "Выход";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 2 * IIntervalWindow);
			wPvP.draw(tText);

			iMousePos = sf::Mouse::getPosition(wPvP);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x <= 3 * 192 && iMousePos.y <= 3 * 192 &&
				EditCell(cGame, iMousePos, bStep))
			{
				iStep++;
				bStep = !bStep;
				Sleep(200);
			}

			for (auto i = std::size_t(0); i < IArr; i++)//draws cells
			{
				if (cGame[i] == 'E')
					sTitle = Empty;
				else if (cGame[i] == 'X')
					sTitle = X;
				else
					sTitle = O;

				sTitle.setPosition(float(i % 3 * ISizeT), float(i / 3 * ISizeT));
				wPvP.draw(sTitle);
			}

			if (WinCell(cGame, !bStep))//if someone win
			{
				//bStep is inverted!
				// 0 - player
				// 1 - enemy
				if (!bStep)//if win player 1
				{
					player.AddWin();
					enemy.AddLose();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += player.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "1 игрок выигрывает раунд!";
				}
				else
				{
					player.AddLose();
					enemy.AddWin();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += enemy.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "2 игрок выигрывает раунд!";
				}
				player.WriteFile();
				enemy.WriteFile();
				tText.setString(str);
				tText.setPosition(FPosPlayer, 9. *IIntervalWindow);
				wPvP.draw(tText);
				iStep = 0;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x >= FPosPlayer && iMousePos.x <= FPosPlayer + ISizeButton)
				//if in interval buttons winth save & quit
			{
				if (iMousePos.y >= HEIGHT - 5 * IIntervalWindow &&
					iMousePos.y <= HEIGHT - 5 * IIntervalWindow + 64)
					//if pressed save;
				{
					strcpy_s(player.sp.cLastEnemy, 128, enemy.ReturnName());
					player.WriteArr(cGame);
					player.sp.bCross = true;
					player.sp.bFirst = !bPlayerFirst;
					if (!bStep)
					{
						player.sp.bFirst = true;
					}
					else
					{
						player.sp.bFirst = false;
					}
					player.WriteFile();
					enemy.WriteFile();
				}
				if (iMousePos.y >= HEIGHT - 3 * IIntervalWindow &&
					iMousePos.y <= HEIGHT - 3 * IIntervalWindow + 64)
				{
					delete[] cGame;
					exit(0);
				}
			}

			wPvP.display();
			wPvP.clear();
		}

		//
	}
	delete[] cGame;
	return -1;
}

int PvCPU(Player& player, BaseAccount& enemy)
{
	bool bDifficult = SelectDifficult();
	Sleep(200);
	const std::size_t IArr = 9;
	const int ISizeT = 192;
	const float FPosPlayer = 600.f;
	const float FPosEnemy = 875.f;
	char* cGame = new char[IArr];

	bool bStep = true;//which symbol is now
	bool bPlayerFirst = true;//defines who move first
	player.LoadFile();
	enemy.LoadFile();

	if (!strcmp(player.sp.cLastEnemy, enemy.ReturnName()))//if save
	{
		player.LoadFile();
		enemy.LoadFile();
		if (player.sp.bFirst)//if 1st player move second in file
		{
			bPlayerFirst = false;
			bStep = false;
		}
		for (auto i = std::size_t(0); i < IArr; i++)
		{
			cGame[i] = player.ReturnArr()[i];
		}
	}
	else
	{
		memset(cGame, 'E', IArr);
	}
	int iStep = CountArr(cGame);//number of step

	std::string str;//string-buffer

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Vector2i iMousePos;//gets position of mouse

	sf::RenderWindow wPvP(sf::VideoMode(WIDTH, HEIGHT), "Tick-tack-toe", sf::Style::Close);
	//renders window of PvP

	sf::Event eClose;//event for test pressed button "cross"

	sf::Texture title;//tiles with xoe
	if (!title.loadFromFile("src/tileset.png"))//load tiles
		throw std::runtime_error("Not found texture tiles in \"src\" directory!");

	sf::Sprite Empty;//make empty sprite
	Empty.setTexture(title);
	Empty.setTextureRect(sf::IntRect(0, 0, ISizeT, ISizeT * 2));

	sf::Sprite X;//make sprite with X
	X.setTexture(title);
	X.setTextureRect(sf::IntRect(ISizeT * 2, 0, ISizeT, ISizeT));

	sf::Sprite O;//make sprite with 0
	O.setTexture(title);
	O.setTextureRect(sf::IntRect(ISizeT, 0, ISizeT, ISizeT));

	sf::Sprite sTitle;//for draw

	while (wPvP.isOpen())//wile opened menu window
	{
		while (wPvP.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wPvP.close();//close this window

			if (WinCell(cGame, !bStep))
			{
				Sleep(1200);
				memset(cGame, 'E', IArr);
			}
			else if (iStep == IArr)
			{
				memset(cGame, 'E', IArr);
				player.AddDraw();
				enemy.AddDraw();
				player.WriteFile();
				enemy.WriteFile();
				iStep = 0;

				std::string tmp(player.ReturnName());
				tmp += " vs ";
				tmp += enemy.ReturnName();
				tmp += ". Draw";
				WriteLog(tmp);

				Sleep(1200);
			}

			str = player.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosPlayer, float(IIntervalWindow));
			wPvP.draw(tText);
			str = enemy.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosEnemy, float(IIntervalWindow));
			wPvP.draw(tText);
			if (bStep)//bstep
				str = "Ходит первый игрок";
			else
				str = "Ходит второй игрок";
			tText.setString(str);
			tText.setPosition(FPosPlayer, 5. * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 6 * IIntervalWindow);//save
			wPvP.draw(sButton);

			str = "Сохранить игру";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 5 * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 3 * IIntervalWindow);
			wPvP.draw(sButton);

			str = "Выход";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 2 * IIntervalWindow);
			wPvP.draw(tText);

			iMousePos = sf::Mouse::getPosition(wPvP);
			if (bStep && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x <= 3 * 192 && iMousePos.y <= 3 * 192 &&
				EditCell(cGame, iMousePos, bStep))
			{
				iStep++;
				bStep = !bStep;
				Sleep(200);
			}
			else if (!bStep)
			{
				LogicCPU(cGame, bDifficult, bStep);
				bStep = !bStep;
				iStep++;
			}

			for (auto i = std::size_t(0); i < IArr; i++)//draws cells
			{
				if (cGame[i] == 'E')
					sTitle = Empty;
				else if (cGame[i] == 'X')
					sTitle = X;
				else
					sTitle = O;

				sTitle.setPosition(float(i % 3 * ISizeT), float(i / 3 * ISizeT));
				wPvP.draw(sTitle);
			}

			if (WinCell(cGame, !bStep))//if someone win
			{
				//bStep is inverted!
				// 0 - player
				// 1 - enemy
				if (!bStep)//if win player 1
				{
					player.AddWin();
					enemy.AddLose();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += player.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "1 игрок выигрывает раунд!";
				}
				else
				{
					player.AddLose();
					enemy.AddWin();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += enemy.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "2 игрок выигрывает раунд!";
				}
				player.WriteFile();
				enemy.WriteFile();
				tText.setString(str);
				tText.setPosition(FPosPlayer, 9. *IIntervalWindow);
				wPvP.draw(tText);
				iStep = 0;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x >= FPosPlayer && iMousePos.x <= FPosPlayer + ISizeButton)
				//if in interval buttons winth save & quit
			{
				if (iMousePos.y >= HEIGHT - 5 * IIntervalWindow &&
					iMousePos.y <= HEIGHT - 5 * IIntervalWindow + 64)
					//if pressed save;
				{
					strcpy_s(player.sp.cLastEnemy, 128, enemy.ReturnName());
					player.WriteArr(cGame);
					player.sp.bCross = true;
					player.sp.bFirst = !bPlayerFirst;
					if (!bStep)
					{
						player.sp.bFirst = true;
					}
					else
					{
						player.sp.bFirst = false;
					}
					player.WriteFile();
					enemy.WriteFile();
				}
				if (iMousePos.y >= HEIGHT - 3 * IIntervalWindow &&
					iMousePos.y <= HEIGHT - 3 * IIntervalWindow + 64)
				{
					delete[] cGame;
					exit(0);
				}
			}

			wPvP.display();
			wPvP.clear();
		}

		//
	}
	delete[] cGame;
	return -1;
}


int PvCPU(BaseAccount& player, BaseAccount& enemy)
{
	bool bDifficult = SelectDifficult();
	Sleep(200);
	const std::size_t IArr = 9;
	const int ISizeT = 192;
	const float FPosPlayer = 600.f;
	const float FPosEnemy = 875.f;
	char* cGame = new char[IArr];

	bool bStep = true;//which symbol is now
	bool bPlayerFirst = true;//defines who move first
	player.LoadFile();
	enemy.LoadFile();

	//there is no any saves and loads
	memset(cGame, 'E', IArr);
	int iStep = CountArr(cGame);//number of step

	std::string str;//string-buffer

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Vector2i iMousePos;//gets position of mouse

	sf::RenderWindow wPvP(sf::VideoMode(WIDTH, HEIGHT), "Tick-tack-toe", sf::Style::Close);
	//renders window of PvP

	sf::Event eClose;//event for test pressed button "cross"

	sf::Texture title;//tiles with xoe
	if (!title.loadFromFile("src/tileset.png"))//load tiles
		throw std::runtime_error("Not found texture tiles in \"src\" directory!");

	sf::Sprite Empty;//make empty sprite
	Empty.setTexture(title);
	Empty.setTextureRect(sf::IntRect(0, 0, ISizeT, ISizeT * 2));

	sf::Sprite X;//make sprite with X
	X.setTexture(title);
	X.setTextureRect(sf::IntRect(ISizeT * 2, 0, ISizeT, ISizeT));

	sf::Sprite O;//make sprite with 0
	O.setTexture(title);
	O.setTextureRect(sf::IntRect(ISizeT, 0, ISizeT, ISizeT));

	sf::Sprite sTitle;//for draw

	while (wPvP.isOpen())//wile opened menu window
	{
		while (wPvP.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wPvP.close();//close this window

			if (WinCell(cGame, !bStep))
			{
				Sleep(1200);
				memset(cGame, 'E', IArr);
			}
			else if (iStep == IArr)
			{
				memset(cGame, 'E', IArr);
				player.AddDraw();
				enemy.AddDraw();
				player.WriteFile();
				enemy.WriteFile();
				iStep = 0;

				std::string tmp(player.ReturnName());
				tmp += " vs ";
				tmp += enemy.ReturnName();
				tmp += ". Draw";
				WriteLog(tmp);

				Sleep(1200);
			}

			str = player.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosPlayer, float(IIntervalWindow));
			wPvP.draw(tText);
			str = enemy.ReturnName();
			tText.setString(str);
			tText.setPosition(FPosEnemy, float(IIntervalWindow));
			wPvP.draw(tText);
			if (bStep)//bstep
				str = "Ходит первый игрок";
			else
				str = "Ходит второй игрок";
			tText.setString(str);
			tText.setPosition(FPosPlayer, 5. * IIntervalWindow);
			wPvP.draw(tText);

			sButton.setPosition(FPosPlayer, HEIGHT - 3 * IIntervalWindow);//save
			wPvP.draw(sButton);

			str = "Выход";
			tText.setString(str);
			tText.setPosition(FPosPlayer + IIntervalWindow, HEIGHT - 2 * IIntervalWindow);
			wPvP.draw(tText);

			iMousePos = sf::Mouse::getPosition(wPvP);
			if (bStep && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x <= 3 * 192 && iMousePos.y <= 3 * 192 &&
				EditCell(cGame, iMousePos, bStep))
			{
				iStep++;
				bStep = !bStep;
				Sleep(200);
			}
			else if (!bStep)
			{
				LogicCPU(cGame, bDifficult, bStep);
				bStep = !bStep;
				iStep++;
			}

			for (auto i = std::size_t(0); i < IArr; i++)//draws cells
			{
				if (cGame[i] == 'E')
					sTitle = Empty;
				else if (cGame[i] == 'X')
					sTitle = X;
				else
					sTitle = O;

				sTitle.setPosition(float(i % 3 * ISizeT), float(i / 3 * ISizeT));
				wPvP.draw(sTitle);
			}

			if (WinCell(cGame, !bStep))//if someone win
			{
				//bStep is inverted!
				// 0 - player
				// 1 - enemy
				if (!bStep)//if win player 1
				{
					player.AddWin();
					enemy.AddLose();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += player.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "1 игрок выигрывает раунд!";
				}
				else
				{
					player.AddLose();
					enemy.AddWin();
					std::string tmp(player.ReturnName());
					tmp += " vs ";
					tmp += enemy.ReturnName();
					tmp += ". ";
					tmp += enemy.ReturnName();
					tmp += " win";
					WriteLog(tmp);
					str = "2 игрок выигрывает раунд!";
				}
				player.WriteFile();
				enemy.WriteFile();
				tText.setString(str);
				tText.setPosition(FPosPlayer, 9. *IIntervalWindow);
				wPvP.draw(tText);
				iStep = 0;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.x >= FPosPlayer && iMousePos.x <= FPosPlayer + ISizeButton)
				//if in interval buttons winth save & quit
			{
				if (iMousePos.y >= HEIGHT - 3 * IIntervalWindow &&
					iMousePos.y <= HEIGHT - 3 * IIntervalWindow + 64)
				{
					delete[] cGame;
					exit(0);
				}
			}

			wPvP.display();
			wPvP.clear();
		}

		//
	}
	delete[] cGame;
	return -1;
}



bool EditCell(char* cArray, sf::Vector2i& iMousePos, bool bStep)
{
	int iIndex = int(iMousePos.x / 192) + 3 * int(iMousePos.y / 192);
	if (cArray[iIndex] == 'E')
	{
		if (bStep)
			cArray[iIndex] = 'X';
		else
			cArray[iIndex] = 'O';
		return true;//if can edit
	}
	return false;
}
bool WinCell(char* cArray, bool bStep)
{
	char ch = 0;
	if (bStep)
		ch = 'X';
	else
		ch = 'O';
	if (cArray[0] == ch && cArray[1] == ch && cArray[2] == ch)
		return true;
	if (cArray[3] == ch && cArray[4] == ch && cArray[5] == ch)
		return true;
	if (cArray[6] == ch && cArray[7] == ch && cArray[8] == ch)
		return true;
	if (cArray[0] == ch && cArray[3] == ch && cArray[6] == ch)
		return true;
	if (cArray[1] == ch && cArray[4] == ch && cArray[7] == ch)
		return true;
	if (cArray[2] == ch && cArray[5] == ch && cArray[8] == ch)
		return true;
	if (cArray[0] == ch && cArray[4] == ch &&cArray[8] == ch)
		return true;
	if (cArray[2] == ch && cArray[4] == ch && cArray[6] == ch)
		return true;
	return false;
}


int CountArr(char* cArray)
{
	int res = 0;
	for (int i = 0; i < 9; i++)
	{
		if (cArray[i] == 'E')
			res++;
	}
	return 9 - res;
}


bool SelectDifficult(void)
{
	const int IHeight = 200;
	const int IWidth = 512;
	const float FPosY = 128.f;

	std::string str;

	sf::Vector2i iMousePos;//gets position of mouse

	sf::Font fText;//Makes font for text. My font has rissian leters, and i used them
	if (!fText.loadFromFile("src\\CyrilicOld.TTF"))//try load font
		throw std::runtime_error("Not found font in \"src\" directory!");
	//if font not load - throw exception

	sf::Texture tButton;//Texture of button
	if (!tButton.loadFromFile("src/button.png"))
		throw std::runtime_error("Not found texture button in \"src\" directory!");
	//if font not load - throw exception

	sf::Sprite sButton;//Sprite of button
	sButton.setTexture(tButton);//load texture for sprite button

	sf::Text tText;//label with text
	tText.setFont(fText);//sets font frome file CyrilicOld.TTF
	tText.setScale(FSizeText, FSizeText);//set scale 25x25 px

	sf::RenderWindow wDifficult(sf::VideoMode(IWidth, IHeight), "Select Difficult", sf::Style::Close);
	//makes window message

	sf::Event eClose;//event for test pressed button "cross"


	std::string sBuf[2] = { "В меню", "Продолжить" };
	while (wDifficult.isOpen())//wile opened menu window
	{
		while (wDifficult.pollEvent(eClose))//while not pressed close button
		{
			if (eClose.type == sf::Event::Closed)//if pressed x in right top angle
				wDifficult.close();//close this window
			sButton.setPosition(0, FPosY);
			wDifficult.draw(sButton);
			sButton.setPosition(ISizeButton * 1., FPosY);
			wDifficult.draw(sButton);

			str = "Выберите сложность:";
			tText.setString(str);
			tText.setPosition(5. * IIntervalWindow, FPosY / 2);
			wDifficult.draw(tText);

			str = "Салага";
			tText.setString(str);
			tText.setPosition(3. * IIntervalWindow, FPosY + IIntervalWindow * 0.5f);
			wDifficult.draw(tText);

			str = "Ветеран";
			tText.setString(str);
			tText.setPosition(3. * IIntervalWindow + ISizeButton, FPosY + IIntervalWindow * 0.5f);
			wDifficult.draw(tText);

			iMousePos = sf::Mouse::getPosition(wDifficult);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				iMousePos.y >= FPosY && iMousePos.y <= 1.5f * FPosY)
			{
				if (iMousePos.x < ISizeButton)
					return false;//return easy
				else
					return true;//return hard
			}

			wDifficult.display();
			wDifficult.clear();
		}
	}
	return 0;
}


void LogicCPU(char* cGame, bool bDifficult, bool bStep)
{
	srand(std::size_t(time(0)));
	Sleep(200);
	char ch = 0;
	char ech = 0;//enemy char
	if (bStep)//if X
	{
		ch = 'X';
		ech = 'O';
	}
	else
	{
		ch = 'O';
		ech = 'X';
	}
	int i = 0;

	if (bDifficult)
	{
		//if CPU set 2 symbols in line
		//line 1,1 - 1,3
		if (cGame[0] == ch && cGame[1] == ch && cGame[2] == 'E')
			//if in 0,0 and 0,1 and 0,2 - empty
			cGame[2] = ch;
		else if (cGame[0] == ch && cGame[2] == ch && cGame[1] == 'E')
			cGame[1] = ch;
		else if (cGame[1] == ch && cGame[2] == ch && cGame[0] == 'E')
			cGame[0] = ch;

		//line 2,1 - 2,3
		else if (cGame[3] == ch && cGame[4] == ch && cGame[5] == 'E')
			cGame[5] = ch;
		else if (cGame[3] == ch && cGame[5] == ch && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ch && cGame[5] == ch && cGame[3] == 'E')
			cGame[3] = ch;

		//line 3,1 - 3,3
		else if (cGame[6] == ch && cGame[7] == ch && cGame[8] == 'E')
			cGame[8] = ch;
		else if (cGame[6] == ch && cGame[8] == ch && cGame[7] == 'E')
			cGame[7] = ch;
		else if (cGame[7] == ch && cGame[8] == ch && cGame[6] == 'E')
			cGame[6] = ch;

		//line 1,1 - 3,1
		else if (cGame[0] == ch && cGame[3] == ch && cGame[6] == 'E')
			cGame[6] = ch;
		else if (cGame[0] == ch && cGame[6] == ch && cGame[3] == 'E')
			cGame[3] = ch;
		else if (cGame[3] == ch && cGame[6] == ch && cGame[0] == 'E')
			cGame[0] = ch;

		//line 2,1 - 2,3
		else if (cGame[1] == ch && cGame[4] == ch && cGame[7] == 'E')
			cGame[7] = ch;
		else if (cGame[1] == ch && cGame[7] == ch && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ch && cGame[7] == ch && cGame[1] == 'E')
			cGame[1] = ch;

		//line 3,1 - 3,3
		else if (cGame[2] == ch && cGame[5] == ch && cGame[8] == 'E')
			cGame[8] = ch;
		else if (cGame[2] == ch && cGame[8] == ch && cGame[5] == 'E')
			cGame[5] = ch;
		else if (cGame[5] == ch && cGame[8] == ch && cGame[2] == 'E')
			cGame[2] = ch;

		//diagonal 0,4,8
		else if (cGame[0] == ch && cGame[4] == ch && cGame[8] == 'E')
			cGame[8] = ch;
		else if (cGame[0] == ch && cGame[8] == ch && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ch && cGame[8] == ch && cGame[0] == 'E')
			cGame[0] = ch;

		//diagonal 2,4,6
		else if (cGame[2] == ch && cGame[4] == ch && cGame[6] == 'E')
			cGame[6] = ch;
		else if (cGame[2] == ch && cGame[6] == ch && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ch && cGame[6] == ch && cGame[2] == 'E')
			cGame[2] = ch;

		//if CPU can't win at current step - need test can Player win now, and lock him cell

		else if (cGame[0] == ech && cGame[1] == ech && cGame[2] == 'E')
			//if in 0,0 and 0,1 and 0,2 - empty
			cGame[2] = ch;
		else if (cGame[0] == ech && cGame[2] == ech && cGame[1] == 'E')
			cGame[1] = ch;
		else if (cGame[1] == ech && cGame[2] == ech && cGame[0] == 'E')
			cGame[0] = ch;

		//line 2,1 - 2,3
		else if (cGame[3] == ech && cGame[4] == ech && cGame[5] == 'E')
			cGame[5] = ch;
		else if (cGame[3] == ech && cGame[5] == ech && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ech && cGame[5] == ech && cGame[3] == 'E')
			cGame[3] = ch;

		//line 3,1 - 3,3
		else if (cGame[6] == ech && cGame[7] == ech && cGame[8] == 'E')
			cGame[8] = ch;
		else if (cGame[6] == ech && cGame[8] == ech && cGame[7] == 'E')
			cGame[7] = ch;
		else if (cGame[7] == ech && cGame[8] == ech && cGame[6] == 'E')
			cGame[6] = ch;

		//line 1,1 - 3,1
		else if (cGame[0] == ech && cGame[3] == ech && cGame[6] == 'E')
			cGame[6] = ch;
		else if (cGame[0] == ech && cGame[6] == ech && cGame[3] == 'E')
			cGame[3] = ch;
		else if (cGame[3] == ech && cGame[6] == ech && cGame[0] == 'E')
			cGame[0] = ch;

		//line 2,1 - 2,3
		else if (cGame[1] == ech && cGame[4] == ech && cGame[7] == 'E')
			cGame[7] = ch;
		else if (cGame[1] == ech && cGame[7] == ech && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ech && cGame[7] == ech && cGame[1] == 'E')
			cGame[1] = ch;

		//line 3,1 - 3,3
		else if (cGame[2] == ech && cGame[5] == ech && cGame[8] == 'E')
			cGame[8] = ch;
		else if (cGame[2] == ech && cGame[8] == ech && cGame[5] == 'E')
			cGame[5] = ch;
		else if (cGame[5] == ech && cGame[8] == ech && cGame[2] == 'E')
			cGame[2] = ch;

		//diagonal 0,4,8
		else if (cGame[0] == ech && cGame[4] == ech && cGame[8] == 'E')
			cGame[8] = ch;
		else if (cGame[0] == ech && cGame[8] == ech && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ech && cGame[8] == ech && cGame[0] == 'E')
			cGame[0] = ch;

		//diagonal 2,4,6
		else if (cGame[2] == ech && cGame[4] == ech && cGame[6] == 'E')
			cGame[6] = ch;
		else if (cGame[2] == ech && cGame[6] == ech && cGame[4] == 'E')
			cGame[4] = ch;
		else if (cGame[4] == ech && cGame[6] == ech && cGame[2] == 'E')
			cGame[2] = ch;

		else//if noobody win - random add
		{
			bool edit = false;
			while (!edit && CountArr(cGame) != 9)
			{
				int iPos = rand() % 9;
				if (cGame[iPos] == 'E')
				{
					if (bStep)//if X
						cGame[iPos] = ch;
					else
						cGame[iPos] = ch;
					edit = !edit;
				}
			}
		}
	}
	else
	{
		bool edit = false;
		while (!edit && CountArr(cGame)!= 9)
		{
			int iPos = rand() % 9;
			if (cGame[iPos] == 'E')
			{
				if (bStep)//if X
					cGame[iPos] = ch;
				else
					cGame[iPos] = ch;
				edit = !edit;
			}
		}

	}
}