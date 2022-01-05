#include "Game.h"
extern bool IS_SILENT;

Game::Game() {
	srand(time(NULL)); //start generating rand numbers for ghost dir
}

void Game::game() {
	find_files();
	if (save_mode && board_level == 0)
		init_number_of_files();

	load_game_from_files();
	Position next_pos;
	unsigned char temp;
	current_key = _kbhit();

	while (!is_valid_key(current_key) || current_key == ESC)
		current_key = _getch();
	temp = current_key;

	while (!loop_flag)
	{
		Sleep(SPEED);
		if (_kbhit())
			current_key = _getch();

		if (is_valid_key(current_key))
		{
			handle_key_input(current_key);
			if (pause_flag)
			{
				current_key = temp;
				pause_flag = false;
			}
			save.set_current_key(current_key);

			next_pos = pacman.move_dir();

			if (hold_move % 2 == 0)
			{
				save.clear_direction_stuck();
				handle_ghost_move();
				if (!is_fruit_dead)
					handle_fruit_move();
				else
				{
					if (save_mode)
						save.set_is_fruit_dead(true);

					if (pacman.get_total_steps() == 150)
					{
						is_fruit_dead = false;
						if (save_mode)
							save.set_is_fruit_dead(false);

						fruit = Fruit();
						fruit.set_board(board);
						fruit.fruit();
					}
				}
			}
			else
			{
				for (int i = 0; i < board.get_num_of_ghosts(); i++)
				{
					if (ghosts[i].is_collided(pacman.get_position(), next_pos, pacman.get_direction()))
					{
						handle_collision();
						ghosts[i].set_position(board.get_ghost_pacman_pos()[i].get_x(), board.get_ghost_pacman_pos()[i].get_y());
					}
				}
			}

			handle_pacman_move();

			if (save_mode)
				save.save_steps();
			hold_move++;
			handle_score();
			temp = current_key;
		}
		else
		{
			if (current_key != '9')
				current_key = temp;
			else
				loop_flag = true;//stop the loop
		}

	}

	if (save_mode)
	{
		save.write_to_file(pacman.get_total_steps(), 0);
		save.write_to_file(pacman.get_total_steps(), 1);
		save.write_to_file(":", 1);
		save.write_to_file(1, 1);
		save.write_to_file('\n', 1);

		save.finish_saving();
	}

	system("cls");

	return;
}

//--Game Logic Fucns: --//
void Game::handle_pacman_move() {
	Position curr_pos = pacman.get_position();
	int to_add = 0;
	Position next_fruit_pos;
	Position next_pos = pacman.handle_move();


	//next position
	if (pacman.is_invalid_place(next_pos))
	{
		print_move(curr_pos, pacman.get_shape());
		pacman.add_step(1);
		return;
	}

	next_pos = handle_teleport(next_pos);

	if (board.get_cell(next_pos) == Entity::Shape::P)
		to_add = 1;


	next_fruit_pos = fruit.move_dir();

	//colision with fruit
	if (!is_fruit_dead && (pacman.is_collided(fruit.get_position(), next_fruit_pos, fruit.get_direction())
		|| board.get_cell(fruit.get_position()) == Entity::Shape::PACMAN
		|| board.get_cell(curr_pos) == fruit.get_shape()
		|| board.get_cell(next_pos) == fruit.get_shape()))
	{

		if ((pacman.get_total_steps() - last_step_fruit_collision != 1) || last_step_fruit_collision == 0)
			to_add += fruit.get_fruit_val();

		last_step_fruit_collision = pacman.get_total_steps();
		print_move(fruit.get_position(), Entity::Shape::S);

		if (!load_mode && !IS_SILENT)
			fruit.fruit();
	}
	pacman.add_score(to_add);

	board.set_cell(curr_pos, Entity::Shape::S);
	print_move(curr_pos, Entity::Shape::S);

	pacman.set_position(next_pos);
	print_move(next_pos, Entity::Shape::PACMAN);
	board.set_cell(next_pos, Entity::Shape::PACMAN);

	pacman.add_step(1);
}

