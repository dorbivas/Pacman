#pragma once
#include "Entity.h"

class Load {

public:

	//--Data Members Funcs: --//

	Position& get_fruit_position() { return fruit_pos; }

	int get_fruit_shape() { return fruit_shape; }

	vector<int> get_ghost_direction() { return ghosts_directions; }

	Entity::Direction get_fruit_direction() { return fruit_direction; }

	unsigned char get_current_key() const { return current_key; }

	bool get_fruit_is_dead() { return is_fruit_dead; }

	int get_num_of_steps() { return num_of_steps; }

	int get_result_steps() { return result_steps; }

	int get_pacman_status() { return pacman_status; }

	void set_num_of_ghosts(int _num_of_ghsots) {
		num_of_ghosts = _num_of_ghsots;
	}
	void set_board_name(string _board_name) {
		board_name = _board_name;
	}

	//--Game Logic Fucns: --//

	void read_line_from_result(string line);

	void load_line(int select);

	void init_load_files();

	void read_params_from_steps(string line);

	void finish_loading();

private:
	unsigned char current_key;
	bool is_fruit_dead;
	int num_of_ghosts = Board::MAX_GHOSTS;
	int num_of_steps = 30;

	int result_steps = 0;
	int pacman_status = 0;

	vector<int> ghosts_directions;
	Entity::Direction fruit_direction;
	int fruit_shape;

	ifstream steps_file;
	ifstream result_file;

	Position fruit_pos;
	string board_name;
};