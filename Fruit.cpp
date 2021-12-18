#include "Fruit.h"

Position& Fruit::generate_random_pos() {
	Position new_fruit_pos((1 + rand() % board.MAX_WIDTH), (1 + rand() % board.MAX_HEIGHT)); // TODO board size
	while(is_invalid_place(new_fruit_pos))
		Position new_fruit_pos((1 + rand() % board.MAX_WIDTH), (1 + rand() % board.MAX_HEIGHT)); // TODO board size
	return new_fruit_pos;
}

void Fruit::fruit_interaction() { //move to game
	
}
bool Fruit::is_invalid_place(const Position& next_pos) {
	return ((board.get_cell(next_pos) == (unsigned char)Board::WALL) || (is_my_teleporting(next_pos)));
}
void Point::set_dir(){
	if (steps == MAX_STEPS) {
		steps = 0;
		direction = generate_random_dir();
	}
	else
		steps++;
}
