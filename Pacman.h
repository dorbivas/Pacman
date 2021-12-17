#pragma once
#include "Position.h"

#include "Utility.h"
#include "Entity.h"



class Pacman :Entity
{
public:
	enum pacman_table { STARTING_SOULS = 3, ZERO_POINTS = 0, INITIAL_X = 39, INITIAL_Y = 12 };

private:
	int souls = STARTING_SOULS;
	int direction = (int)Direction::STAY;
	//Shape shape = Shape::PACMAN;
	//Color color = Color::LIGHTGREEN;
	Position pos{ INITIAL_X,INITIAL_Y };
	int score = ZERO_POINTS;


public:

	//--Constructor --//
	Pacman() {};
	Pacman(int souls, int direction, Position& pos, int score);

	//--Data Members Funcs: --//
	void set_souls(int souls);
	void set_score(int score);
	void set_position(Position& pos) { this->pos = pos; }
	void set_position(int x, int y) { this->pos.set_xy(x, y); }
	void set_direction(int direction);

	int get_souls()const;
	int get_score() const;
	int get_direction() const;

	Position& get_position() { return pos; }
	void add_score();
	void decrease_soul();
};
