#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(Game *_game);
	~Player(void);

	void NewPlayer();
	int SendCommand(std::string _command);

	std::string playerName;
	std::string statusMessage;

	int posX;
	int posY;

	//Normal
	int movePlayerUp();
	int movePlayerDown();
	int movePlayerLeft();
	int movePlayerRight();

	//Diagonal
	int movePlayerUpLeft();
	int movePlayerUpRight();
	int movePlayerDownLeft();
	int movePlayerDownRight();
private:
	Game *mGame;
};

#endif