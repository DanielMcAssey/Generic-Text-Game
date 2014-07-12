#include "main.h"
#include "helper.h"

Helper::Helper(void)
{
	srand((unsigned)time(0)); //Sets random seed for randomizing.
}

Helper::~Helper(void)
{
}

void Helper::setWindowTitle(LPCTSTR windowTitle)
{
	SetConsoleTitle(windowTitle); //Sets console window title.
}

void Helper::resizeWindow(unsigned int x, unsigned int y)
{
	HANDLE hOut; //Creates a new console handle.
	COORD consoleCoOrdinates; //Creates a new co-ordinate system.
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer; //Creates console screen buffer;
	SMALL_RECT consoleArea = {0, 0, 0, 0}; //New area for console.

	hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Sets current console handle to the new handle.
	GetConsoleScreenBufferInfo(hOut, &consoleBuffer); //Gets screen buffer info.

	consoleArea.Right  = x; //Sets co-ord to new position. X co-ord.
	consoleArea.Bottom = y; //Sets co-ord to new position. Y co-ord.

	SetConsoleWindowInfo(hOut, TRUE, &consoleArea); //Sets all the new console window information.

	consoleCoOrdinates.X = x; //Assigns X as a new co-ord.
	consoleCoOrdinates.Y = y; //Assigns Y as a new co-ord.
	SetConsoleScreenBufferSize(hOut, consoleCoOrdinates); //Sets new Console Screen buffer info.
}

void Helper::maximizeWindow()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer; //Stores Console screen buffer info.
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer); //Gets screen buffer info
	SMALL_RECT consoleArea; //New area for console.
	consoleArea.Left = consoleArea.Top = 0; //Sets console area left, with top which is set to 0.
	consoleArea.Right = (short)(min(consoleBuffer.dwMaximumWindowSize.X, consoleBuffer.dwSize.X) - 1); //Sets right of console area, to what the maximum size is.
	consoleArea.Bottom = (short)(min(consoleBuffer.dwMaximumWindowSize.Y, consoleBuffer.dwSize.Y) - 1); //Sets bottom of console area, to what the maximum size is.
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &consoleArea); //Sets all the new console window information.
}

int Helper::generateRandInt(int low, int high)
{
	if(high > low)
	{
		return rand() % high + low; //Creates a random number, between 2 ints
	}
	else
	{
		return -1;
	}
}

string Helper::toLower(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::tolower); //Makes all text lowercase.

	return text;
}