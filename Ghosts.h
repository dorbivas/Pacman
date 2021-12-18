#pragma once
#include "Position.h"
#include "Entity.h"

//#include "Game.h"
#include <queue>

#define INITAL_GHOST_X 17
#define INITAL_GHOST_Y 6
#define MAX_STEPS 20

enum Ghost_mode {//TODO
    Smart,
    Good,
    Novice
};
class Ghosts:public Entity
{

private:
    int mode;
    int steps;
    int generate_random_dir() { return rand() % 4; }

public:
   
    //--Constructor --//
    Ghosts(){
        steps = 0;
        shape = Shape::GHOST;
        color = Board::Color::RED;
        direction = generate_random_dir();
        pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
    }
     //--Data Members Fucns: --//
    int get_step() const { return steps; }
    int get_mode() { return mode; }

    void set_mode(int mode) {
        this->mode = mode;
    }
    //--Game Logic Fucns: --//
    void rotate_direction() {
        if (direction == (int)Direction::RIGHT) { direction = (int)Direction::UP; }
        else { direction++; }
    }
    void novice_lvl_ghost();
    void smart(Position target);
    bool is_valid_bfs(Position new_pos);

    void good_lvl_ghost(Position target);
        //bool is_collided_ghost(const Position pacman_pos, Ghosts ghosts[], int num_of_ghosts, Pacman pacman);
};
