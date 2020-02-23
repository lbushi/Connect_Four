#pragma once
#include "subject.h"
#include "info.h"
class Cell: public Subject, public Observer {
	char c = '.';
	int chain_length = 1;
	int row, col;
	Direction direction = Direction::DEFAULT;
	public:
	Cell(int row, int col);
	void mark(char);
	char get_char();
	Info getInfo() const;
	void setInfo(int, Direction);
	void notify(const Subject& whonotified) override;
};
