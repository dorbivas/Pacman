#pragma once
class Position {

private:
    int x, y;

public:
    //--Constructor --//
    Position() { x = 0; y = 0; }
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
    //--Data Members Fucns: --//
    void set_xy(int _x, int _y) {x = _x; y = _y;}
    int get_x() const { return this->x; }
    int get_y() const { return this->y; }

    //--Game Logic Fucns: --//
    bool operator==(const Position& pos){return((pos.get_x()==x)&&(pos.get_y()==y));}

}; 
