#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
	Enemy(unsigned int newID, unsigned int newPosX, unsigned int newPosY);
	~Enemy(void);
	unsigned int id;
	unsigned int posX;
	unsigned int posY;
	unsigned int alive;
};

#endif