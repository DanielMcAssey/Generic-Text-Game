#ifndef AI_H
#define AI_H

#include "enemy.h"

class Game; //Reference to classGame class.
class AI
{
public:
	AI(Game *_game);
	~AI(void);

	void NewAI();

	void GenerateEnemies(unsigned int enemyCount);
	void KillEnemy(unsigned int posX, unsigned int posY);
	void ProcessAI();

	std::string GetEnemiesList();

	unsigned int GetAIAliveCount();

	unsigned int generatePerTurn; //Enemies to generate in what turn.
	unsigned int generatePerTurnReset; //What to reset to when enemy is generated.

	std::vector<Enemy*> vectorEnemies; //Stores the enemies
private:
	Game *mGame;
};

#endif