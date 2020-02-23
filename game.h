#pragma once
#include <vector>
#include "observer.h"
#include "textdisplay.h"
#include <memory>
#include <iostream>
#include "info.h"
#include "cell.h"
#include "controller.h"
#include "controllerX.h"
#include "controllerO.h"
#include <utility>
#include <map>
class Command;
class Subject;
class Game: public Observer {
	const int game_size = 8;
	const int win_size = 4;
	bool is_game_over = false;
	std::map<std::pair<int, int>, int> the_chain;
	std::vector<std::vector<Cell>> the_grid;
	std::unique_ptr<TextDisplay> td;
	std::vector<int> free_cells;
	int turn = 0;
	std::vector<std::unique_ptr<Controller>> controllers;
	public:
	std::map<std::pair<int, int>, int> get_chain() const;
	void init();
	void change_turn();
	bool game_over() const;
	int get_row(int) const;
	void mark(char c,int col);
	void graphics_mark(int col);
	void notify(const Subject&) override;
	int winner();
	Command* handleInput();
	friend std::ostream& operator<<(std::ostream&, Game& g);
};

