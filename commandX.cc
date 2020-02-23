#include "commandX.h"
CommandX::CommandX(int col): Command{col} {}
void CommandX::execute(Game& g) {
	g.mark('X',col);
}
