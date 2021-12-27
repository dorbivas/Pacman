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

/*
    TODO:

    1. SPEED
    2. IMMEDIATE SYNCHRONIZATION OF THE BOARD WITH THE OTHER CLASSES
       ALLOWS OPTIMAL UTILIZATION OF POLYMOPHISM AND INGERITANCE-DISCUSS IT
    3. COLLISION
    4. FURIT- TIMER FOR DISAPPPERED
    5. RECORD
    6. TRY CATCH-DOR
    7.
    8.
    9.
    10.
    11.
    12.


*/
