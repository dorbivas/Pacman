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

    1.DONE SPEED(DOR)
        BUG in collision sometimes(yarden+dor)

    3.load -almost done
        TODO- get num of ghosts(yarden +dor)

    6. run_silent()-TODO (almost done)

    9. pause in the load mode- check -yarden //no


    13. exceptions -almost done

    14. readme

    15. win - wrong input to fix

    16. in the board 2  - fruit print not good(tiny problem- yarden will fix it later);


        


*/
