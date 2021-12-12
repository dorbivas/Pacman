#pragma once
#include "Board.h"
//#include "Ghosts.h"
//#include "Pacman.h"
class Entity {
    

public:



    //  +1 move()
    //   +1 virtual colision(Pos1 , Pos2, Object1, Object2 )


//Kids:
    //colision()

    
    enum direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STAY
    };
    enum Color {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHTGREY,
        DARKGREY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE
    };


    int get_speed() { return speed; }
    void set_speed(int speed) { this->speed = speed; }
    Position& get_position() { return curr; }
    void print_move(const Position pos, Shape shape, bool color_mode, int score, int souls) const;
    void display_score_souls(int score, int souls, bool color_mode) const;
   // virtual bool is_collided_ghost(const Position pacman_pos,Ghosts ghosts[],int num_of_ghosts,Pacman pacman);
protected:
    Board board;

private:
    int speed;
    Position curr;
    

};