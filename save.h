#pragma once
#include "Entity.h"

class Save {

public:


	//--Data Members Funcs: --//

	void set_board_name(string _board_name) {
		board_name = _board_name;
	}
	void set_current_key(unsigned char _current_key) { current_key = _current_key; }

	void set_ghosts_directions(int _ghosts_directions) {
		ghosts_directions.push_back(_ghosts_directions);
	}

	void clear_direction_stuck() {
		ghosts_directions.clear();
	}

	void set_fruit_direction(int _fruit_direction) {
		fruit_direction = _fruit_direction;
	}

	void set_fruit_shape(int _fruit_shape) {
		fruit_shape = _fruit_shape;
	}

	void set_fruit_pos(Position& _fruit_pos) {
		fruit_pos = _fruit_pos;
	}

	void set_is_fruit_dead(bool _is_dead) {
		is_fruit_dead = _is_dead;
	}

	//--Game Logic Fucns: --//

	void init_save_files();

	void save_steps();

	void write_to_file(const char buffer, int select) {
		if (select == 0)
			steps_file << buffer;
		else
			result_file << buffer;
	}

	void write_to_file(const char* buffer, int select) {
		if (select == 0)
			steps_file << buffer;
		else
			result_file << buffer;
	}

	void write_to_file(const int buffer, int select) {
		if (select == 0)
			steps_file << buffer;
		else
			result_file << buffer;
	}

	void finish_saving() {
		steps_file.close();
		result_file.close();
	}

private:
	ofstream steps_file;
	ofstream result_file;
	string board_name;
	unsigned char current_key;
	vector<int> ghosts_directions;
	int fruit_direction;
	int fruit_shape;
	Position fruit_pos;
	bool is_fruit_dead = false;
};