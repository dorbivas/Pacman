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

bool Entity::is_collided(const Position& curr_pos, const Position& next_pos, int against_direction) {
	int d1, d2, x_dif, y_dif;
	Position next_move_dir = this->move_dir();
	if (get_position() == curr_pos|| get_position() == next_pos
		/*||next_move_dir == curr_pos*/)
		return true;
	//edge cases//TODO REMOVE AFTER TESTING
	/*
	d1 = get_direction();
	d2 = against_direction;
	x_dif = next_pos.get_x() - get_position().get_x();
	y_dif = next_pos.get_y() - get_position().get_y();
	Position dif(x_dif, y_dif);

	if ((d1 == (int)Entity::Direction::UP && d2 == (int)Entity::Direction::DOWN && dif == Position(0, 1) ||
		d1 == (int)Entity::Direction::DOWN && d2 == (int)Entity::Direction::UP && dif == Position(0, -1) ||
		d1 == (int)Entity::Direction::LEFT && d2 == (int)Entity::Direction::RIGHT && dif == Position(-1, 0) ||
		d1 == (int)Entity::Direction::RIGHT && d2 == (int)Entity::Direction::LEFT && dif == Position(1, 0)))
		return true;*/
	return false;
}
bool Entity::invalid_place(const Position& next_pos)
{
	return ((board.get_cell(next_pos) == (unsigned char)Board::WALL) ||
		(next_pos.get_x() >= board.get_cols() - 1) ||
		(next_pos.get_y() >= board.get_rows() - 1) ||
		(next_pos.get_x() <= 0) ||
		(next_pos.get_x() <= 0));
}

