#include "controllerO.h"
#include "commandO.h"
Command* ControllerO::handleInput() {
	int col = 0;
	std::cin >> col;
	return new CommandO{col};
}
