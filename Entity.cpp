#include "Entity.h"

Position& Entity::move_dir() {
	int dir_x = 0, dir_y = 0;
	Position new_dir(dir_x, dir_y);
	if (direction == (int)Direction::UP)
	{
		new_dir.set_xy(dir_x, dir_y-1);
	}
	else if (direction == (int)Direction::DOWN)
	{
		new_dir.set_xy(dir_x, dir_y+1);
	}
	else if (direction == (int)Direction::LEFT)
	{
		new_dir.set_xy(dir_x-1, dir_y);

	}
	else if (direction == (int)Direction::RIGHT)
	{
		new_dir.set_xy(dir_x + 1, dir_y);
	}//else ->stay
	return new_dir;
}

