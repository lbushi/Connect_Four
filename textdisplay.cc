#include "textdisplay.h"
#include "cell.h"
using namespace std;
TextDisplay::TextDisplay(int size) {
	the_grid = vector<vector<char>>(size, vector<char>(size, '.'));
}
void TextDisplay::notify(const Subject& whonotified) {
	const Cell& the_cell = static_cast<const Cell&>(whonotified);
	Info info = the_cell.getInfo();
	int row = info.row;
	int col = info.col;
	char the_mark = info.c;
	the_grid[row][col] = the_mark;
}
ostream& operator<<(ostream& out, TextDisplay& t) {
	for (auto row: t.the_grid) {
		for (auto mark: row) {
			out << mark;
		}
		out << endl;
	}
	return out;
}

