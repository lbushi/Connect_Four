#pragma once
#include "observer.h"
#include <vector>
#include "subject.h"
#include <iostream>
class TextDisplay: public Observer {
	std::vector<std::vector<char>> the_grid;
	public:
	TextDisplay(int);
	void notify(const Subject&) override;
	friend std::ostream& operator<<(std::ostream& out, TextDisplay& t);
};

