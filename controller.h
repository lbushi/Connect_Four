#pragma once
class Command;
#include <iostream>
class Controller {
	public:
		virtual  Command* handleInput() = 0;
};
