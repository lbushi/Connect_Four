#include "controllerX.h"
#include "commandX.h"
using namespace std;
Command* ControllerX::handleInput() {
	int col = 0;
	cin >> col;
	return new CommandX{col};
}
