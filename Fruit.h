#include "Position.h"
#include "Utility.h"
#include "Entity.h"

class Fruit:public Entity {

private:
	static const int offset = 49; //diffrence between the int and the char his represent.
	int generate_random_fruit_val() { return  5 + (rand() % 5); } //5-9 
	int fruit_val = generate_random_fruit_val();
	int generate_random_dir() { return rand() % 4; }

	char num_to_char(int fruit) { return fruit + offset; }

public:
	Fruit() {
		shape = Shape::P;
		color = Board::Color::WHITE;
		pos = generate_random_pos();
		fruit_val = generate_random_fruit_val();
		direction = generate_random_dir();
		
	}
	
	Position& generate_random_pos();
	
	void place_fruit();
	void generate_new_fruit() { Fruit(); } //TODO 
	void fruit_interaction();
	void rotate_direction() {
        if (direction == (int)Direction::RIGHT) { direction = (int)Direction::UP; }
        else { direction++; }
	int get_fruit_val()const { return fruit_val; } 
	bool is_invalid_place(const Position& next_pos);
	void set_dir();

};