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

    2. in the function win(): 
        - move to the next board:
        - find_files()(Does this happen automatically?)-TODO

    3.load -almost done
        TODO- get num of ghosts

    4. BUG- AFTER 3 SCREEN 

    5. BUG- Collision between the GHOSTS and the fruit

    6. run_silent()-TODO (almost done)

    7. MAIN WITH CMD

    9. pause in the load mode- check

    11. print_move in load_mode

    12. NEW BOARDS DOR

    13. exceptions

    14. readme


        


*/
