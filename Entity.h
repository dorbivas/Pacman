#pragma once
#include "Board.h"
#define MAX_STEPS 20//for ghosts and fruit
class Entity {
    

public:
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STAY
    };
    
    enum  Shape {
        PACMAN = '@',
        GHOST = '$',
        P = '.',
        W = '#',
        T = 176,
        S = ' ',
        FIVE = '5',
        SIX = '6',
        SEVEN = '7',
        EIGHT = '8',
        NINE = '9'
    };
    //--Data Members Funcs: --//
    int get_speed() { return speed; }
    Position& get_position() { return pos; }
    int get_direction() const { return direction; }
    Board::Color get_color() const { return color; }
    Shape get_shape() const { return shape; }

    void set_speed(int speed) { this->speed = speed; }
    void set_position(Position& pos) { this->pos = pos; }
    void set_position(int x, int y) { this->pos.set_xy(x, y); }
    void set_direction(Entity::Direction dir) { direction = (int)dir; } 
    void set_direction(int direction) { this->direction = direction; }
    void set_board(Board& board) { this->board = board; }
    void set_shape(Entity::Shape shape) { this->shape = shape; }
 

    //--Game Logic Fucns: --//
    virtual bool is_invalid_place(const Position& next_pos) = 0;
    bool invalid_place(const Position& next_pos);//the smae for ghost and fruit but not for pacman
    Position& move_dir();
    bool is_collided(const Position& curr_pos, const Position& next_pos, int against_direction);
    virtual Position& handle_move() = 0;
    
    
protected:
    Position pos;
    int direction;
    int speed;
    Shape shape;
    Board::Color color;
    Board board;

    //only for ghosts and fruit:
    int generate_random_dir() { return rand() % 4; }
    int steps = 0;
    void rotate_direction() {
        if (direction == (int)Direction::RIGHT) { direction = (int)Direction::UP; }
        else { direction++; }}
    void novice_lvl();

private:
    
};