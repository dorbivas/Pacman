#include "save.h"

void Save::init_save_files() {
	string result_file_name, steps_file_name;
	result_file_name = steps_file_name = board_name = board_name.substr(0, board_name.find('.'));

	steps_file_name += ".steps";
	result_file_name += ".result";
	steps_file.open(steps_file_name,ios::trunc);

	if (!steps_file) {
		throw " steps : unable to open file. ";
	}

	result_file.open(result_file_name,ios::trunc);
	if (!result_file) {
		throw " result : unable to open file. ";
	}

}

void Save::save_steps()
{
	//pacman
	write_to_file("P:", 0);
	write_to_file((const char)current_key, 0);

	//Ghosts
	for (int i = 0; i < ghosts_directions.size(); i++)
	{
		write_to_file(":G", 0);
		write_to_file(i, 0);
		write_to_file(":", 0);
		write_to_file(ghosts_directions[i], 0);
	}

	//Fruit
	write_to_file(":F:", 0);
	if (is_fruit_dead)
		write_to_file("0", 0);
	else
	{
		write_to_file((const char)fruit_shape, 0);
		write_to_file(":", 0);
		write_to_file(fruit_direction, 0);
		write_to_file(":", 0);
		write_to_file(fruit_pos.get_x(), 0);
		write_to_file(":", 0);
		write_to_file(fruit_pos.get_y(), 0);
	}
	write_to_file('\n', 0);

}