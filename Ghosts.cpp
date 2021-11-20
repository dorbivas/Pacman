#include "Ghosts.h"

//--------Constructors------//

Ghosts::Ghosts(){
    direction = rand() % 4;
    pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
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
void Ghosts::set_direction(int direction){
    this->direction = direction;
}

int Ghosts::get_direction(){
    return this->direction;
}

Position Ghosts::move_ghost(){
	Position dir_pos;
	direction = rand() % 4;

	if (direction == UP)
	{
		dir_pos.set_xy(pos.get_x(), pos.get_y() + 1); 
	}
	else if (direction == DOWN)
	{
		dir_pos.set_xy(pos.get_x(), pos.get_y() - 1);
	}
	else if (direction == LEFT)
	{
		dir_pos.set_xy(pos.get_x()-1, pos.get_y());
	}
	else
	{  
		dir_pos.set_xy(pos.get_x()+1, pos.get_y());
	}
	return dir_pos;
}


