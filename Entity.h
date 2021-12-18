#pragma once
#include "Board.h"
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
        PACMAN = 233,
        GHOST = 36,
        P = 250,
        W = 219,
        T = 176,
        S = 32
    };
 
    int get_speed() { return speed; }
    Position& get_position() { return pos; }
    int get_direction() const { return direction; }
    Board::Color get_color() const { return color; }
    Shape get_shpae() const { return shape; }

    void set_speed(int speed) { this->speed = speed; }
    void set_position(Position& pos) { this->pos = pos; }
    void set_position(int x, int y) { this->pos.set_xy(x, y); }
    void set_direction(Entity::Direction dir) { direction = (int)dir; } 
    void set_direction(int direction) { this->direction = direction; }
    void set_color(Board::Color direction) { this->color = color; }
    void set_shape(Shape direction) { this->shape = shape; }

    //TODO REMOVE THIS FUNCTIONS
    bool is_my_teleporting(const Position& next_pos) {
        return (board.get_cell(next_pos) == (unsigned char)Board::TELEPORT);
    }
    bool is_invalid_place(const Position& next_pos) {
        return (board.get_cell(next_pos) == (unsigned char)Board::WALL);
    }
    //TODO MOVE
    Position& move_dir();
    

    
protected:
    
    Position pos;
    int direction;
    int speed;
    Shape shape;
    Board::Color color;

private:
    Board board;//maybe not //TODO
    
};