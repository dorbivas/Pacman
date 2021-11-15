#include "Ghosts.h"

//--------Constructors------//
Ghosts::Ghosts() {

}
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
