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
        load_game_from_files()(Does this happen automatically?)-TODO
        - reset score witout souls- DONE

    3.DONE load - in process(DOR)
    4. save:
        - Save the file to the name of the current board plus .result(strcat)- (find_file?)-TODO
        - Save the data to the file according to the format
    5. Collision between the wind and the fruit(YARDEN)-BUG- TODO
    6. run_silent()-TODO
    7. MAIN WITH CMD-TODO-DONE
    8. get curr_board_file_name-TODO
    9. NUM OF GHOSTS-LOAD resize- TEST
    10. pause in load_run- test

    11. load print not clear- todo(yarden)
    12. NEW BOARDS DOR
        


*/
