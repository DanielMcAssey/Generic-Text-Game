#include "main.h"
#include "game.h"

Game::Game(void)
{
	//Reset any variables
	//Options Variables
	initStarted = false;
	nameComplete = false;
	monsterOccuranceComplete = false;
	maxTurnsComplete = false;
	//END: Options Variables

	this->mHelper = new Helper();
	this->mMap = new Map(this);
	this->mapSizeX = this->mMap->mapSizeX;
	this->mapSizeY = this->mMap->mapSizeY;

	this->mAI = new AI(this);
	this->mPlayer = new Player(this);
	this->mCommand = new Command(this);

	//Extra Variables
	isWrongCommand = false;
	isError = false;
	isNewMonster = false;
	startMessage = false;
	isInternalError = false;
	//END: Extra Variables

	//Game Variables
	startMonsterCount = 10; //Sets the starting monsters.
	monstersEachTurn = 0;
	monstersAlive = 0;
	maxTurn = 0;
	curTurn = 0;
	statusMessage = "";
	isShowMap = false; //Show map to player.
	isGameWon = false;
	mapSizeX = 0;
	mapSizeY = 0;
	//END: Game Variables

	//Menu Mode
	mode = 0;
}

Game::~Game(void)
{
}

void Game::setupEnemies(unsigned int enemiesCount)
{
	this->mAI->GenerateEnemies(enemiesCount); //Generates enemies, based on value passed.
}

string Game::displayMap()
{
	return this->mMap->GetMap();
}

unsigned int Game::movePlayer(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY)
{
	return this->mMap->MovePlayer(oldX, oldY, newX, newY); //Moves player to the new co-ordinates.
}

unsigned int Game::moveAI(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY)
{
	return this->mMap->MoveAI(oldX, oldY, newX, newY); //Moves AI to the new co-ordinates.
}

void Game::generateAIpos(unsigned int &posX, unsigned int &posY)
{
	this->mMap->StartAI(posX, posY); //When AI is spawned, it generates a random position for the AI.
}

void Game::killAI(unsigned int posX, unsigned int posY)
{
	this->mAI->KillEnemy(posX, posY); //When an AI has been killed, it sets its local boolean variable "Alive" to false.
}

void Game::redrawMap()
{
	this->mMap->RedrawMap();
}

void Game::DrawMenu()
{

	cout << "		 ______  ______  __  __   ______     ______   ______   __    __   ______" << endl;
	cout << "		/\\__  _\\/\\  ___\\/\\_\\_\\_\\ /\\__  _\\   /\\  ___\\ /\\  __ \\ /\\ \"-./  \\ /\\  ___\\" << endl;
	cout << "		\\/_/\\ \\/\\ \\  __\\\\/_/\\_\\/_\\/_/\\ \\/   \\ \\ \\__ \\\\ \\  __ \\\\ \\ \\-./\\ \\\\ \\  __\\" << endl;
	cout << "		   \\ \\_\\ \\ \\_____\\/\\_\\/\\_\\  \\ \\_\\    \\ \\_____\\\\ \\_\\ \\_\\\\ \\_\\ \\ \\_\\\\ \\_____\\" << endl;
	cout << "		    \\/_/  \\/_____/\\/_/\\/_/   \\/_/     \\/_____/ \\/_/\\/_/ \\/_/  \\/_/ \\/_____/" << endl << endl;
	cout << "	 ______   _____    __   __ ______   __   __   ______  __  __   ______   ______   ______" << endl;
	cout << "	/\\  __ \\ /\\  __-. /\\ \\ / //\\  ___\\ /\\ \"-.\\ \\ /\\__  _\\/\\ \\/\\ \\ /\\  == \\ /\\  ___\\ /\\  ___\\" << endl;
	cout << "	\\ \\  __ \\\\ \\ \\/\\ \\\\ \\ \\'/ \\ \\  __\\ \\ \\ \\-.  \\\\/_/\\ \\/\\ \\ \\_\\ \\\\ \\  __< \\ \\  __\\ \\ \\___  \\" << endl;
	cout << "	 \\ \\_\\ \\_\\\\ \\____- \\ \\__|  \\ \\_____\\\\ \\_\\\\\"\\_\\  \\ \\_\\ \\ \\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\/\\_____\\" << endl;
	cout << "	  \\/_/\\/_/ \\/____/  \\/_/    \\/_____/ \\/_/ \\/_/   \\/_/  \\/_____/ \\/_/ /_/ \\/_____/ \\/_____/" << endl;

	cout << "\n --------------------------------------------------------------------------------------------------------\n";
	cout << " |					Main Menu							|\n";
	cout << " --------------------------------------------------------------------------------------------------------\n |													|\n";
	cout << " |					1. Play Game							|\n";
	cout << " |					2. Credits							|\n";
	cout << " |					3. Exit								|\n |													|";
	cout << "\n --------------------------------------------------------------------------------------------------------\n\n";

	string input = "";

	if(isInternalError == true)
	{
		cout << "\n			ERROR: Input must be a number and between 1 and 3." << endl; //Shows Error
	}

	cout << "\n					Please choose: ";
	getline(cin, input);

	stringstream strStream(input);
	if(input.length() > 0 && strStream >> mode)
	{
		if(mode >= 1 && mode <= 3) //Check whether the menu selection is in bounds.
		{
			input = "";
			isInternalError = false;
		}
		else
		{
			isInternalError = true;
		}
	}
	else
	{
		isInternalError = true;
	}
}

