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
#define MAX_POINTS 200 //TODO check
#define PACMAN_SYMBOL 233
#define GHOST_SYMBOL 36
#define NUM_OF_GHOSTS 2

class Game {

private:
    Pacman pacman;
    Ghosts ghosts[NUM_OF_GHOSTS];
    bool pause_flag = false;
    Board board;

public:
    Pacman get_pacman() { return this->pacman; }
    void set_pacman(Pacman pacman) { this->pacman = pacman; }
    Position get_pacman_position() { return this->pacman.get_position(); }

    void Menu();
    void print_ruls();
    void game();
    void print_move(Position pos, unsigned char c);

    void move(Position dir_pos);
    void handle_move(Position next_pos);
    bool is_collided_ghost();
    bool is_invalid_place(Position next_pos);
    void handle_score(Position pacman_pos);
    bool is_teleporting(Position next_pos);
    Position teleport(Position next_pos);

    void win();
    bool lose();
    void reset_game();

    void pause();
    Position handle_key_input(unsigned char currentKey);

};