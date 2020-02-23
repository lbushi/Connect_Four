#pragma once
#include <iostream>
#include "game.h"
class Command{
	protected:
	int col;
	public:
	        Command(int col);
		virtual void execute(Game& g) = 0;
		virtual ~Command() = default;
};
