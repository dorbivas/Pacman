#pragma once
#include "Entity.h"

class Load {

public:
	Position& get_fruit_position() { return fruit_pos; }
	Entity::Shape get_fruit_shape() { return fruit_shape; }
	Entity::Direction* get_ghost_direction() { return ghosts_directions; }
	Entity::Direction get_fruit_direction() { return fruit_direction; }

	unsigned char get_current_key() const { return current_key; }
	bool get_fruit_is_dead() { return is_fruit_dead; }

	void set_num_of_ghosts(int _num_of_ghsots) {
		num_of_ghosts = _num_of_ghsots;
	}

	void load_line();//TODO-dor
	void init_load_file();
	void read_params_from_line(string line);
	void finish_loading();

private:
	unsigned char current_key;
	bool is_fruit_dead;
	int num_of_ghosts;

	Entity::Direction ghosts_directions[Board::MAX_GHOSTS];//TODO
	Entity::Direction fruit_direction;
	Entity::Shape fruit_shape;

	Position fruit_pos;
	ifstream steps_file;
	string board_name;
};