#pragma once
#include "Position.h"
#include "Utility.h"
#include "Entity.h"



class Pacman :public Entity
{
public:
	enum pacman_table { STARTING_SOULS = 3, ZERO_POINTS = 0, INITIAL_X = 17, INITIAL_Y = 4 };

private:
	int souls = STARTING_SOULS;
	int score = ZERO_POINTS;
	

public:

	//--Constructor --//
	Pacman() {
		shape = Shape::PACMAN;
		color = Board::Color::YELLOW;
		direction = (int)Direction::STAY;
		pos.set_xy( INITIAL_X,INITIAL_Y );
	};
	Pacman(int souls, int direction, Position& pos, int score);

	//--Data Members Funcs: --//
	void set_souls(int souls);
	void set_score(int score);

	int get_souls()const;
	int get_score() const;
	void add_score();
	void decrease_soul();
};