void Game::handle_ghost_move() {
	Position curr_pos, next_pos, next_fruit_pos, next_pacman_pos;
	int i;

	for (i = 0; i < board.get_num_of_ghosts(); i++)
	{
		ghosts[i].set_pacman_pos(pacman.get_position());
		curr_pos = ghosts[i].get_position();

		if (load_mode || IS_SILENT)
			next_pos = ghosts[i].move_dir();
		else
		{
			next_pos = ghosts[i].handle_move();
			if (save_mode)
				save.set_ghosts_directions(ghosts[i].get_direction());
		}

		//curr positon 
		if (board.get_cell(curr_pos) == Entity::Shape::P)
			print_move(curr_pos, Entity::Shape::P);

		else
		{
			print_move(curr_pos, Entity::Shape::S);
			board.set_cell(curr_pos, Entity::Shape::S);
		}

		if (!is_fruit_dead)
		{
			next_fruit_pos = fruit.move_dir();
			if (ghosts[i].is_collided(fruit.get_position(), next_fruit_pos, fruit.get_direction()))
			{
				if (!load_mode && !IS_SILENT)
					fruit.fruit();

				print_move(fruit.get_position(), Entity::Shape::S);
			}
		}

		next_pacman_pos = pacman.move_dir();
		if (ghosts[i].is_collided(pacman.get_position(), next_pacman_pos, pacman.get_direction()))
		{
			handle_collision();
			current_key = stay_lower_case;

			ghosts[i].set_position(board.get_ghost_pacman_pos()[i].get_x(), board.get_ghost_pacman_pos()[i].get_y());
		}
		else
		{
			//next position
			if (!ghosts[i].is_invalid_place(next_pos))
			{
				ghosts[i].set_position(next_pos);
				print_move(next_pos, Entity::Shape::GHOST);
			}
		}
	}
}

void Game::handle_fruit_move() {
	Position curr_pos, next_pos;
	curr_pos = fruit.get_position();
	next_pos = fruit.move_dir();

	if (board.get_cell(curr_pos) == Entity::Shape::P)
		print_move(curr_pos, Entity::Shape::P);

	else
	{
		print_move(curr_pos, Entity::Shape::S);
		board.set_cell(curr_pos, Entity::Shape::S);
	}

	if (pacman.get_total_steps() == 100)//fruit disappeard
	{
		if (board.get_cell(next_pos) == Entity::Shape::P)
			print_move(next_pos, Entity::Shape::P);
		else
		{
			if (!fruit.is_invalid_place(next_pos))
			{
				print_move(next_pos, Entity::Shape::S);
				board.set_cell(curr_pos, Entity::Shape::S);
			}
		}
		is_fruit_dead = true;
		fruit.~Fruit();
	}
	else
	{
		if (load_mode || IS_SILENT)
			next_pos = fruit.move_dir();
		else
			next_pos = fruit.handle_move();

		fruit.set_position(next_pos);
		print_move(fruit.get_position(), fruit.get_shape());

		if (save_mode)
		{
			save.set_fruit_shape(fruit.get_shape());
			save.set_fruit_direction(fruit.get_direction());
			save.set_fruit_pos(curr_pos);
		}
	}
}

void Game::init_number_of_files()
{
	for (int i = 0; i < file_names.size(); i++)
	{
		ofstream tmp_res_file, tmp_steps_file;
		string tmp_res, tmp_steps;
		tmp_res = tmp_steps = file_names[i].substr(0, file_names[i].find('.'));

		tmp_steps += ".steps";
		tmp_res += ".result";
		tmp_res_file.open(tmp_res, ios::trunc);
		tmp_steps_file.open(tmp_steps, ios::trunc);
	}
}

void Game::checking_loading(int pacman_status)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
	load.load_line(1);
	if (pacman.get_total_steps() != load.get_result_steps())
		throw " steps does not correspond to the steps file  ";

	if (load.get_pacman_status() != pacman_status)
		throw " pacman is alive the result file does not match to steps file ";
}


