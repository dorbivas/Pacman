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
    6. run_silent()-TODO (almost done)


    13. exceptions -SILENT-DOR

    14. readme

    16. in the board 2  - fruit print not good(tiny problem- yarden will fix it later);

    - CONST

    - TODO PRINT SOULS PRINT *10 WHEN UNDER 10


        


*/
