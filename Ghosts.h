#pragma once
#include "Position.h"
#include "Entity.h"
#include <queue>

enum Ghost_mode {
	Smart,
	Good,
	Novice
};
class Ghosts :public Entity
{
private:
	int mode;
	int random_steps;
	int generate_random_steps() {
		return 1 + rand() % 15;
	}
	bool novice_smart_switch;//if its true its refer to novice function(by steps)
	Position pacman_pos;
public:

	//--Constructor --//
	Ghosts() {
		novice_smart_switch = false;
		steps = 0;
		random_steps = generate_random_steps();
		shape = Shape::GHOST;
		color = Board::Color::RED;
		direction = generate_random_dir();
	}
	//--Data Members Fucns: --//
	int get_step() const { return steps; }
	int get_mode() const  { return mode; }
	bool get_novice_smart_switch() { return novice_smart_switch; }

	void set_mode(int mode) {
		this->mode = mode;
	}
	void set_mode(Ghost_mode& mode) {
		this->mode = (int)mode;
	}
	void set_pacman_pos(const Position& _pacman_pos) {
		pacman_pos = _pacman_pos;
	}
	//--Game Logic Fucns: --//
	void smart(const Position& target);

	void good_lvl(Position& target);
	bool is_invalid_place(const Position& next_pos);
	Position& handle_move();

};
