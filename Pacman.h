#pragma once
#include "Position.h"
#include "Utility.h"
#include "Entity.h"

class Pacman :public Entity
{
private:
	int souls = STARTING_SOULS;
	int score = ZERO_POINTS;
	int total_steps = ZERO_STEPS;
	
public:
	enum pacman_table { STARTING_SOULS = 30, ZERO_POINTS = 0, ZERO_STEPS=0};
	//--Constructor --//
	Pacman() {
		shape = Shape::PACMAN;
		color = Board::Color::YELLOW;
		direction = (int)Direction::STAY;		
	};
	Pacman(int souls, int direction, Position& pos, int score);

	//--Data Members Funcs: --//
	void set_souls(int souls);
	void add_step(int step) { total_steps += step; }//TODO-BETTER NAME

	int get_souls()const;
	int get_score() const;
	int get_total_steps() { return total_steps; }

	void add_score(int new_val);
	void init_score(){score = ZERO_POINTS;}
	void init_total_steps() { total_steps = ZERO_STEPS; }
	void decrease_soul();
	bool is_invalid_place(const Position& next_pos);
	Position& handle_move() { return move_dir(); };
};
