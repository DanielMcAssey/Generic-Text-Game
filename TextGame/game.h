#ifndef GAME_H
#define GAME_H

class Helper;
class Map;
class AI;
class Player;
class Command;

class Game
{
public:
	Game(void);
	~Game(void);

	//Startup Functions
	void setupEnemies(unsigned int enemiesCount);

	//Game Functions
	std::string displayMap();
	unsigned int movePlayer(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY);
	unsigned int moveAI(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY);
	void generateAIpos(unsigned int &posX, unsigned int &posY);
	void killAI(unsigned int posX, unsigned int posY);
	void redrawMap();

	//Generic Functions
	void DrawMenu();
	void DrawGame();
	void DrawCredits();

	//Reset Function
	void resetGame();

	//BEGIN: Variables
	//Initial Options Variables
	bool initStarted;
	bool nameComplete;
	bool monsterOccuranceComplete;
	bool maxTurnsComplete;
	//END: Initial Options Variables

	//Game Variables
	unsigned int startMonsterCount;
	unsigned int monstersEachTurn;
	unsigned int monstersAlive;
	unsigned int maxTurn;
	unsigned int curTurn;
	unsigned int mapSizeX;
	unsigned int mapSizeY;
	bool isShowMap; //Show map to player.
	bool isGameWon; //Checks if player has won.
	//END: Game Variables
	
	unsigned int mode; //Menu Mode

	Helper *mHelper;
	Map *mMap;
	AI *mAI;
	Player *mPlayer;
	Command *mCommand;
private:
	std::string statusMessage;

	//Extra Variables
	bool isWrongCommand;
	bool isError;
	bool isNewMonster;
	bool startMessage;
	bool isInternalError;
	//END: Extra Variables
};

#endif