#include "main.h"
#include "ai.h"

AI::AI(Game *_game)
{
	this->mGame = _game;
	//Reset variables
	vectorEnemies.clear();
	generatePerTurn = 0;
	generatePerTurnReset = 0;
}

AI::~AI()
{
}

void AI::NewAI()
{
	//Reset variables
	for(unsigned int i = 0; i < vectorEnemies.size(); i++) //Loops vector full of pointer to enemy objects.
	{
		delete vectorEnemies[i]; //Deletes stored object that pointer points to.
		vectorEnemies[i] = NULL; //Sets the pointer to NULL.
	}

	vectorEnemies.clear(); //Clears vector of all pointers.
	
	generatePerTurn = 0; //Resets generate per turn counter to 0.
	generatePerTurnReset = 0; //And its partner variable to 0 as well.
}

void AI::GenerateEnemies(unsigned int enemyCount)
{
	unsigned int newEnemies = enemyCount + vectorEnemies.size(); //Gets the size of the vector if the new enemies where included.

	unsigned int posX = 0; //Sets default position to 0.
	unsigned int posY = 0;

	unsigned int maximumEnemies = 0;
	maximumEnemies = (this->mGame->mapSizeX * this->mGame->mapSizeY) - 10; //Gets the maximum amount of enemies that can fit on the map at any one time.

	if(vectorEnemies.size() >= maximumEnemies) //If maximum enemy is reached, dont generate any more.
	{
		return;
	}

	for (unsigned int i = vectorEnemies.size(); i < newEnemies; i++)
	{
		this->mGame->generateAIpos(posX, posY); //Generates an X,Y position for the AI.
		vectorEnemies.push_back(new Enemy(i, posX, posY)); //Creates a new object, and assigns the pointer to the vector.
    }
}

void AI::KillEnemy(unsigned int posX, unsigned int posY)
{
	for(unsigned int i = 0; i < vectorEnemies.size(); i++)
	{
		if(vectorEnemies[i]->posX == posX && vectorEnemies[i]->posY == posY)
		{
			delete vectorEnemies[i]; //Deletes the object its pointing to in memory.
			vectorEnemies[i] = NULL; //Assigns null to the pointer, so it points to nothing.
			vectorEnemies.erase(vectorEnemies.begin() + i); //Deletes the pointer stored in the vector.
		}
	}
}

void AI::ProcessAI()
{
	if(generatePerTurn > 0)
		generatePerTurn = generatePerTurn - 1; //Reduces the counter, when enemies will spawn.

	if(generatePerTurn <= 0)
	{
		GenerateEnemies(1); //When counter reaches 0, generate 1 enemy.
		generatePerTurn = generatePerTurnReset; //Reset the counter
	}

	for(unsigned int i = 0; i < vectorEnemies.size(); i++)
	{
		int dirMovement = this->mGame->mHelper->generateRandInt(1, 8); //Random int, to determine direction. 1 = Up, 2 = Left, 3 = Down, 4 = Right, 5 = Up-Right, 6 = Up-Left, 7 = Down-Right, 8 = Down-Left.
		int status = 0;
		int newPosX = 0;
		int newPosY = 0;

		switch(dirMovement)
		{
		case 1: //Moves AI up.
			newPosY = vectorEnemies[i]->posY - 1; //Assigns new position.
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, vectorEnemies[i]->posX, newPosY); //Passes new position to parent.

			if(status == 1)
			{
				vectorEnemies[i]->posY = newPosY;
			}
			break;
		case 2: //Moves AI left.
			newPosX = vectorEnemies[i]->posX - 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, newPosX, vectorEnemies[i]->posY);

			if(status == 1)
			{
				vectorEnemies[i]->posX = newPosX;
			}
			break;
		case 3: //Moves AI down.
			newPosY = vectorEnemies[i]->posY + 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, vectorEnemies[i]->posX, newPosY);

			if(status == 1)
			{
				vectorEnemies[i]->posY = newPosY;
			}
			break;
		case 4: //Moves AI right.
			newPosX = vectorEnemies[i]->posX + 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, newPosX, vectorEnemies[i]->posY);

			if(status == 1)
			{
				vectorEnemies[i]->posX = newPosX;
			}
			break;
		case 5: //Moves AI up-right.
			newPosX = vectorEnemies[i]->posX + 1;
			newPosY = vectorEnemies[i]->posY - 1; //Assigns new position.
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, newPosX, newPosY); //Passes new position to parent.

			if(status == 1)
			{
				vectorEnemies[i]->posY = newPosY;
			}
			break;
		case 6: //Moves AI up-left.
			newPosX = vectorEnemies[i]->posX - 1;
			newPosY = vectorEnemies[i]->posY - 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, newPosX, newPosY);

			if(status == 1)
			{
				vectorEnemies[i]->posX = newPosX;
			}
			break;
		case 7: //Moves AI down-left.
			newPosX = vectorEnemies[i]->posX + 1;
			newPosY = vectorEnemies[i]->posY - 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, newPosX, newPosY);

			if(status == 1)
			{
				vectorEnemies[i]->posY = newPosY;
			}
			break;
		case 8: //Moves AI down-right.
			newPosX = vectorEnemies[i]->posX + 1;
			newPosY = vectorEnemies[i]->posY + 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, newPosX, newPosY);

			if(status == 1)
			{
				vectorEnemies[i]->posX = newPosX;
			}
			break;
		default: //Moves AI default up.
			newPosY = vectorEnemies[i]->posY - 1;
			status = this->mGame->moveAI(vectorEnemies[i]->posX, vectorEnemies[i]->posY, vectorEnemies[i]->posX, newPosY);

			if(status == 1)
			{
				vectorEnemies[i]->posY = newPosY;
			}
		}
	}

	this->mGame->redrawMap();
}

string AI::GetEnemiesList()
{
	string list = "";

	if(vectorEnemies.size() > 0)
	{
		for(unsigned int i = 0; i < vectorEnemies.size(); i++) //Gets a list of enemies from the vector.
		{
			char buffer[256];

			sprintf_s(buffer, sizeof(buffer), "Enemy ID: %d - X: %d / Y: %d\n ", vectorEnemies[i]->id, vectorEnemies[i]->posX, vectorEnemies[i]->posY);

			list += buffer;
		}
	}

	return list;
}

unsigned int AI::GetAIAliveCount()
{
	return vectorEnemies.size(); //Returns the amount of enemies alive.
}