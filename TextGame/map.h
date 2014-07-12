#ifndef MAP_H
#define MAP_H

#include "game.h"

class Map
{
public:
	Map(Game *game);
	~Map(void);

	std::string GetMap();
	void RedrawMap();
	void NewMap();
	unsigned int MovePlayer(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY);
	unsigned int MoveAI(unsigned int oldX, unsigned int oldY, unsigned int newX, unsigned int newY);
	void StartAI(unsigned int &posX, unsigned int &posY);

	static const unsigned int mapSizeX = 10; //Allows editing the size of the map, X co-ord.
	static const unsigned int mapSizeY = 10; //Allows editing the size of the map, Y co-ord.
private:
	char map[mapSizeY][mapSizeX];
	Game *mGame;
};

#endif