void Game::handle_collision() {

	pacman.decrease_soul();
	print_move(pacman.get_position(), Entity::Shape::S);
	pacman.set_position((int)board.get_inital_pacman_pos().get_x(), (int)board.get_inital_pacman_pos().get_y());
	pacman.set_direction((int)Entity::Direction::STAY);;

	if (save_mode)
	{
		save.write_to_file(pacman.get_total_steps(), 1);
		save.write_to_file(":", 1);
		save.write_to_file(0, 1);
		save.write_to_file('\n', 1);
	}
	if (load_mode || IS_SILENT)
		checking_loading(0);

	


	if (pacman.get_souls() <= 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
		lose();
	}
}

void Game::handle_score() {
	if (pacman.get_score() >= MAX_POINTS)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
		win();
	}
}

Position& Game::handle_teleport(Position& next_pos)
{
	int pacman_direction = pacman.get_direction();
	int last_col = board.get_cols();
	int last_row = board.get_rows();

	if (next_pos.get_x() == last_col - 1 && pacman_direction == 3)
	{
		next_pos.set_xy(1, next_pos.get_y());
		pacman.set_direction((int)Entity::Direction::RIGHT);
	}
	if (next_pos.get_x() == 0 && pacman_direction == 2)
	{
		next_pos.set_xy(last_col - 2, next_pos.get_y());
		pacman.set_direction((int)Entity::Direction::LEFT);
	}
	if (next_pos.get_y() == last_row - 1 && pacman_direction == 1)
	{
		next_pos.set_xy(next_pos.get_x(), 1);
		pacman.set_direction((int)Entity::Direction::DOWN);
	}
	if (next_pos.get_y() == 0 && pacman_direction == 0)
	{
		next_pos.set_xy(next_pos.get_x(), last_row - 2);
		pacman.set_direction((int)Entity::Direction::UP);
	}
	return next_pos;
}

void Game::print_move(const Position pos, Entity::Shape shape) {
	display_score_souls();
	if (color_mode)
	{
		if (shape == Entity::Shape::P)
			board.set_color((int)Board::Color::WHITE);
		else if (shape == Entity::Shape::PACMAN)
			board.set_color((int)pacman.get_color());
		else if (shape == Entity::FIVE || shape == Entity::SIX ||
			shape == Entity::SEVEN || shape == Entity::EIGHT || shape == Entity::NINE)
			board.set_color((int)Board::Color::MAGENTA);
		else // (c == GHOST_ICON)
			board.set_color((int)ghosts[0].get_color());
	}
	goto_xy(pos.get_x(), pos.get_y());
	if (shape != 0)
		my_print(unsigned char(shape));
}

void Game::display_score_souls() const {

	goto_xy(board.get_legend_x(), board.get_legend_y());
	if (color_mode)
		board.set_color((int)Board::Color::LIGHTGREEN);

	my_print("score: ");
	my_print(std::to_string(pacman.get_score()));

	goto_xy(board.get_legend_x(), board.get_legend_y() + 1);
	if (color_mode)
		board.set_color((int)Board::Color::RED);

	my_print("souls: ");
	my_print(std::to_string(pacman.get_souls()));
}

void Game::pause() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
	unsigned char c = _getch();
	goto_xy(PAUSE_X, PAUSE_Y);  
	my_print("Pause . . .");
	while (c != ESC)
		c = _getch();

	goto_xy(PAUSE_X, PAUSE_Y);
	my_print("           ");
}



void Game::handle_key_input(const unsigned char current_key) {  //return the direction vectors
	switch (current_key)
	{
	case right_upper_case:
	case right_lower_case:
		pacman.set_direction((int)Entity::Direction::RIGHT);
		break;

	case left_upper_case:
	case left_lower_case:
		pacman.set_direction((int)Entity::Direction::LEFT);
		break;

	case up_upper_case:
	case up_lower_case:
		pacman.set_direction((int)Entity::Direction::UP);
		break;

	case down_upper_case:
	case down_lower_case:
		pacman.set_direction((int)Entity::Direction::DOWN);
		break;

	case stay_upper_case:
	case stay_lower_case:

		pacman.set_direction((int)Entity::Direction::STAY);
		break;

	case ESC:
		if (!load_mode && !IS_SILENT)
			pause();
		pause_flag = true;
		break;
	}
}

