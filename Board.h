#pragma once
#include "Utility.h"
#include <fstream>
#include <vector>

using namespace std::filesystem;
using std::ifstream;
using std::vector;



class Board {

public:
    enum board_signs { P = 250, W = 219, T = 176, S = 32, POINT = 250, WALL = 219, TELEPORT = 176 };
    enum board_size { MAX_WIDTH = 80, MAX_HEIGHT = 25, };
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
    int rows, cols, max_score, num_of_ghosts;



    /*ADDED to change ours*/
    void board_from_file(ifstream& file_input);
    void insert_single_line(int curr_col);
    void insert_teleports();
    void handle_legend(const Position& legend_pos);
    void make_board_empty();
    void search_points();
   


public:
    //todo MAYBE private ?
    Position inital_pacman_pos;
    Position* inital_ghosts_pos;
    Position legend_pos;
    vector<Position> points_valid_positions;

    void load_board(const string& file_name);
    void print_board(const bool color_mode);
    void our_spacial_board();

    Position& get_inital_pacman_pos() { return inital_pacman_pos; }
    //Positon& get_ghost_pacman_pos() { return inital_ghosts_pos; }//TODO

    void set_color(int color_pick) const { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_pick); }
    unsigned char get_cell(const Position& cell_pos) { return board[cell_pos.get_y()][cell_pos.get_x()]; }
    void set_cell(Position& cell_pos, unsigned char c) { board[cell_pos.get_y()][cell_pos.get_x()] = c; }

    /*ADDED to change ours*/
    bool is_valid_move(const Position new_pos);
    int get_max_score() const { return max_score; }
    int get_num_of_ghosts() const { return num_of_ghosts; }

    int get_legend_x() const { return legend_pos.get_x(); }
    int get_legend_y() const { return legend_pos.get_y(); }

    unsigned int get_cols() const { return cols; }
    unsigned int get_rows() const { return rows; }

    int getOptionalIndex() const { return points_valid_positions.size(); } // TODO ?
    const Position& getAPointForFruit(int num) const { return points_valid_positions[num]; }

    void setTotalScore() { max_score--; } // TODO



};


























