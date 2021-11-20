#include "Ghosts.h"

Position Ghosts::move_ghost(){
	Position dir_pos;
	set_direction();

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


