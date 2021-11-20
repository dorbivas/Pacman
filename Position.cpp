#include "Position.h"
Position::Position(){}
void Position:: set_xy(int x, int y){
    set_x(x);
    set_y(y);
}
void Position::set_x(int x){
    this->x = x;
}
void Position::set_y(int y){
    this->y = y;
}