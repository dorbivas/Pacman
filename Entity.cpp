#include "Entity.h"

Position& Entity::move_dir() {
	Position new_dir(pos.get_x(), pos.get_y());
	if (direction == (int)Direction::UP)
	{
		new_dir.set_xy(pos.get_x(), pos.get_y()-1);
	}
	else if (direction == (int)Direction::DOWN)
	{
		new_dir.set_xy(pos.get_x(), pos.get_y() + 1);
	}
	else if (direction == (int)Direction::LEFT)
	{
		new_dir.set_xy(pos.get_x()-1, pos.get_y());

	}
	else if (direction == (int)Direction::RIGHT)
	{
		new_dir.set_xy(pos.get_x() + 1, pos.get_y());
	}//else ->stay
	return new_dir;
}

