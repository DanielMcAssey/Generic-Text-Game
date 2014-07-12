#include "main.h"
#include "enemy.h"

Enemy::Enemy(unsigned int newID, unsigned int newPosX, unsigned int newPosY)
{
	id = newID; //Sets the new ID of the enemy.
	posX = newPosX; //Sets the randomly generated positions.
	posY = newPosY;
	alive = 1; //When enemy is created it automatically sets it to alive.
}

Enemy::~Enemy(void)
{
}