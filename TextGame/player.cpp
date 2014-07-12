#include "main.h"
#include "player.h"

Player::Player(Game *_game)
{
	this->mGame = _game;
	this->NewPlayer();
}

Player::~Player(void)
{
}

void Player::NewPlayer()
{
	//Reset any variables
	this->playerName = "";
	this->statusMessage = "UNDEFINED";
	this->posX = 0;
	this->posY = 0;
}


int Player::SendCommand(string Command)
{
	return this->mGame->mCommand->SendCommand(Command);
}

//Functions for moving the player.
int Player::movePlayerUp()
{
	return this->mGame->movePlayer(posX, posY, posX, posY-1); //Passes new co-ordinates to send player 1 space up.
}

int Player::movePlayerDown()
{
	return this->mGame->movePlayer(posX, posY, posX, posY + 1); //Passes new co-ordinates to send player 1 space down.
}

int Player::movePlayerLeft()
{
	return this->mGame->movePlayer(posX, posY, posX - 1, posY); //Passes new co-ordinates to send player 1 space left.
}

int Player::movePlayerRight()
{
	return this->mGame->movePlayer(posX, posY, posX + 1, posY); //Passes new co-ordinates to send player 1 space right.
}

int Player::movePlayerUpLeft()
{
	return this->mGame->movePlayer(posX, posY, posX - 1, posY - 1); //Passes new co-ordinates to send player 1 space up left.
}

int Player::movePlayerUpRight()
{
	return this->mGame->movePlayer(posX, posY, posX + 1, posY - 1); //Passes new co-ordinates to send player 1 space up right.
}

int Player::movePlayerDownLeft()
{
	return this->mGame->movePlayer(posX, posY, posX - 1, posY + 1); //Passes new co-ordinates to send player 1 space down left.
}

int Player::movePlayerDownRight()
{
	return this->mGame->movePlayer(posX, posY, posX + 1, posY + 1); //Passes new co-ordinates to send player 1 space down right.
}