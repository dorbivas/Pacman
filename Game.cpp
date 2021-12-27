﻿#include "Game.h"

Game::Game() {
	srand(time(NULL)); //start generating rand numbers for ghost dir
}

void Game::game() {
	
	//for yarden:(TODO- fix_dir_yarden)
	file_names.push_back("pacman_01.screen");
	file_names.push_back("pacman_02.screen");
	file_names.push_back("pacman_03.screen");
	//for dor:
	//find_files();
	load_game_from_files();
	

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
			pacman.move_dir();//makes direction
			handle_ghost_move();
			if(!loop_flag) 
			{
				handle_fruit_move();
				handle_pacman_move();
				handle_score(pacman.get_position());
				temp = current_key;
			}
		}
		else
		{	
			if (current_key != '9')
				current_key = temp;
			else
				loop_flag = true;//stop the loop
		}
	}
	system("cls");
	return;
}

//--Game Logic Fucns: --//
void Game::handle_pacman_move() {
	Position curr_pos = pacman.get_position();
	int to_add = 0;
	
	Position next_pos = pacman.handle_move();
	//next position
	if (pacman.is_invalid_place(next_pos))
	{
		print_move(curr_pos, pacman.get_shpae());
		return;
	}
		
	next_pos = handle_teleport(next_pos);

	if (board.get_cell(next_pos) == Entity::Shape::P)
		to_add = 1;
	if (pacman.is_collided(fruit.get_position(), fruit.move_dir(), fruit.get_direction())
		|| board.get_cell(fruit.get_position()) == Entity::Shape::PACMAN
		||board.get_cell(curr_pos) == fruit.get_shpae()
		||board.get_cell(next_pos) == fruit.get_shpae())
	{
		to_add += fruit.get_fruit_val();
		fruit.fruit();	
	}
	board.set_cell(curr_pos, Entity::Shape::S);
	print_move(curr_pos, Entity::Shape::S);
	pacman.add_score(to_add);
	pacman.set_position(next_pos);
	print_move(next_pos, Entity::Shape::PACMAN);//was in the game()
	board.set_cell(next_pos, Entity::Shape::PACMAN);
}
void Game::handle_ghost_move() {
	Position curr_pos, next_pos;
	int i;
	for (i = 0; i < board.get_num_of_ghosts(); i++)
	{
		ghosts[i].set_pacman_pos(pacman.get_position());
		curr_pos = ghosts[i].get_position();
		next_pos = ghosts[i].handle_move();
		if (ghosts[i].is_collided(fruit.get_position(), fruit.move_dir(), fruit.get_direction())
			|| board.get_cell(fruit.get_position()) == Entity::Shape::GHOST
			||board.get_cell(curr_pos) == fruit.get_shpae()
			||board.get_cell(next_pos) == fruit.get_shpae())
			fruit.fruit();
		if (ghosts[i].is_collided(pacman.get_position(), pacman.move_dir(), pacman.get_direction())
			|| board.get_cell(pacman.get_position()) == Entity::Shape::GHOST
			|| board.get_cell(ghosts[i].get_position()) == Entity::Shape::PACMAN
			/*|| board.get_cell(next_pos) == Entity::Shape::PACMAN*/)
		{
			handle_collision();
			current_key = stay_lower_case;
		}
		if (board.get_cell(curr_pos) == Entity::Shape::P)
			print_move(curr_pos, Entity::Shape::P);
		else
		{
			print_move(curr_pos, Entity::Shape::S);
			board.set_cell(curr_pos, Entity::Shape::S);
		}

		//next position
		ghosts[i].set_position(next_pos);
		print_move(next_pos, Entity::Shape::GHOST);
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

	next_pos = fruit.handle_move();
	fruit.set_position(next_pos);
	
	print_move(next_pos, fruit.get_shpae());
}
void Game::handle_collision() {
	pacman.decrease_soul();//decreases soul from the pacman
	print_move(pacman.get_position(), Entity::Shape::GHOST);
	pacman.set_position((int)board.get_inital_pacman_pos().get_x(), (int)board.get_inital_pacman_pos().get_y()); //returns the pacman to its original position
	pacman.set_direction((int)Entity::Direction::STAY);
	//pacman.move_dir();
	if (pacman.get_souls() == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
		lose();
	}
}
void Game::handle_score(Position& next_pos) {
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
		next_pos.set_xy(0, next_pos.get_y());
		pacman.set_direction((int)Entity::Direction::RIGHT);
	}
	if (next_pos.get_x() == 0 && pacman_direction == 2)
	{
		next_pos.set_xy(last_col - 1, next_pos.get_y());
		pacman.set_direction((int)Entity::Direction::LEFT);
	}
	if (next_pos.get_y() == last_row - 1 && pacman_direction == 1)
	{
		next_pos.set_xy(next_pos.get_x(), 0);
		pacman.set_direction((int)Entity::Direction::DOWN);
	}
	if (next_pos.get_y() == 0 && pacman_direction == 0)
	{
		next_pos.set_xy(next_pos.get_x(), last_row - 1);
		pacman.set_direction((int)Entity::Direction::UP);
	}
	return next_pos;
}
void Game::print_move(const Position pos, Entity::Shape shape) {
	display_score_souls();
	if (color_mode)
	{
		if (shape == Entity::Shape::P)
			board.set_color((int)fruit.get_color());
		else if (shape == Entity::Shape::T)
			board.set_color((int)Board::Color::LIGHTBLUE);
		else if (shape == Entity::Shape::PACMAN)
			board.set_color((int)pacman.get_color());
		else // (c == GHOST_ICON)
			board.set_color((int)ghosts[0].get_color());
	}
	goto_xy(pos.get_x(), pos.get_y());
	if (shape != 0)
		cout << char(shape); 
}
void Game::display_score_souls() const {
	goto_xy(board.get_legend_x(), board.get_legend_y());
	if (color_mode)
		board.set_color((int)Board::Color::LIGHTGREEN);
	cout <<"score: " << pacman.get_score();
	goto_xy(board.get_legend_x(), board.get_legend_y() + 1);
	if (color_mode)
		board.set_color((int)Board::Color::RED);
	cout <<"souls: " <<pacman.get_souls();
}
void Game::pause() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
	goto_xy(PAUSE_X, PAUSE_Y);  // location of "pause..." in the console
	cout << "Pause . . .";
	unsigned char c = _getch();
	while (c != ESC)
		c = _getch();

	goto_xy(PAUSE_X, PAUSE_Y);
	cout << "           ";
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
	cout << "you lost." << endl;
	system("pause");
	loop_flag = true;
	//find_files();//TODO WHY HERE?
	//load_game_from_files();
}
void Game::win() {
	system("cls");
	cout << "you won." << endl;
	system("pause");
	loop_flag = true;
	//find_files();//TODO WHY HERE?
	//load_game_from_files();
}


