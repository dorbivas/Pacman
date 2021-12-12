#pragma once
#include "Position.h"
#include "Entity.h"
#define INITAL_GHOST_X 17
#define INITAL_GHOST_Y 6
#define MAX_STEPS 20

class Ghosts:Entity
{

private:
    Position pos;
    int direction;
    int steps;
    int generate_random_dir() { return rand() % 4; }

public:
    //--Constructor --//
    Ghosts(){
        steps = 0;
        direction = generate_random_dir();
        pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
    }
     //--Data Members Fucns: --//
    Position& get_position() { return pos; }
    int get_step() const { return steps; }
    int get_direction() const { return direction; }

    void set_position(Position& Pos) { pos = Pos; }
    void set_position(int x, int y) { pos.set_xy(x, y); }
    void set_direction() {
        if (steps == MAX_STEPS) { steps = 0; direction = generate_random_dir(); }
        else { steps++; }
    }

    //--Game Logic Fucns: --//
    void rotate_direction() {
        if (direction == RIGHT) { direction = UP; }
        else { direction++; }
    }
    Position move_ghost();
   //bool is_collided_ghost(const Position pacman_pos, Ghosts ghosts[], int num_of_ghosts, Pacman pacman);
};
