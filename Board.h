#pragma once
#include "Utility.h"
#include "Exceptions.h"

#include <fstream>
#include <vector>

using namespace std::filesystem;
using std::ifstream;
using std::vector;


class Board {

public:
    enum board_signs { P = '.', W = 219, T = 176, S = ' ', POINT = '.' , WALL = 219 , TELEPORT = 176 };
    enum MAX_SIZES { MAX_WIDTH = 80, MAX_HEIGHT = 25,MAX_GHOSTS = 2 };
    enum legend_size{ MAX_LEGEND_ROWS = 3, MAX_LEGEND_COLS = 20 };

    enum class Color {
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
    int rows, cols, max_score, num_of_ghosts, how_many_pacmans=0, how_many_legends = 0 ;

    Position inital_pacman_pos;
    Position inital_ghosts_pos[MAX_GHOSTS];
    Position legend_pos;
    vector<Position> points_valid_positions;
    Exceptions board_errors;

    /*ADDED to change ours*/
    void board_from_file(ifstream& file_input);
    void insert_single_line(int curr_col);
    void insert_teleports();
    void handle_legend();

    void make_board_empty();
    void search_points();
  
public:
    void load_board(const string& file_name);
    void print_board(const bool color_mode);
    void our_spacial_board();//EXTRA

    Position& get_inital_pacman_pos() { return inital_pacman_pos; }
    Position* get_ghost_pacman_pos() { return inital_ghosts_pos; }//EXTRA

    void set_color(int color_pick) const { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_pick); }
    unsigned char get_cell(const Position& cell_pos) { return board[cell_pos.get_y()][cell_pos.get_x()]; }
    void set_cell(Position& cell_pos, unsigned char c) { board[cell_pos.get_y()][cell_pos.get_x()] = c; }

    /*ADDED to change ours*/
    bool is_valid_move(const Position new_pos);
    int get_max_score() const { return max_score; }
    int get_num_of_ghosts() const { return num_of_ghosts; }

    int get_legend_x() const { return legend_pos.get_x(); }
    int get_legend_y() const { return legend_pos.get_y(); }

    int get_cols() const { return cols; }
    int get_rows() const { return rows; }

    int get_valid_index() const { return points_valid_positions.size(); } 
    const Position& get_rand_point(int num) const { return points_valid_positions[num]; } //TODO

    void setTotalScore() { max_score--; } 

    //void handleRead(const char read, int& row, int& col, int& countChars);// TEST TODO


};


























