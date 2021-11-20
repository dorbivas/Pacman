#pragma once
//#include "Utility.h"
//TODO valid check
class Position {

private:
    int x, y;

public:
    Position() {}
    void set_xy(int _x, int _y) {x = _x; y = _y;}
    int get_x() const { return this->x; }
    int get_y() const { return this->y; }

    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
    //Position& operator=(Position pos){return((pos.get_x()==x)&&(pos.get_y()==y));}

};