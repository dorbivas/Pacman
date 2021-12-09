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
    bool operator==(const Position pos){return((pos.get_x()==x)&&(pos.get_y()==y));}
}; 

/*
   
    TODO dor
    
    ***done*** (no deduction) missing a dedicated Menu class for handling user input / output - 
      menu option selection and printing instructions and messages (e.g. for Game::Menu, ::print_ruls)

    - (-1) use enum class rather than enum (enum Color, Direction); (-1) should use named constants / enum 
      instead of literals (Game::Menu, ::pause)

    - Board enum
     ***done*** delete corsair


      TODO yarden
    - (-1) logic to draw entities should be placed in entity classes and not in encompassing board 
    / game class - or altogether separated from classes which handle game logic (Game::print_move)
  
   - (-2) objects (which are not locally created) should be returned by reference to avoid 
    copy (Ghosts::get_position, Pacman::get_position); (-2) objects should be received by reference to avoid copy 
   (Ghosts::set_position, Pacman::set_position)

     class: Entity   
        Shape enum {
        @ $ '5'6'7'8'9'
        }
        Speed int
        Direction enum
        enum color
        Position curr;

      +1 Print();


    //  +1 move()
    //   +1 virtual colision(Pos1 , Pos2, Object1, Object2 )


        Kids:
        colision()


    TODO Gen
    - Finish fruit 

    - ghost LVLS
        BFS startegy

    - board File Support 

    - gibson haritage cherry les paul ++ 

    - GENERIC TELEPORT (modulo size of board)


*/