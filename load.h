#pragma once
#include "Entity.h"

class Load {


public:
    Position& get_fruit_position() { return fruit_pos; }
    Entity::Direction* get_ghost_direction() { return ghosts_directions; }
    unsigned char get_current_key() const { return current_key; }
    bool get_fruit_is_dead() { return fruit_is_dead; }
    Entity::Direction get_fruit_direction() { return fruit_direction; }
    int get_i() { return i; }
    
    void set_i(int new_i) { i = new_i; }
    void read_from_file() {}//TODO-dor
    /*
    every read_line: from i=0 to eof
        READ CURRENT KEY[i]
        READ GHOSTS[i][j] direction-from j=0 to max_ghosts
        read fruit is alive/dead[i]
        read fruit pos[i]

       game_logic_loop contain counter(i) -this is the num of line in the file- TODO-YARDEN
    */




private:
    unsigned char current_key;
    Entity::Direction ghosts_directions[Board::MAX_GHOSTS];
    bool fruit_is_dead;
    Position fruit_pos;
    Entity::Direction fruit_direction;
    int i = 0;
    ifstream steps_file;
};