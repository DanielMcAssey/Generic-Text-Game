#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	Command(Game *_game);
	~Command(void);
	int SendCommand(std::string _command);
private:
	Game *mGame;
	std::string lastCommand;
	std::string lastMessage;
	bool isBackEnabled;
};

#endif

