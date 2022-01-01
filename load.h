#pragma once
#include "Entity.h"



class Load {


public:
    Position& get_fruit_position() { return fruit_pos; }
    Entity::Direction* get_ghost_direction() { return ghosts_directions; }
    unsigned char get_current_key() const { return current_key; }
    bool get_fruit_is_dead() { return fruit_is_dead; }
    Entity::Direction get_fruit_direction() { return fruit_direction; }
    
    void read_from_file() {}//TODO-dor

    void split(string line);




private:
    unsigned char current_key;
    Entity::Direction ghosts_directions[Board::MAX_GHOSTS];
    bool fruit_is_dead;
    Position fruit_pos;
    Entity::Direction fruit_direction;
    ifstream steps_file;
};