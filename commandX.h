#pragma once
#include "command.h"
class CommandX: public Command {
	public:
		CommandX(int col);
		void execute(Game& g);
};
