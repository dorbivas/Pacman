#pragma once
#include "Pacman.h"
#include "Board.h"
#include "Ghosts.h"

#define MAX_POINTS 629 
#define PACMAN_ICON 233 
#define GHOST_ICON 36
#define NUM_OF_GHOSTS 2

/*teleports order is sync with the board from left to right */
enum teleports {
    TP_NORTH1_TOP_X = 21,
    TP_NORTH1_TOP_Y = 1 ,
    TP_NORTH2_TOP_X = 53,
    TP_NORTH2_TOP_Y = 1 ,

    TP_NORTH1_BOT_X = 21,
    TP_NORTH1_BOT_Y = 22,
    TP_NORTH2_BOT_X = 53,
    TP_NORTH2_BOT_Y = 22,

    TP_EAST_BOT_X = 79,
    TP_EAST_BOT_Y = 21,
    TP_WEST_TOP_X = 1 ,
    TP_WEST_TOP_Y = 6
};

class Game {

private:
    Pacman pacman;
    Ghosts ghosts[NUM_OF_GHOSTS];
    Board board;

    bool pause_flag = false;
    bool color_mode = true;
    bool loop_flag = false;

public:
    Pacman get_pacman() { return this->pacman; } // TODO need?
    void set_pacman(Pacman pacman) { this->pacman = pacman; }
    Position get_pacman_position() { return this->pacman.get_position(); }
    void set_color_mode(bool color_mode_switch) { this->color_mode = color_mode_switch; }

    //--Game Logic Fucns: --//
    void pacman_move(Position dir_pos);
    Position handle_ghost_move(Position curr_pos,Position dir_pos);
    void init_ghosts();
    void handle_move(Position next_pos);
    bool is_collided_ghost();
    bool is_invalid_place(Position next_pos);
    void handle_score(Position pacman_pos);
    bool is_teleporting(Position next_pos);
    Position teleport(Position next_pos);
    void pause();
    Position handle_key_input(unsigned char currentKey);

    //--Display Fucns: --//
    void Menu();
    void print_ruls();
    void game();
    void print_move(Position pos, unsigned char c);
    void display_score_souls();

    void win();
    void lose();
    void reset_game();


};