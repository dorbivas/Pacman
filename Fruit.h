#pragma once
#include "Entity.h"
#define MAX_STEPS 20
class Fruit:public Entity{ 

private:
	int fruit_val;
	int generate_random_dir() { return rand() % 4; }
	int steps;

	

public:
	//--Constructor --//
	Fruit() {
		color = Board::Color::WHITE;
		speed = 1;//TODO
	}


	//--Game Logic Fucns: --//
	void fruit();
	void generate_random_pos();
	int generate_random_fruit_val() { return  5 + (rand() % 5); } //5-9 
	
	//void fruit_interaction();
	void rotate_direction() {
		if (direction == (int)Direction::RIGHT)
			direction = (int)Direction::UP;
		else 
			direction++; 
	}
	bool is_invalid_place(const Position& next_pos);
	void set_dir();
	//--Data Members Funcs: --//
	int get_fruit_val()const{ return fruit_val; } 
	Shape num_to_shape(int val);

};