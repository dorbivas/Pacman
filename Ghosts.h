#pragma once
#include "Utility.h"

#define INITAL_GHOST_X 17
#define INITAL_GHOST_Y 6
#define MAX_STEPS 20

class Ghosts
{

private:
    Position pos;
    int direction;
    int steps;//steps counter
    int generate_random_dir() { return rand() % 4; }

public:
    //constructors
    Ghosts(){
        steps = 0;
        direction = generate_random_dir();
        pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
    }
    ~Ghosts() {};

    Position get_position() { return pos; }
    int get_step() { return steps; }
    void set_position(Position Pos) { this->pos = Pos; }
    void set_position(int x, int y) { pos.set_xy(x, y); }
    int get_direction() { return direction; } const

    void set_direction() {
        if (steps == MAX_STEPS) { steps = 0; direction = generate_random_dir(); }
        else { steps++; }
    }
    void rotate_direction() {//TODO STATIC
        if (direction == RIGHT) { direction = UP; }
        else { direction++; }
    }
    Position move_ghost();
};