void Game::DrawGame()
{
	if(initStarted == false) { //Check if player setup has been started.
		initStarted = true; //Sets that player setup has been started.
		cout << "\n --------------------------------------------------------------------------------------------------------\n";
		cout << " |					Player Info:							|\n";
		cout << " --------------------------------------------------------------------------------------------------------\n |													|\n";
		cout << " |					We require							|\n";
		cout << " |					some details							|\n";
		cout << " |					from you.							|\n |													|";
		cout << "\n --------------------------------------------------------------------------------------------------------\n";

		string input = "";

		while(nameComplete == false)
		{
			if(isInternalError == true)
			{
				cout << "\n				ERROR: Input must be longer than 0 characters." << endl; //Shows Error
				isInternalError = false; //Sets no error.
			}

			cout << "\n				Please enter your player name: ";
			getline(cin, input);

			if(input.length() > 0) //Checks length
			{
				this->mPlayer->playerName = input; //Sets player name according to input.
				input = ""; //Clears input.
				nameComplete = true; //Confirms the name has been inputted.
				break; //Breaks loop if everything is ok.
			}
			else
			{
				isInternalError = true; //Sets error to show.
			}
		}

		while(monsterOccuranceComplete == false)
		{
			if(isInternalError == true)
			{
				cout << "\n				ERROR: Input must be a number." << endl; //Shows Error
				isInternalError = false; //Sets no error.
			}

			cout << "\n				Please enter how often the monsters will spawn: ";
			getline(cin, input);

			stringstream strStream(input);
			if(input.length() > 0 && strStream >> monstersEachTurn) //Checks length, and see if string stream can be converted to maximum turns.
			{
				input = ""; //Clears input.
				monsterOccuranceComplete = true; //Confirms the occurance of monsters has been inputted.
				break;  //Breaks loop if everything is ok.
			}
			else
			{
				isInternalError = true; //Sets error to show.
			}
		}

		while(maxTurnsComplete == false)
		{
			if(isInternalError == true)
			{
				cout << "\n				ERROR: Input must be a number and greater than monster occurance." << endl; //Shows Error
				isInternalError = false; //Sets no error.
			}

			cout << "\n				Please enter the maximum number of turns: ";
			getline(cin, input);

			stringstream strStream(input);
			if(input.length() > 0 && strStream >> maxTurn) //Checks length, and see if string stream can be converted to maximum turns.
			{
				if(monstersEachTurn < maxTurn)
				{
					input = ""; //Clears input.
					maxTurnsComplete = true; //Confirms the max turns have been set.
					break; //Breaks loop if everything is ok.
				}
				else
				{
					isInternalError = true; //Sets error to show.
				}
			}
			else
			{
				isInternalError = true; //Sets error to show.
			}
		}

		char buffer[1024]; //Creates a character buffer.
		sprintf_s(buffer, sizeof(buffer), "You are on a quest, you have to kill all monsters around you,\n and you only have %d turns to do it in, but hurry every %d turns,\n a new monster spawns.", maxTurn, monstersEachTurn);
		this->mPlayer->statusMessage = buffer; //Applies the character buffer to the current message shown to the player.
		startMessage = true; //Shows starting message.

		//Setup Player
		this->mPlayer->posX = this->mHelper->generateRandInt(0, this->mMap->mapSizeX); //Generates random co-ordinates to where the player starts. X co-ords
		this->mPlayer->posY = this->mHelper->generateRandInt(0, this->mMap->mapSizeY); //Generates random co-ordinates to where the player starts. Y co-ords
		this->movePlayer(0, 0, this->mPlayer->posX, this->mPlayer->posY); //Moves player to new random co-ordinates.

		//Setup AI
		setupEnemies(startMonsterCount); //Generates enemies and adds them to the map.
		this->mAI->generatePerTurn = monstersEachTurn; //Assigns to the AI class, in what round a new enemy is created.
		this->mAI->generatePerTurnReset = monstersEachTurn; //Assigns to the AI class, what to reset the counter to, when an enemy spawns.
	} else {
		string playerCommand = ""; //Stores Current Command and resets when executed again.
		int commandStatus = 0; //Temporary variable to store the status of the command executed.

		monstersAlive = this->mAI->GetAIAliveCount(); //Gets the number of monsters alive.
		this->statusMessage = this->mPlayer->statusMessage; //Shows the user the current message and status of the game.

		if(monstersAlive == 0) //Chceks if any monsters are still alive.
		{
			this->isGameWon = true; //If there are non alive, set the game as won.
		}
		else
		{
			this->isGameWon = false; //If there are monsters still alive, it keep the game as not won.
		}

		cout << "\n --------------------------------------------------------------------------------------------------------\n";
		cout << " |													|\n |					Player:	" << this->mPlayer->playerName << "							|" << endl;
		cout << " |					Current Turn: " << curTurn << " out of " << maxTurn << "					|" << endl;
		cout << " |					Monsters Alive: " << monstersAlive << "						|\n |													|" << endl;
		cout << " --------------------------------------------------------------------------------------------------------";
		cout << "\n\n";

		if(isWrongCommand == true)
		{
			cout << " ERROR: Command not recognized.\n" << endl; //Shows an error, when command not recognized.
			isWrongCommand = false;
		}

		if (isNewMonster == true && this->isGameWon == false)
		{
			cout << " WARNING: A New monster has appeared.\n" << endl; //Shows a warning to the user, when a new monster is detected.
			isNewMonster = false;
		}

		if(isError == true)
		{
			cout << " ERROR: An error occured.\n" << endl; //Shows if any error's have occured.
			isError = false;
		}

		if(this->isGameWon == false && this->isShowMap == true)
		{
			cout << " ";
			cout << displayMap() << endl;
			cout << "\n P = Player, M = Monster, - = Free Space\n\n\n";
		}

		if (this->isGameWon)
			this->statusMessage = "Congratulations! You have defeated all the monsters.\n Type \"Menu\" to return to the menu, and try again."; //Shows a message when the player has won the game and defeated all monsters.

		if (curTurn >= maxTurn && this->isGameWon == false)
			this->statusMessage = "You have lost! It seems you have run out of turns to kill all the monsters.\n Type \"Menu\" to return to the menu, and try again."; //Shows a message when max turns have been reached.

		if(startMessage == true)
		{
			cout << " Type \"help\" to see a list of commands.\n" << endl; //Shows an introductory message to the player, to help him start.
			startMessage = false;
		}

		if (this->isGameWon == false)
		{
			char buffer[128];
			sprintf_s(buffer, sizeof(buffer), " Your current position (X,Y): %d,%d\n", this->mPlayer->posX, this->mPlayer->posY);

			cout << buffer << endl; //Shows current position of player on main screen.
		}

		cout << " " << this->statusMessage << endl;

		cout << "\n What would you like to do next?: "; //Shows a prompt to the user on what the next command is.
		getline(cin, playerCommand); //Gets the player command inputted.
		cout << "\n";

		commandStatus = this->mPlayer->SendCommand(playerCommand); //Send Command and return active message.
		playerCommand = ""; //Clear stored player command, after it is submitted.

		if(commandStatus == 0) //Command does not use a turn.
		{

		}
		else if(commandStatus == 1) //Command uses a turn.
		{
			this->mAI->ProcessAI(); //If command uses turn, process the AI.

			if (this->mAI->generatePerTurn == 0)
			{
				isNewMonster = true; //Sets true, when a new monster has been spawned.
			}
			curTurn = curTurn + 1; //Add to Turns
		}
		else if(commandStatus == 2) //Command not found.
		{
			isWrongCommand = true; //Sets true when command is not recognized.
		}
		else if(commandStatus == 3) //Error occured.
		{
			isError = true; //Sets true when an error occured processing the command.
		}
	}
}

