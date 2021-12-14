#include "Ghosts.h"

Position Ghosts::move_ghost(){
	Position dir_pos;
	set_direction();

	if (direction == (int)Direction::UP)
	{
		dir_pos.set_xy(pos.get_x(), pos.get_y() + 1); 
	}
	else if (direction == (int)Direction::DOWN)
	{
		dir_pos.set_xy(pos.get_x(), pos.get_y() - 1);
	}
	else if (direction == (int)Direction::LEFT)
	{
		dir_pos.set_xy(pos.get_x()-1, pos.get_y());
	}
	else //RIGHT
	{  
		dir_pos.set_xy(pos.get_x()+1, pos.get_y());
	}

	return dir_pos;
}
/*
bool Ghosts::Entity::is_collided_ghost(const Position pacman_pos,Ghosts ghosts[],int num_of_ghosts,Pacman pacman) {
	int d1, d2, x_dif, y_dif;
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].get_position() == pacman.get_position())
			return true;

		//edge cases
		d1 = ghosts[i].get_direction();
		d2 = pacman.get_direction();
		x_dif = pacman_pos.get_x() - ghosts[i].get_position().get_x();
		y_dif = pacman_pos.get_y() - ghosts[i].get_position().get_y();
		Position dif(x_dif, y_dif);

		if ((d1 == UP && d2 == DOWN && dif == Position(0, 1) ||
			d1 == DOWN && d2 == UP && dif == Position(0, -1) ||
			d1 == LEFT && d2 == RIGHT && dif == Position(-1, 0) ||
			d1 == RIGHT && d2 == LEFT && dif == Position(1, 0)))
			return true;
	}
	return false;
}*/



