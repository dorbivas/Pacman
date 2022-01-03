#include "Game.h"

extern bool IS_SILENT; //todo

Game::Game() {
	srand(time(NULL)); //start generating rand numbers for ghost dir
}

void Game::game() {

	save_mode = true;//TODO DELATE- JUST FOR TESTING
	find_files();
	load_game_from_files();

	Position next_pos;
	unsigned char temp;
	current_key = _kbhit();

	while (!is_valid_key(current_key) || current_key == ESC)
		current_key = _getch();
	temp = current_key;

	while (!loop_flag)
	{
		Sleep(SPEED);//TODO SPEED
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
					if(save_mode)
						save.set_is_fruit_dead(true);

					if (pacman.get_total_steps() == 150)
					{
						is_fruit_dead = false;
						if(save_mode)
							save.set_is_fruit_dead(false);

						fruit = Fruit();
						fruit.set_board(board);
						fruit.fruit();
					}
				}
			}
		
			handle_pacman_move();
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
		if (save_mode)
			save.save_steps();
		hold_move++;
	}

	system("cls");

	if (save_mode)
	{
		save.write_to_file(pacman.get_total_steps());
		save.finish_saving();
	}
	return;
}

//--Game Logic Fucns: --//
void Game::handle_pacman_move() {
	Position curr_pos = pacman.get_position();
	int to_add = 0;
	Position next_fruit_pos;
	Position next_pos = pacman.handle_move();

	//next position
	if(pacman.is_invalid_place(next_pos))
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
		to_add += fruit.get_fruit_val();
		print_move(fruit.get_position(), Entity::Shape::S);

		if(!load_mode && !IS_SILENT)
			fruit.fruit();
	}

	board.set_cell(curr_pos, Entity::Shape::S);
	print_move(curr_pos, Entity::Shape::S);

	pacman.add_score(to_add);

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
				if(!load_mode && !IS_SILENT)
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
			ghosts[i].set_position(next_pos);
			print_move(next_pos, Entity::Shape::GHOST);
			
		}
	}
}

void Game::handle_fruit_move() {
	Position curr_pos, next_pos;
	curr_pos = fruit.get_position();

	if (board.get_cell(curr_pos) == Entity::Shape::P)
		print_move(curr_pos, Entity::Shape::P);
	else
	{
		print_move(curr_pos, Entity::Shape::S);
		board.set_cell(curr_pos, Entity::Shape::S);
	}

	if ((pacman.get_total_steps() == 100 && !load_mode) || (pacman.get_total_steps() == 99 && (load_mode||IS_SILENT)))//fruit disappeard
	{
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
			
		if (save_mode)//TOcheck
		{
			save.set_fruit_shape(fruit.get_shape());
			save.set_fruit_direction(fruit.get_direction());
			save.set_fruit_pos(curr_pos);
		}
	}
}

void Game::handle_collision() {

	pacman.decrease_soul();//decreases soul from the pacman
	print_move(pacman.get_position(), Entity::Shape::S);
	pacman.set_position((int)board.get_inital_pacman_pos().get_x(), (int)board.get_inital_pacman_pos().get_y()); //returns the pacman to its original position
	pacman.set_direction((int)Entity::Direction::STAY);


	if (pacman.get_souls() == 0)
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
	unsigned char c = _getch();//TODO in load mode
	goto_xy(PAUSE_X, PAUSE_Y);  // location of "pause..." in the console
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
	my_print("retry ? (1) back to menu(0):");
	//system("pause");
	int selection;
	cin >> selection;
	while (selection != 0 && selection != 1)//TODO EXCEPTION
	{
		cout << "wrong input,retry?-(1), back to menu-(0):";
		cin >> selection;
	}
	if (selection == 0)
		loop_flag = true;
	else
	{
		if (save_mode)
			save.finish_saving();
		load_new_board_to_play(file_names[board_level]);//retry
	}
}

void Game::win() {
	system("cls");
	int selection;
	board_level++;
	if (board_level < file_names.size())
	{
		if (load_mode)
		{
			load.finish_loading();
			load_new_board_to_play(file_names[board_level]);//load new board
		}
		else
		{
			cout << "next level-(1), back to menu-(0): ";
			cin >> selection;
			while (selection != 0 && selection != 1)//TODO EXCEPTION
			{
				cout << "ext level-(1), back to menu-(0):";
				cin >> selection;
			}
			if (selection == 0)
				loop_flag = true;	
			else
			{
				if (save_mode)
				{
					save.write_to_file(pacman.get_total_steps());
					save.finish_saving();
				}
					
				load_new_board_to_play(file_names[board_level]);//load new board
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
	board.load_board(file_name);

	fruit = Fruit();
	fruit.set_board(board);
	if(!load_mode)
		fruit.fruit();

	pause_flag = false;
	loop_flag = false;
	is_fruit_dead = false;

	if(!first_run_done)
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
		
	current_key = 's'; 
	pacman.set_position(board.get_inital_pacman_pos());
	pacman.set_direction(Entity::Direction::STAY);
	pacman.set_board(board);

	init_ghosts();
	board.print_board(this->color_mode);

	if (save_mode)
	{
		save.set_board_name(file_names[board_level]);
		save.init_save_file();
	}

	if (load_mode)
	{
		load.set_board_name(file_names[board_level]);
		load.set_num_of_ghosts(board.get_num_of_ghosts());
		load.init_load_file();
	}

	if (IS_SILENT)
	{
		//TODO
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
		}
		else if (user_choice == 11)//saved game
		{
			//IS_SILENT = true;
			IS_SILENT = !IS_SILENT;
			cout << "SILENT!" << endl << endl;
			Sleep(200);
			system("cls");
			run.first_run_done = true;
			run.run_silent();
			//menu_display();
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
		<< "Collect 300 POINTS!" << endl
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
	{
		//TODO EXCEPTION
		cout << "error";
	}

	//load_board_from_user();//TODO(ASK DOR) -GET BOARD NAME FROM THE USER, its necessary?	
}

void Game::load_board_from_user()
{
	system("cls");
	_flushall();
	
	int i = 0;
	string desired_board_name;

	vector <string> tmp;
	cout << "Please enter board name:" << endl;// TODO EXCEPTION
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
	is_fruit_dead = load.get_fruit_is_dead();
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
	unsigned char temp;

	int counter_steps = 0;

	find_files();
	load_game_from_files();
	
	while (!loop_flag)
	{
		load.load_line();
		update_values_from_file();

		if(!IS_SILENT)
			Sleep(SPEED);
		if (is_valid_key(current_key))
		{
			handle_key_input(current_key);
			if (pause_flag)
			{
				current_key = temp;
				pause_flag = false;
			}
			next_pos = pacman.move_dir();
			if (counter_steps % 2 == 0)
			{
				handle_ghost_move();
				if (!is_fruit_dead)
					handle_fruit_move();
				else
				{
					if (pacman.get_total_steps() == 150)//alive again
					{
						is_fruit_dead = false;
						fruit = Fruit();
						fruit.set_board(board);
					}
				}
			}
			
			handle_pacman_move();
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
		if (counter_steps==load.get_num_of_steps())
			loop_flag = true;//stop the loop

		counter_steps++;
	}

	system("cls");
	return;
}
void Game::run_silent()
{
	IS_SILENT = true;
	run_load();
	bool test_is_good = false;


	/*
		conditon for good test:TODO
	*/

	if (test_is_good)
		cout << "passed" << endl;
	else
		cout << "test falied" << endl;

}


