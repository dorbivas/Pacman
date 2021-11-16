#pragma once
#include "Pacman.h"
class Ghosts
{

private:
    Position pos;
    int direction;

public:
    //constructors
    Ghosts();
    ~Ghosts();

    Position get_position();
    void set_position(Position pos);
    void set_position(int x, int y);
    int get_direction();
    void set_direction(int direction);
   // Position get_pacman_position(Pacman pacman);
    void set_direction_near();

};
