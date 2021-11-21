#pragma once
#include "Utility.h"
#include "Position.h"
#define POINT 250
#define WALL 219
#define TELEPORT 176
#define P 250
#define W 219
#define T 176
#define S 32

enum board_dictionary {
	WIDTH = 80		,
	HEIGHT = 25		,
	//WALL = 219,
	//W = 219,
	//POINT = 250,
	//P = 250,
	//TELEPORT = 176 ,
	//T = 176
	//S = 32
};

enum Color {
	BLACK           ,
	BLUE 			,
	GREEN			,
	CYAN 			,
	RED 			,
	MAGENTA 		,
	BROWN  			,
	LIGHTGREY 		,
	DARKGREY 		,
	LIGHTBLUE 		,
	LIGHTGREEN		,
	LIGHTCYAN 		,
	LIGHTRED 		,
	LIGHTMAGENTA 	,
	YELLOW  		,
	WHITE 
};

class Board {
	unsigned char board[HEIGHT][WIDTH];

public:
	void init_board();
	void print_board(const bool color_mode);
	void set_color(int color_pick) const {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_pick) ;}

	unsigned char get_cell(const Position cell_pos) { return board[cell_pos.get_y()][cell_pos.get_x()]; }
	void set_cell(Position cell_pos, unsigned char c) { board[cell_pos.get_y()][cell_pos.get_x()] = c; }

};




























