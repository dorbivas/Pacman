#pragma once
#include "Pacman.h"
#include "Board.h"
#include "Ghosts.h"

#define INITIAL_X 40
#define INITIAL_Y 12
#define WIDTH 79
#define HIGHT 24
#define OFFSET 14
#define BRICK 219
#define INSIDE_BRICK 178
#define PACMAN_SYMBOL 233
#define GHOST_SYMBOL 36
#define NUM_OF_GHOSTS 2

class Game {

private:
    Pacman pacman;
    Ghosts ghosts[NUM_OF_GHOSTS];
    bool pause_flag = false;

public:
    Pacman get_pacman() { return this->pacman; }
    void set_pacman(Pacman pacman) { this->pacman = pacman; }
    Position get_pacman_position() { return this->pacman.get_position(); }
    void Menu();
    void print_ruls();
    void game();
    void move(Position dir_pos);

    void print_move(Position pos,unsigned char c);
    bool is_collided();
    bool is_teleporting(Position curr_pos);
    void teleport(Pacman& pacman);
    void LosePring();
    void pause();
    Position handle_movement(unsigned char currentKey);

    //void boarders();
    //void board_init();
};