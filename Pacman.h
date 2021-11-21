#pragma once
#include "Position.h"
#include "Utility.h"
#define STARTING_SOULS 30
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
	//constructors
	Pacman() {};
	Pacman(int souls, int direction, Position pos, int score);

	int get_souls()const;
	void set_souls(int souls);
	void set_score(int score);
	void add_score();
	int get_score() const;
	int get_direction() const;
	void set_direction(int direction);
	Position get_position() const;
	void set_position(Position pos);
	void set_position(int x, int y) { this->pos.set_xy(x, y); }

	void decrease_soul();
};
