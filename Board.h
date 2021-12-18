#pragma once
#include "Utility.h"
#include "Position.h"
#include "Color.h"

#include <fstream>

using namespace std::filesystem;

class Board {

public:
	enum board_signs { P = 250, W = 219, T = 176, S = 32 , POINT = 250, WALL = 219, TELEPORT = 176 };
    enum board_size { MAX_WIDTH = 80, MAX_HEIGHT = 25, };

    enum class Color{
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHTGREY,
        DARKGREY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE
    };
private:
	unsigned char board[MAX_HEIGHT][MAX_WIDTH];
    int height, width;
    Position inital_pacman_pos;
    Position inital_ghosts_pos[];
    

public:
	void print_board(const bool color_mode);
    void our_spacial_board();

    Positon& get_inital_pacman_pos() { return inital_pacman_pos; }
    Positon& get_ghost_pacman_pos() { return inital_ghosts_pos; }

	void set_color(int color_pick) const { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_pick); }
	unsigned char get_cell(const Position& cell_pos) { return board[cell_pos.get_y()][cell_pos.get_x()]; }
	void set_cell(Position& cell_pos, unsigned char c) { board[cell_pos.get_y()][cell_pos.get_x()] = c; }
    
    void init_board_from_file(const char* file_name, bool& is_valid_file);
    void handle_board_input(const unsigned char curr_char, int& curr_row, int& curr_col, int& countChars);
};


