//--Display Fucns: --//
void Game::lose() {
	system("cls");
	my_print("you lost.");
	my_print("\n");
	my_print("retry ? y / n :");

	char selection;
	cin >> selection;
	while (selection != 'y' && selection != 'n')
	{
		cout << "unvalid input! - y / n:";
		cin >> selection;
	}
	if (selection == 'n')
		loop_flag = true;
	else
	{
		pacman.set_souls(3);
		if (save_mode)
			save.finish_saving();
		load_game_from_files();
		loop_flag = true;
	}
}

void Game::win() {
	system("cls");
	char selection;
	board_level++;
	fruit.~fruit();
	is_fruit_dead = false;

	if (board_level < file_names.size())
	{
		if (load_mode || IS_SILENT)
		{
			checking_loading(1);

			load.finish_loading();
			load_game_from_files();
		}
		else
		{
			cout << "would you like to try the next lvl? y / n : ";
			cin >> selection;
			while (selection != 'y' && selection != 'n')
			{
				cout << "unvalid input y / n:";
				cin >> selection;
			}
			if (selection == 'n')
				loop_flag = true;

			else
			{
				if (save_mode)
				{
					if (board_level != (file_names.size()))
					{
						save.write_to_file(pacman.get_total_steps(), 0);

						save.write_to_file(pacman.get_total_steps(), 1);
						save.write_to_file(":", 1);
						save.write_to_file(1, 1);
						save.write_to_file('\n', 1);

						save.finish_saving();
					}
				}
				load_game_from_files();	
			}
		}
	}

	else
	{
		my_print("you won.");
		my_print("\n");
		system("pause");
		loop_flag = true;
	}
}

void Game::init_ghosts()
{
	ghosts.resize(board.get_num_of_ghosts());
	for (int i = 0; i < board.get_num_of_ghosts(); i++)
	{
		ghosts[i].set_position(board.get_ghost_pacman_pos()[i].get_x(), board.get_ghost_pacman_pos()[i].get_y());
		ghosts[i].set_board(board);
		ghosts[i].set_mode(ghosts_level_mode);
	}
}

void Game::load_new_board_to_play(const string& file_name) {
	system("cls");
	_flushall();

	try
	{
		hold_move = 0;
		board.set_how_many_legends(0);
		board.set_how_many_pacmans(0);
		board.set_num_of_ghosts(0);
		board.load_board(file_name);

		fruit = Fruit();
		fruit.set_board(board);
		if (!load_mode && !IS_SILENT)
			fruit.fruit();

		pause_flag = false;
		loop_flag = false;
		is_fruit_dead = false;

		if (!first_run_done)
		{
			board_level = 0;
			first_run_done = true;
			this->pacman = Pacman();
		}
		else
		{
			pacman.init_score();
			pacman.init_total_steps();
		}
		last_step_fruit_collision = 0;

		current_key = 's';
		pacman.set_position(board.get_inital_pacman_pos());
		pacman.set_direction(Entity::Direction::STAY);
		pacman.set_board(board);

		init_ghosts();
		board.print_board(this->color_mode);

		if (save_mode)
		{
			save.clear_direction_stuck();
			save.set_board_name(file_names[board_level]);
			save.init_save_files();
		}

		if (load_mode || IS_SILENT)
		{
			load.set_board_name(file_names[board_level]);
			load.set_num_of_ghosts(board.get_num_of_ghosts());
			load.init_load_files();
		}
	}
	catch (const char* error_msg)
	{
		if (IS_SILENT)
			throw error_msg;

		system("cls");
		cout << "board number: " << board_level + 1 << " ERROR: " << error_msg << " skipping the board" << endl;
		system("PAUSE");
		system("cls");

		board.board_errors.clear();

		if (error_msg[0] == 'B' && (board_level < file_names.size() - 1))
		{
			board_level++;
			load.finish_loading();
			save.finish_saving();
			load_game_from_files();
		}
		else if (board_level == file_names.size() - 1)
			throw " out of boards! ";
		else
			throw " unexcpected error game ";
	}
	catch (const string error_msg)
	{
		if (IS_SILENT)
			throw error_msg;

		system("cls");
		cout << "board number: " << board_level + 1 << " ERROR: " << error_msg << " skipping the board" << endl;
		system("PAUSE");
		system("cls");

		if (error_msg[0] == 'B' && (board_level < file_names.size() - 1))
		{
			board_level++;
			load_game_from_files();
		}
		else if (board_level == file_names.size() - 1)
			throw " out of boards! ";
		else
			throw " unexcpected error game ";
	}
}

