#include "main.h"
#include "command.h"

Command::Command(Game *_game)
{
	this->mGame = _game;
	isBackEnabled = false;
	lastCommand = "";
	lastMessage = "";
}

Command::~Command(void)
{
}

int Command::SendCommand(string _command)
{
	int status = 0; //Sets status of command. 1 = Turn should be used up. 2 = No Turn should be used.

	_command = this->mGame->mHelper->toLower(_command); //Makes all commands passed lowercase.

	if ((this->mGame->monstersAlive == 0 || this->mGame->curTurn >= this->mGame->maxTurn) && _command != "menu")
		return 2; //Returns an error if in endgame mode.

	if(isBackEnabled == false) //Checks if the back command is enabled.
	{
		lastCommand = _command; //Stores last command.
		lastMessage = this->mGame->mPlayer->statusMessage; //Stores last message.
	}

	if (_command == "back" || _command == "b" || _command == "map" || _command == "m" || _command == "help" || _command == "h" || _command == "monsters") //Checks if its not a main command.
		isBackEnabled = true; //Allows the "back" command to be used.

	if (_command == "w" || _command == "up") //Detects command sent, see if it exists, if it does it executes, if not error.
	{
		status = this->mGame->mPlayer->movePlayerUp(); //Sets status, so if player moved, it uses up a turn.

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further up.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step up.";
			this->mGame->mPlayer->posY -= 1;
			break;
		case 2: //Monster killed.
			status = 1;
			this->mGame->mPlayer->statusMessage = "You moved 1 step up, and killed a monster!";
			this->mGame->mPlayer->posY -= 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "a" || _command == "left")
	{
		status = this->mGame->mPlayer->movePlayerLeft();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further left.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step left.";
			this->mGame->mPlayer->posX -= 1;
			break;
		case 2: //Monster killed.
			status = 1;
			this->mGame->mPlayer->statusMessage = "You moved 1 step left, and killed a monster!";
			this->mGame->mPlayer->posX -= 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "d" || _command == "right")
	{
		status = this->mGame->mPlayer->movePlayerRight();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further right.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step right.";
			this->mGame->mPlayer->posX += 1;
			break;
		case 2: //Monster killed.
			status = 1;
			this->mGame->mPlayer->statusMessage = "You moved 1 step right, and killed a monster!";
			this->mGame->mPlayer->posX += 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "s" || _command == "down")
	{
		status = this->mGame->mPlayer->movePlayerDown();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further down.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step down.";
			this->mGame->mPlayer->posY += 1;
			break;
		case 2: //Monster killed.
			status = 1;
			this->mGame->mPlayer->statusMessage = "You moved 1 step down, and killed a monster!";
			this->mGame->mPlayer->posY += 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "q")
	{
		status = this->mGame->mPlayer->movePlayerUpLeft();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further diagonally up-left.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally up-left.";
			this->mGame->mPlayer->posX -= 1;
			this->mGame->mPlayer->posY -= 1;
			break;
		case 2: //Monster killed.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally up-left, and killed a monster!";
			this->mGame->mPlayer->posX -= 1;
			this->mGame->mPlayer->posY -= 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "e")
	{
		status = this->mGame->mPlayer->movePlayerUpRight();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further diagonally up-right.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally up-right.";
			this->mGame->mPlayer->posX += 1;
			this->mGame->mPlayer->posY -= 1;
			break;
		case 2: //Monster killed.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally up-right, and killed a monster!";
			this->mGame->mPlayer->posX += 1;
			this->mGame->mPlayer->posY -= 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "z")
	{
		status = this->mGame->mPlayer->movePlayerDownLeft();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further diagonally down-left.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally down-left.";
			this->mGame->mPlayer->posX -= 1;
			this->mGame->mPlayer->posY += 1;
			break;
		case 2: //Monster killed.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally down-left, and killed a monster!";
			this->mGame->mPlayer->posX -= 1;
			this->mGame->mPlayer->posY += 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "c")
	{
		status = this->mGame->mPlayer->movePlayerDownRight();

		switch(status)
		{
		case 0: //Edge reached. No movement.
			status = 0; //No Turn Used.
			this->mGame->mPlayer->statusMessage = "You cannot go any further diagonally down-right.";
			break;
		case 1: //Normal movement.
			status = 1; //Turn Used.
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally down-right.";
			this->mGame->mPlayer->posX += 1;
			this->mGame->mPlayer->posY += 1;
			break;
		case 2: //Monster killed.
			status = 1;
			this->mGame->mPlayer->statusMessage = "You moved 1 step diagonally down-right, and killed a monster!";
			this->mGame->mPlayer->posX += 1;
			this->mGame->mPlayer->posY += 1;
			break;
		default: //Just in case its not any of them, show error.
			status = 2;
		}
	}
	else if (_command == "map" || _command == "m")
	{
		status = 0; //Map does not use a turn.
		this->mGame->isShowMap = !this->mGame->isShowMap;
	}
	else if (_command == "monsters")
	{
		status = 0;
		this->mGame->mPlayer->statusMessage = this->mGame->mAI->GetEnemiesList();
		this->mGame->mPlayer->statusMessage += "\n\n Type \"back\" to return.";
	}
	else if (_command == "help" || _command == "h")
	{
		status = 0; //Sets status to 0 so this command does not use up a turn.
		this->mGame->mPlayer->statusMessage = ""; //Clears any message that may still remain.

		ifstream fileReader; //Starts a new stream reader to open files.
		fileReader.open("data/help.txt"); //Open help.txt to read its contents.
		if(fileReader.good())
		{
			string msgTemp = "";
			while(getline(fileReader, msgTemp)) // Read all the lines in the file and place current line in temp variable.
			{
				this->mGame->mPlayer->statusMessage += msgTemp + "\n"; // Gets the current line and places it in the string.

				if(!fileReader.good())
				{
					break;
				}
			}
		}
		else
		{
			this->mGame->mPlayer->statusMessage = "Could not load \"help.txt\"."; // Shows error when it cant find or open the text file.
		}
		fileReader.close(); //Closes up the file stream to free up memory.
	}
	else if (_command == "back" || _command == "b")
	{
		status = 0;

		if(isBackEnabled == true)
		{
			this->mGame->mPlayer->statusMessage = lastMessage; //Shows the last thing the player did before going to another menu.
		} else {
			status = 2; //Shows command is not recognized, because the player isnt on a appropriate screen.
		}
	}
	else if (_command == "menu")
	{
		status = 0;
		this->mGame->resetGame();
	}
	else if (_command == "exit" || _command == "quit")
	{
		status = 0;
		exit(0); //Exits the program with generic error code 0.
	}
	else
		status = 2;

	return status;
}
