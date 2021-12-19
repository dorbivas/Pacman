#pragma once
#include "Position.h"
#include "Entity.h"

#include <queue>
#define MAX_STEPS 20

enum Ghost_mode {
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
    bool novice_smart_switch;//if its true its refer to novice function(by steps)

public:
   
    //--Constructor --//
    Ghosts(){
        novice_smart_switch = false;
        steps = 0;
        shape = Shape::GHOST;
        color = Board::Color::RED;
        direction = generate_random_dir();
    }
     //--Data Members Fucns: --//
    int get_step() const { return steps; }
    int get_mode() { return mode; }
    bool get_novice_smart_switch() { return novice_smart_switch; }

    void set_mode(int mode) {
        this->mode = mode;
    }
    void set_mode(Ghost_mode mode) {
        this->mode = (int)mode;
    }
    //--Game Logic Fucns: --//
    void rotate_direction() {
        if (direction == (int)Direction::RIGHT) { direction = (int)Direction::UP; }
        else { direction++; }
    }
    void novice_lvl_ghost();
    void smart(const Position& target);

    void good_lvl_ghost(Position target);
    bool is_invalid_place(const Position& next_pos);


};
