#pragma once
#include "Position.h"
#include "Entity.h"

#include "Game.h"
#include <queue>

#define INITAL_GHOST_X 17
#define INITAL_GHOST_Y 6
#define MAX_STEPS 20

class Ghosts:Entity
{

private:
    Position pos;
    int direction;
    int steps;
    //Shape shape = Shape::GHOST;
    //Color color = Color::LIGHTGREEN;
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
    void set_direction1(int dir) { direction = dir; } //TODO

    //--Game Logic Fucns: --//
    void rotate_direction() {
        if (direction == (int)Direction::RIGHT) { direction = (int)Direction::UP; }
        else { direction++; }
    }
    Position move_ghost();
    Entity::Direction smart(Position target);
        //bool is_collided_ghost(const Position pacman_pos, Ghosts ghosts[], int num_of_ghosts, Pacman pacman);
};