//----------- Menu Class: -----------//
void Game::Menu::handle_menu() {
	Game run;
	do {
		system("cls");
		menu_display();
		cin >> user_choice;

		if (user_choice == Show_Ruls)
		{
			print_ruls();
			system("PAUSE");
			system("cls");
		}
		else if (user_choice == Start_Game)
		{
			system("cls");
			handle_ghosts_level(run);
			system("cls");
			run.set_save_mode(save_mode);
			run.game();
			run.first_run_done = false;
			run.set_level_board(0);
		}
		else if (user_choice == Change_Color_Mode)
		{
			if (run.color_mode == true)
			{

				cout << "color off!" << endl << endl;
				run.set_color_mode(false);
				Sleep(200);
				system("cls");
				menu_display();
			}
			else
			{
				cout << "color on!" << endl << endl;
				run.set_color_mode(true);
				Sleep(200);
				system("cls");
				menu_display();
			}
		}
		else
		{
			if (user_choice != Exit_Game)
			{
				cout << "pick valid choice." << endl;
				Sleep(250);
				system("cls");
				continue;
			}
		}

	} while (user_choice != Exit_Game);
	system("cls");
	return;
}
void Game::Menu::handle_ghosts_level(Game& run)
{
	cout << "Please select the level of ghosts" << endl;
	cout << "a ==> BEST" << endl << endl;
	cout << "b ==> GOOD" << endl << endl;
	cout << "c ==> NOVICE" << endl << endl;
	do
	{
		cin >> ghosts_level_choice;
		if (ghosts_level_choice == BEST)
			run.ghosts_level_mode = Smart;
		else if (ghosts_level_choice == GOOD)
			run.ghosts_level_mode = Good;
		else if (ghosts_level_choice == NOVICE)
			run.ghosts_level_mode = Novice;
		else
		{
			cout << "pick valid choice." << endl;
			Sleep(250);
			system("cls");
			cout << "Please select the level of ghosts" << endl;
			cout << "a ==> BEST" << endl << endl;
			cout << "b ==> GOOD" << endl << endl;
			cout << "c ==> NOVICE" << endl << endl;
		}
	} while (ghosts_level_choice != Exit_Game && ghosts_level_choice != BEST && ghosts_level_choice != GOOD && ghosts_level_choice != NOVICE);
}
void Game::Menu::menu_display() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
	cout << "Welcome to \"the\" Pacman !" << endl;
	cout << "Please select option : " << endl << endl;
	cout << "1 ==> Start a new game" << endl << endl;
	cout << "2 ==> switch color mode ON\\\OFF" << endl << endl;
	cout << "8 ==> Present instructions and keys" << endl << endl;
	cout << "9 ==> Exit from game" << endl;
}

void Game::Menu::print_ruls() const {
	cout << "Welcome to \"the\" Pacman !" << endl << "Your goal is to eat 'em all inorder to accumulate scroe" << endl
		<< "Each POINT equal to +1 for your score" << endl
		<< "Collect 100 POINTS!" << endl
		<< "Once you ate 'em all you won." << endl << endl
		<< "Keys:" << endl
		<< "UP --> w or W" << endl
		<< "DOWN --> x or X" << endl
		<< "LEFT --> a or A" << endl
		<< "RIGHT --> d or D" << endl
		<< "STAY --> s or S" << endl
		<< "ESC --> Pause" << endl
		<< "9 --> in game will exit to menu and reset(you will get new souls)" << endl << endl;
}


void Game::load_game_from_files()
{
	system("cls");
	_flushall();
	if (file_names.size() >= 1)
		load_new_board_to_play(file_names[board_level]);

	else
		throw " no valid board files ";
}

