#include "Fruit.h"

void Fruit::generate_random_pos() {
	Position new_fruit_pos(15,4); // TODO board size
	pos = new_fruit_pos;
}
/*
void Fruit::generate_random_pos() {
	int random_index_number = (1 + rand() % (board.getOptionalIndex()));
	Position new_fruit_pos(board.getAPointForFruit(random_index_number)); 
	pos = new_fruit_pos;
}*/
void Fruit::fruit() {
	fruit_val = generate_random_fruit_val();
	shape = num_to_shape(fruit_val);
	direction = generate_random_dir();
	steps = 0;
	generate_random_pos();
}
bool Fruit::is_invalid_place(const Position& next_pos) {
	return ((board.get_cell(next_pos) == (unsigned char)Board::WALL) || (is_my_teleporting(next_pos)));
}
void Fruit::set_dir(){
	if (steps == MAX_STEPS) {
		steps = 0;
		direction = generate_random_dir();
	}
	else
		steps++;
}
Entity::Shape Fruit::num_to_shape(int val)
{
	if (val == 5)
		return Entity::Shape::FIVE;
	else if (val == 6)
		return Entity::Shape::SIX;
	else if (val == 7)
		return Entity::Shape::SEVEN;
	else if (val == 8)
		return Entity::Shape::EIGHT;
	else//9
		return Entity::Shape::NINE;

}