void Game::load_new_board_to_play(const string& file_name) {

	system("cls");
	_flushall();
	board.load_board(file_name);
	this->pacman = Pacman();
	pacman.set_position(board.get_inital_pacman_pos());
	pacman.set_board(board);

	fruit = Fruit();
	fruit.set_board(board);
	fruit.fruit();
	
	pause_flag = false;
	loop_flag = false;
	first_run_done = false;
	
	pacman.set_position(board.get_inital_pacman_pos());

	for (int i = 0; i < board.get_num_of_ghosts(); i++) {
		ghosts[i].set_position(board.get_ghost_pacman_pos()[i].get_x() , board.get_ghost_pacman_pos()[i].get_y());
		ghosts[i].set_board(board);
		ghosts[i].set_mode(ghosts_level_mode);
	}
	board.print_board(this->color_mode);
	
}



//----------- Menu Class: -----------//
void Game::Menu::handle_menu() { 
	Game run; 
	do {
		cursor_visibility(false);

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
			run.game();
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
	cout << "9 ==> Exit" << endl;
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
		<< "ESC --> Pause" << endl << endl;
}


void Game::load_game_from_files()
{

	int i = 0;
	string desired_board_name;
	vector <string> tmp;

	system("cls");
	_flushall();

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

bool Game::find_files(){
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


