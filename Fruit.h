#pragma once
#include "Entity.h"
class Fruit:public Entity{ 

private:
	int fruit_val;

public:
	//--Constructor --//
	Fruit() {
		color = Board::Color::WHITE;
	}
	~Fruit(){}


	//--Game Logic Fucns: --//
	void fruit();
	void generate_random_pos();
	int generate_random_fruit_val() { return  5 + (rand() % 5); } //5-9 
	bool is_invalid_place(const Position& next_pos);
	Position& handle_move();

	//--Data Members Funcs: --//

	int get_fruit_val()const{ return fruit_val; } 
	Shape num_to_shape(int val);
	void set_fruit_val(int val) { fruit_val = val; }

};