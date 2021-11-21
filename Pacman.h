#pragma once
#include "Position.h"
#include "Utility.h"

#define STARTING_SOULS 3
#define ZERO_POINTS 0
#define INITIAL_X 39
#define INITIAL_Y 12

class Pacman
{
private:
	int souls = STARTING_SOULS;
	int direction = STAY;
	Position pos{ INITIAL_X,INITIAL_Y };
	int score = ZERO_POINTS;

public:
	//--Constructor --//
	Pacman() {};
	Pacman(int souls, int direction, Position pos, int score);

	//--Data Members Funcs: --//
	void set_souls(int souls);
	void set_score(int score);
	void set_position(Position pos);
	void set_position(int x, int y) { this->pos.set_xy(x, y); }
	void set_direction(int direction);

	int get_souls()const;
	int get_score() const;
	int get_direction() const;
	Position get_position() const;

	void add_score();
	void decrease_soul();
};
