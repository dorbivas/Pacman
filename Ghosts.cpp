#include "Ghosts.h"

//--------Constructors------//
Ghosts::~Ghosts() {
}

Position Ghosts::get_position() {
    return this->pos;
}

void Ghosts::set_position(Position pos) {
    this->pos = pos;
}
void Ghosts::set_position(int x, int y)
{
    this->pos.set_xy(x, y);
}
void Ghosts::set_direction(int direction){
    this->direction = direction;
}

int Ghosts::get_direction(){
    return this->direction;
}
/*void Ghosts::set_direction_near()
{
    bool flag = false;
        int pacman_x=pacman_position.get_x();
    int pacman_y=pacman_position.get_y();
    
}*/