/*we can load boards from user input*/
/*
void Game::load_board_from_user()
{
	system("cls");
	_flushall();

	int i = 0;
	string desired_board_name;

	vector <string> tmp;
	cout << "Please enter board name:" << endl;
	cin >> desired_board_name;
	while (i < file_names.size())
	{
		size_t parser = file_names[i].find("pacman_");
		string curr_name = file_names[i].substr(parser);
		tmp.push_back(curr_name);

		if (desired_board_name != tmp[i])
			i++;

		else
		{
			load_new_board_to_play(desired_board_name);
			break;
		}
		if (i == file_names.size())
		{
			Sleep(500);
			system("cls");
			cout << "enter a valid file name!" << endl;
			cin >> desired_board_name;
			i = 0;
		}

	}
}
*/

bool Game::find_files() {
	int isFound = -1; // -1 indicate find() is false
	string curr_path = current_path().string();
	set<path> paths_names;

	int numFiles = 0;
	for (auto& entry : directory_iterator(curr_path))
	{
		isFound = entry.path().string().find(".screen");
		if (isFound != -1)
		{
			paths_names.insert(entry.path()); // sort the names coz its a set
			isFound = -1;
		}
	}
	for (auto& files : paths_names)
		file_names.push_back(files.string()); //push names sorted

	if (file_names.empty())
		return false;

	return true;
}

void Game::update_values_from_file()
{
	current_key = load.get_current_key();
	fruit.set_position(load.get_fruit_position());
	fruit.set_direction(load.get_fruit_direction());
	fruit.set_fruit_val(load.get_fruit_shape());
	fruit.set_shape(fruit.num_to_shape(fruit.get_fruit_val()));

	for (int i = 0; i < board.get_num_of_ghosts(); i++)
		ghosts[i].set_direction(load.get_ghost_direction()[i]);
}

void Game::run_load()
{
	load_mode = true;
	save_mode = false;

	Position next_pos;
	unsigned char temp = 's';

	find_files();
	load_game_from_files();

	hold_move = 0;
	while (!loop_flag)
	{

		load.load_line(0);
		update_values_from_file();

		if (!IS_SILENT)
			Sleep(SPEED / 3);  // fast forrward
		if (is_valid_key(current_key))
		{
			handle_key_input(current_key);
			if (pause_flag)
			{
				current_key = temp;
				pause_flag = false;
			}
			next_pos = pacman.move_dir();
			if (hold_move % 2 == 0)
			{
				handle_ghost_move();
				if (!is_fruit_dead)
					handle_fruit_move();
				else
				{
					is_fruit_dead = true;
					if (pacman.get_total_steps() == 150) //revive fruit
					{
						is_fruit_dead = false;
						fruit = Fruit();
						fruit.set_board(board);
					}
				}
			}
			else
			{
				for (int i = 0; i < board.get_num_of_ghosts(); i++)
				{
					if (ghosts[i].is_collided(pacman.get_position(), next_pos, pacman.get_direction()))
					{
						handle_collision();
						ghosts[i].set_position(board.get_ghost_pacman_pos()[i].get_x(), board.get_ghost_pacman_pos()[i].get_y());
					}
				}
			}

			handle_pacman_move();
			hold_move++;
			handle_score();
			temp = current_key;
		}
		else
		{
			if (current_key != '9')
				current_key = temp;
			else
				loop_flag = true; //stop the loop
		}
	}
	if (load.get_pacman_status() != 1)
		throw " pacman is alive the result file does not match to steps file ";

	load.finish_loading();
	return;
}

void Game::run_silent()
{
	IS_SILENT = true;
	try
	{
		run_load();
	}
	catch (const char* error_msg)
	{
		system("cls");
		cout << "Test Failed: Error: " << error_msg << endl;
		system("PAUSE");
		system("cls");
		return;
	}

	catch (const string error_msg)
	{
		system("cls");
		cout << "Test Failed: Error: " << error_msg << endl;
		system("PAUSE");
		system("cls");
		return;
	}

	cout << "Test Passed!" << endl;
	return;
}
