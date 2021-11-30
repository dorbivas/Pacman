
#include "Position.h"
#include "Utility.h"


class Fruit {

private:
	static const int offset = 49; //diffrence between the int and the char his represent.
	int generate_random_fruit_val() { return  5 + (rand() % 5); } //5-9 
	int fruit_val = generate_random_fruit_val();
	Position fruit_pos;

	char num_to_char(int fruit) { return fruit + offset; }

	

public:
	Fruit() {
		fruit_pos = generate_random_pos();
		fruit_val = generate_random_fruit_val();
		
	}
	Fruit(Position new_pos) {

		fruit_pos = generate_random_pos();

	}
	Position generate_random_pos();
	
	void place_fruit();
	void generate_new_fruit() { Fruit(); } //TODO 
	void fruit_interaction();

	int get_fruit_val()const { return this->fruit_val; } 
	Position get_fruit_pos()const { return this->fruit_pos; }

};