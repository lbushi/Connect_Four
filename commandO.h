#pragma once
#include "command.h"
class CommandO: public Command {
	public:
		CommandO(int col);
		void execute(Game& g) override;
};
