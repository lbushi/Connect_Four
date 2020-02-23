#include "cell.h"
Cell::Cell(int row, int col):row{row}, col{col}{}
Info Cell::getInfo() const {
	return Info{c, row, col, chain_length, direction};
}
void Cell::mark(char c) {
	this->c = c;
	chain_length = 1;
	notifyObservers();
}
void Cell::setInfo(int chain_length, Direction direction) {
	this->chain_length = chain_length;
	this->direction = direction;
}
void Cell::notify(const Subject& whonotified) {
	const Cell& the_cell = static_cast<const Cell&>(whonotified);
	Info info = the_cell.getInfo();
	int row = info.row;
	int col = info.col;
	char c = info.c;
	Direction direction = info.direction;
	if (this->c != c) {
		return;
	}
	if (direction == Direction::DEFAULT) {
	       chain_length = info.chain_length + 1;
	       if (this->row - row == 0 && this->col - col == 1) {
		       this->direction = Direction::W;
		       notifyObservers();
	       }
	       else if (this->row - row == 0 && this->col - col == -1) {
		       this->direction = Direction::E;
		       notifyObservers();
	       }
	       else if (this->row - row == 1 && this->col - col == 1) {
		       this->direction = Direction::NW;
		       notifyObservers();
	       }
	       else if (this->row - row == 1 && this->col - col == -1) {
		       this->direction = Direction::NE;
		       notifyObservers();
	       }
	       else if (this->row - row == -1 && this->col - col == 1) {
		       this->direction = Direction::SW;
		       notifyObservers();
	       }
	       else if (this->row - row == -1 && this->col - col == -1) {
		       this->direction = Direction::SE;
	               notifyObservers();
	       }
	       else if (this->row - row == 1 && this->col - col == 0) {
		       this->direction = Direction::N;
		       notifyObservers();
	       }
	       else {
		       this->direction = Direction::S;
		       notifyObservers();
	       }
	}
	else {
		if (this->row - row == 0 && this->col - col == 1 && direction == Direction::W){
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == 0 && this->col - col == -1 && direction == Direction::E) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == 1 && this->col - col == 1 && direction == Direction::NW) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == 1 && this->col - col == -1 && direction == Direction::NE) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == -1 && this->col - col == 1 && direction == Direction::SW) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == -1 && this->col - col == -1 && direction == Direction::SE) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == 1 && this->col - col == 0 && direction == Direction::N) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
		else if (this->row - row == -1 && this->col == col && direction == Direction::S) {
			chain_length = info.chain_length + 1;
			this->direction = direction;
			notifyObservers();
		}
	}
}
char Cell::get_char() {
	return c;
}




