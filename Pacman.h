#pragma once
#include "Position.h"
#include "Utility.h"
#include "Entity.h"

class Pacman :public Entity
{

private:
	int souls = STARTING_SOULS;
	int score = ZERO_POINTS;
	

public:
	enum pacman_table { STARTING_SOULS = 3, ZERO_POINTS = 0, INITIAL_X = 39, INITIAL_Y = 12 };
	//--Constructor --//
	Pacman() {
		shape = Shape::PACMAN;
		color = Board::Color::YELLOW;
		direction = (int)Direction::STAY;
		//pos=board.get_inital_pacman_pos();//todo
		pos = Position(INITIAL_X, INITIAL_Y);
		
	};
	Pacman(int souls, int direction, Position& pos, int score);

	//--Data Members Funcs: --//
	void set_souls(int souls);


	int get_souls()const;
	int get_score() const;
	void add_score(int new_val);
	void decrease_soul();
	bool is_invalid_place(const Position& next_pos);
};
