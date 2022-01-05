#include "Fruit.h"

void Fruit::generate_random_pos() {
	int valid_position_size = board.get_valid_index();
	int random_index_number = (0 + rand() % valid_position_size);
	Position new_fruit_pos(board.get_rand_point(random_index_number));
	pos = new_fruit_pos;
}
void Fruit::fruit() {
	fruit_val = generate_random_fruit_val();
	shape = num_to_shape(fruit_val);
	direction = generate_random_dir();
	steps = 0;
	generate_random_pos();
}
bool Fruit::is_invalid_place(const Position& next_pos) {
	return invalid_place(next_pos);
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
	else //9
		return Entity::Shape::NINE;

}
Position& Fruit::handle_move()
{
	novice_lvl();
	Position next_pos = move_dir();

	while (is_invalid_place(next_pos) || !board.is_valid_move(next_pos))
	{
		rotate_direction();
		novice_lvl();
		next_pos = move_dir();
	}
	return next_pos;
}