#pragma once
class Position {

private:
    int x, y;

public:
    Position() { x = 0; y = 0; }
    void set_xy(int _x, int _y) {x = _x; y = _y;}
    int get_x() const { return this->x; }
    int get_y() const { return this->y; }

    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool operator==(Position pos){return((pos.get_x()==x)&&(pos.get_y()==y));}
};