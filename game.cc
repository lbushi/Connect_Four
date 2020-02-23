#include "game.h"
#include <vector>
#include <iostream>
using namespace std;
bool valid_cell(int row, int col, int game_size) {
	return row >= 0 && row < game_size && col >= 0 && col < game_size;
}
map<pair<int, int>, int> Game::get_chain() const
{
	return the_chain;
}
void Game::init() {
	controllers.emplace_back(new ControllerX());
	controllers.emplace_back(new ControllerO());
	td = unique_ptr<TextDisplay>(new TextDisplay(game_size));
	for (int i = 0; i < game_size; ++i) {
		free_cells.emplace_back(7);
	}
	for (int i = 0; i < game_size; ++i) {
		the_grid.emplace_back(vector<Cell>(0, Cell{-1, -1}));
		for (int j = 0; j < game_size; ++j) {
			the_grid[i].emplace_back(Cell{i, j});
		}
	}
	for (int i = 0; i < game_size; ++i) {
		for (int j = 0; j < game_size; ++j) {
			if (valid_cell(i, j + 1, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i][j + 1]);
			}
			if (valid_cell(i, j - 1, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i][j - 1]);
			}
			if (valid_cell(i + 1, j, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i + 1][j]);
			}
			if (valid_cell(i - 1, j, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i - 1][j]);
			}
			if (valid_cell(i + 1, j + 1, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i + 1][j + 1]);
			}
			if (valid_cell(i + 1, j - 1, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i + 1][j - 1]);
			}
			if (valid_cell(i - 1, j - 1, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i - 1][j - 1]);
			}
			if (valid_cell(i - 1, j + 1, game_size)) {
			the_grid[i][j].attachObserver(&the_grid[i - 1][j + 1]);
			}
			the_grid[i][j].attachObserver(this);
			the_grid[i][j].attachObserver(td.get());
		}
	}
}
void Game::change_turn() {
       ++turn;
}
int Game::winner() {
	return turn % 2 + 1;
}
bool Game::game_over() const {
	return is_game_over;
}
int Game::get_row(int col) const
{
	return free_cells[col];
}
void Game::mark(char c, int col) {
	if (free_cells[col] < 0) {
		string exception = "Invalid Move!";
		throw exception;
	}
	int row = free_cells[col];
	--free_cells[col];
	the_grid[row][col].setInfo(0, Direction::DEFAULT);
	the_grid[row][col].mark(c);
	for (auto& row: the_grid) {
		for (auto& cell: row) {
			cell.setInfo(0, Direction::DEFAULT);
		}
	}
	for (auto& row: the_grid) {
		for (auto& cell: row) {
			if (cell.get_char() != '.') {
			cell.mark(cell.get_char());
			for (auto& row: the_grid) {
				for (auto& cell: row) {
					cell.setInfo(0, Direction::DEFAULT);
				}
			}
		}
	}
}
}
void Game::graphics_mark(int col)
{
	mark(turn % 2 ? 'O' : 'X', col);
}
Command* Game::handleInput() {
	return controllers[turn % 2]->handleInput();
}
void Game::notify(const Subject& whonotified) {
	const Cell& the_cell = static_cast<const Cell&>(whonotified);
	Info info = the_cell.getInfo();
	int row = info.row;
	int col = info.col;
	Direction dir = info.direction;
	if (info.chain_length == win_size) {
		is_game_over = true;
		if (dir == Direction::N) {
			
		}
		if (dir == Direction::S) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row + 1, col)] = 1;
			the_chain[make_pair(row + 2, col)] = 1;
			the_chain[make_pair(row + 3, col)] = 1;
		}
		if (dir == Direction::E) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row, col + 1)] = 1;
			the_chain[make_pair(row, col + 2)] = 1;
			the_chain[make_pair(row, col + 3)] = 1;
		}
		if (dir == Direction::W) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row, col - 1)] = 1;
			the_chain[make_pair(row, col - 2)] = 1;
			the_chain[make_pair(row, col - 3)] = 1;
		}
		if (dir == Direction::NW) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row - 1, col - 1)] = 1;
			the_chain[make_pair(row - 2, col - 2)] = 1;
			the_chain[make_pair(row - 3, col - 3)] = 1;
		}
		if (dir == Direction::NE) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row - 1, col + 1)] = 1;
			the_chain[make_pair(row - 2, col + 2)] = 1;
			the_chain[make_pair(row - 3, col + 3)] = 1;
		}
		if (dir == Direction::SW) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row + 1, col - 1)] = 1;
			the_chain[make_pair(row + 2, col - 2)] = 1;
			the_chain[make_pair(row + 3, col - 3)] = 1;
		}
		if (dir == Direction::SE) {
			
			the_chain[make_pair(row, col)] = 1;
			the_chain[make_pair(row + 1, col + 1)] = 1;
			the_chain[make_pair(row + 2, col + 2)] = 1;
			the_chain[make_pair(row + 3, col + 3)] = 1;
		}
	}
}
ostream& operator<<(ostream& out, Game& g) {
	out << *(g.td);
	return out;
}


