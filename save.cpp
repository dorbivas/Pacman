#include "save.h"

void Save::save_steps()
{
	//pacman
	write_to_file("P:");
	write_to_file((const char)current_key);

	//Ghosts
	for (int i = 0; i < ghosts_directions.size(); i++)
	{
		write_to_file(":G");
		write_to_file(i);
		write_to_file(":");
		write_to_file(ghosts_directions[i]);
	}

	//Fruit
	write_to_file(":F:");
	if (is_fruit_dead)
		write_to_file("0");
	else
	{
		write_to_file((const char)fruit_shape);
		write_to_file(":");
		write_to_file(fruit_direction);
		write_to_file(":");
		write_to_file(fruit_pos.get_x());
		write_to_file(":");
		write_to_file(fruit_pos.get_y());
	}
	write_to_file('\n');

}