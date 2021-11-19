#pragma once
#include "Utility.h"
#define NUM_OF_SOULS 3
#define ZERO_POINTS 0
class Pacman
{

private:
    int souls;
    int direction;
    Position pos;
    int score;

public:
    //constructors
    Pacman();
    Pacman(int souls, int direction, Position pos, int score);
    ~Pacman();

    int get_souls();
    void set_souls(int souls);
    void set_score(int score);
    void add_score();
    int get_score();
    int get_direction();
    void set_direction(int direction);
    Position get_position();
    void set_position(Position pos);
    void set_position(int x, int y) { this->pos.set_xy(x, y); }

    void decrease_soul();
};
