#pragma once
enum class Direction { N, S, E, W, NE, NW, SE, SW, DEFAULT};
struct Info{
	char c;
	int row;
	int col;
	int chain_length;
	Direction direction;
};
