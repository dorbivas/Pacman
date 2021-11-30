#include "Fruit.h"

Fruit::Fruit() {

}


Position Fruit::generate_random_pos() {
	Position new_fruit_pos((1 + rand() % 80), (1 + rand() % 25)); // TODO board size
	return new_fruit_pos;
}

void Fruit::fruit_interaction() { //move to game
	
}