void Game::DrawCredits()
{
	string input = "";

	cout << "\n --------------------------------------------------------------------------------------------------------\n";
	cout << " |													|\n |					Developed By: Daniel McAssey					|\n";
	cout << " |					Programmed By: Daniel McAssey					|\n |													|\n";
	cout << " --------------------------------------------------------------------------------------------------------\n";

	if(isError == true)
	{
		cout << "\n\n					ERROR: Command not recognized.";
		isError = false;
	}

	cout << "\n\n					Type \"back\" to return: ";
	getline(cin, input);

	input = this->mHelper->toLower(input); //Makes all text lowercase.

	if(input == "back")
	{
		mode = 0; //Sets mode to main menu;
	}
	else
	{
		isError = true; //Causes an error.
	}
}

void Game::resetGame()
{
	//Reset any variables
	//Options Variables
	this->initStarted = false;
	this->nameComplete = false;
	this->monsterOccuranceComplete = false;
	this->maxTurnsComplete = false;
	//END: Options Variables

	//Extra Variables
	this->isWrongCommand = false;
	this->isError = false;
	this->isNewMonster = false;
	this->startMessage = false;
	//END: Extra Variables

	//Game Variables
	this->monstersEachTurn = 0;
	this->monstersAlive = 0;
	this->maxTurn = 0;
	this->curTurn = 0;
	this->statusMessage = "";
	this->isGameWon = false;
	this->isShowMap = false; //Show map to player.
	//END: Game Variables

	//Reset AI
	this->mAI->NewAI();

	//Reset Player
	this->mPlayer->NewPlayer();

	//Reset Map
	this->mMap->NewMap();

	//Menu Mode
	mode = 0;
}