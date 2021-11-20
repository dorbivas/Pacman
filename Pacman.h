#pragma once
#include "Utility.h"
#define NUM_OF_SOULS 3
#define ZERO_POINTS 0
#define INITIAL_X 39
#define INITIAL_Y 12
class Pacman
{
private:
	int souls = 3;
	int direction = STAY;
	Position pos{ INITIAL_X,INITIAL_Y };
	int score = ZERO_POINTS;

public:
	//constructors
	Pacman();
	Pacman(int souls, int direction, Position pos, int score);
	//~Pacman();

	int get_souls()const;
	void set_souls(int souls);
	void set_score(int score);
	void add_score();//TODO STATIC
	int get_score() const;
	int get_direction();
	void set_direction(int direction);
	Position get_position();
	void set_position(Position pos);
	void set_position(int x, int y) { this->pos.set_xy(x, y); }

	void decrease_soul();
};
