#pragma once
#include "Entity.h"
#define MAX_STEPS 20
class Fruit:public Entity{ 

private:
	static const int offset = 49; //diffrence between the int and the char his represent.
	int fruit_val;
	int generate_random_dir() { return rand() % 4; }
	int steps;

	char num_to_char(int fruit) { return fruit + offset; }

public:
	Fruit() {
		shape = Shape::NINE;
		color = Board::Color::WHITE;
		pos = generate_random_pos();
		fruit_val = generate_random_fruit_val();
		direction = generate_random_dir();
		steps = 0;
		
	}
	
	Position& generate_random_pos();
	int generate_random_fruit_val() { return  5 + (rand() % 5); } //5-9 
	void place_fruit();
	//void generate_new_fruit() { Fruit(); } //TODO 
	void fruit_interaction();
	void rotate_direction() {
		if (direction == (int)Direction::RIGHT)
			direction = (int)Direction::UP;
		else 
			direction++; 
	}
	int get_fruit_val()const{ return fruit_val; } 
	bool is_invalid_place(const Position& next_pos);
	void set_dir();

};