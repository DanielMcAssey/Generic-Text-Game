#include "main.h"
#include "map.h"

Map::Map(Game *_game)
{
	this->mGame = _game; //Assign pointer so this class can access the core game.
	this->NewMap(); //Generates a new map when constructor is called.
}

Map::~Map(void)
{
}

void Map::RedrawMap()
{
	for(unsigned int i = 0; i < mapSizeY; i++) //Loops Y co-ordinates.
		for(unsigned int j = 0; j < mapSizeX; j++) //Loops X co-ordinates.
			map[i][j] = 'f'; //Resets map.

	if (this->mGame->mAI->vectorEnemies.size() > 0)
		for (unsigned int i = 0; i < this->mGame->mAI->vectorEnemies.size(); i++) //Loops vector full of pointer to enemy objects.
			map[this->mGame->mAI->vectorEnemies[i]->posY][this->mGame->mAI->vectorEnemies[i]->posX] = 'E';

	map[this->mGame->mPlayer->posY][this->mGame->mPlayer->posX] = 'P';
}

void Map::NewMap()
{
	for(unsigned int i = 0; i < mapSizeY; i++) //Loops Y co-ordinates.
	{
		for(unsigned int j = 0; j < mapSizeX; j++) //Loops X co-ordinates.
		{
			map[i][j] = 'f'; //Resets map.
		}
	}
}

unsigned int Map::MovePlayer(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY)
{
	unsigned int status = 0; //Sets status of player. 0 = No movement. 1 = Normal Movement. 2 = Killed Monster.

	if(newX >= 0 && newX <= (mapSizeX - 1)) //Checks if its inside map bounds.
	{
		if(newY >= 0 && newY <= (mapSizeY - 1)) //Checks if its inside map bounds.
		{
			if(map[newY][newX] == 'E') //Checks if monster is in the spot, if it is, it kills it.
			{
				map[oldY][oldX] = 'f'; //Resets old player position, to an available one.
				map[newY][newX] = 'P'; //Sets new player position.
				this->mGame->killAI(newX, newY); //Kills the enemy.
				status = 2; //Sets status that movement is ok.
			}
			else
			{
				map[oldY][oldX] = 'f'; //Resets old player position, to an available one.
				map[newY][newX] = 'P'; //Sets new player position.
				status = 1; //Sets status that movement is ok.
			}
		}
		else
		{
			status = 0; //Edge of Y reached. No Movement
		}
	}
	else
	{
		status = 0; //Edge of X reached. No Movement
	}

	return status;
}

unsigned int Map::MoveAI(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY)
{
	unsigned int status = 0; //Sets status of AI. 0 = No movement. 1 = Normal Movement.

	if(newX >= 0 && newX <= (mapSizeX - 1)) //Checks if its inside map bounds.
	{
		if(newY >= 0 && newY <= (mapSizeY - 1)) //Checks if its inside map bounds.
		{
			if(map[newY][newX] == 'f') //Checks if area is free, if it is it moves it.
			{
				map[oldY][oldX] = 'f'; //Resets old AI position, to an available one.
				map[newY][newX] = 'E'; //Sets new AI position.
				status = 1; //Sets status that movement is ok.
			}
			else
			{
				status = 0; //No movement, as area is taken up.
			}
		}
		else
		{
			status = 0; //Edge of Y reached. No Movement
		}
	}
	else
	{
		status = 0; //Edge of X reached. No Movement
	}

	return status;
}

void Map::StartAI(unsigned int &posX, unsigned int &posY)
{
	bool posIsSet = false;

	while(posIsSet == false)
	{
		posX = this->mGame->mHelper->generateRandInt(0, (mapSizeX - 1)); //Generate random position within boundries.
		posY = this->mGame->mHelper->generateRandInt(0, (mapSizeY - 1));

		if(map[posY][posX] == 'f') //If position is free set it as new enemy position.
		{
			map[posY][posX] = 'E'; //Set new position as an enemy.
			posIsSet = true; //Tells while loop that position is ok and its been set.
		}
	}
}

string Map::GetMap()
{
	this->RedrawMap();
	string underscoreSpacing = "";
	string spaceSpacing = "";

	for(unsigned int i = 0; i < mapSizeX; i++)
	{
		underscoreSpacing += "_";
		spaceSpacing += " ";
	}

	string dispMap = "y   " + underscoreSpacing + "\n    /" + spaceSpacing + "\\\n";
	dispMap += "";

	for(unsigned int i = 0; i < mapSizeY; i++) //Loops Y co-ordinates.
	{
		char buffer[128]; //Create a buffer for sprintf.

		if(i < 10)
			sprintf_s(buffer, sizeof(buffer), " %d  |", i);
		else
			sprintf_s(buffer, sizeof(buffer), " %d |", i);

		dispMap += buffer;

		for(unsigned int j = 0; j < mapSizeX; j++) //Loops X co-ordinates.
		{
			char curMapTarget = map[i][j];

			switch(curMapTarget)
			{
			case 'f': //Available space on map.
				dispMap += "."; //Shows a symbol for available space.
				break;
			case 'P': //Shows player on map.
				dispMap += "P"; //Shows a symbol for player.
				break;
			case 'E': //Shows AI on map.
				dispMap += "M"; //Shows a symbol for an AI.
				break;
			default:
				dispMap += "."; 
			}
		}
		dispMap += "|\n";
	}

	dispMap += "    \\" + underscoreSpacing + "/\n\n     ";

	for(unsigned int i = 0; i < mapSizeX; i++)
	{
		char buffer[128]; //Create a buffer for sprintf.
		sprintf_s(buffer, sizeof(buffer), "%d", i);
		dispMap += buffer;
	}

	dispMap += "  x";

	return dispMap;
}