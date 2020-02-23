#include "commandO.h"
CommandO::CommandO(int col): Command{col} {}
void CommandO::execute(Game& g) {
	g.mark('O',col);
}
