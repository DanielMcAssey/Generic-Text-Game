#include "main.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Game* localGame = new Game();

	//Console Init
	localGame->mHelper->setWindowTitle(L"Text Game - Adventures"); //Sets title of console.
	localGame->mHelper->resizeWindow(106, 42); //Resize the console window, height and width.
	localGame->mHelper->maximizeWindow(); //Maximizes window to new size.

	while(true)
	{
		system("cls"); //Clears Console screen, every time it goes through the loop.
		switch(localGame->mode)
		{
		case 0: //Mode: Menu
			localGame->DrawMenu(); //Draws Menu
			break;
		case 1: //Mode: Game
			localGame->DrawGame(); //Draws Game
			break;
		case 2: //Mode: Credits
			localGame->DrawCredits(); //Draws Credits
			break;
		case 3: //Mode: Exit
			return 0; //Returns 0 and exits the console application.
			break;
		default:
			localGame->DrawMenu(); //Draws Menu
		}
	}

	return 0;
}