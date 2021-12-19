#include "Game.h"

Game::Game() {
	srand(time(NULL)); //start generating rand numbers for ghost dir
}

void Game::game() {
	//reset_game();
	//bool found = find_files();
	//if(found)
	find_files();
	//load_game_from_files();
	load_new_board_to_play("pacman_03.screen.txt");

	unsigned char current_key, temp;
	current_key = _kbhit();

	while (!is_valid_key(current_key) || current_key == ESC)
		current_key = _getch();
	temp = current_key;

	while (!loop_flag)
	{
		Sleep(SPEED);
		handle_ghost_move();
		handle_fruit_move();
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
			pacman.move_dir();
			if (is_collided_ghost(pacman.get_position(),pacman.move_dir(),pacman.get_direction()))
			{
				handle_collision();
				current_key = stay_lower_case;
				continue; // no need to cheeck other conditions.
			}
			check_pacman_move();
			print_move(pacman.get_position(), Entity::Shape::PACMAN);
			temp = current_key;
		}
		else
		{		//exit yo menu 
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
void Game::check_pacman_move() {

	if (is_my_teleporting(pacman.get_position()))
	{
		board.set_cell(pacman.get_position(), (unsigned char)Board::TELEPORT);
		print_move(pacman.get_position(), Entity::Shape::T);
	}
	else
	{
		board.set_cell(pacman.get_position(), Entity::Shape::S);
		print_move(pacman.get_position(), Entity::Shape::S);
	}
	handle_move();//next position
}

void Game::handle_collision() {
	pacman.decrease_soul();//decreases soul from the pacman
	print_move(pacman.get_position(), Entity::Shape::GHOST);
	pacman.set_position((int)Pacman::INITIAL_X, (int)Pacman::INITIAL_Y); //returns the pacman to its original position
	pacman.set_direction((int)Entity::Direction::STAY);
	if (pacman.get_souls() == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
		lose();
	}
}
//TODO VIRT
/*
void Game::handle_collision() {
	pacman.add_score();//decreases soul from the pacman
	print_move(pacman.get_position(), fruit.get_shpae());
	pacman.set_position((int)Pacman::INITIAL_X, (int)Pacman::INITIAL_Y); //returns the pacman to its original position
	pacman.set_direction((int)Entity::Direction::STAY);
	if (pacman.get_souls() == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
		lose();
	}
}*/

void Game::handle_move() {
	Position next_pos = pacman.move_dir();
	if (pacman.is_invalid_place(next_pos))
		return;
	else
	{
		if (pacman.is_my_teleporting(next_pos))
			next_pos = my_teleport(next_pos);

		handle_score(next_pos);
		pacman.set_position(next_pos);
	}
}

void Game::handle_ghost_move() {//TODO VIRTUAL
	Position curr_pos, next_pos;
	int next_x = 0, next_y = 0;
	for (int i = 0; i < board.get_num_of_ghosts(); i++)
	{
		curr_pos = ghosts[i].get_position();
		if (ghosts[i].get_mode() == Smart)
			ghosts[i].smart(pacman.get_position());
		else if (ghosts[i].get_mode() == Novice)
			ghosts[i].novice_lvl_ghost();
		else
			ghosts[i].good_lvl_ghost(pacman.get_position());

		next_pos =  ghosts[i].move_dir();
		if (ghosts[i].get_mode() == Novice)
		{
			while (ghosts[i].is_invalid_place(next_pos))
			{
				ghosts[i].rotate_direction();
				ghosts[i].novice_lvl_ghost();
				next_pos = ghosts[i].move_dir();
			}
		}
		ghosts[i].set_position(next_pos);

		/*if (board.get_cell(curr_pos) == Entity::Shape::P)//TODO-YARDEN
		{
			fruit = Fruit();
			//timer
		}*/
		print_move(curr_pos, Entity::Shape::S);//TODO-YRADEN
		print_move(next_pos, Entity::Shape::GHOST);
	}
}
void Game::handle_fruit_move() {//TODO VIRTUAL
	Position curr_pos, next_pos;
	int next_x = 0, next_y = 0;
	curr_pos = fruit.get_position();
	fruit.set_dir();
	next_pos = fruit.move_dir();
	while (fruit.is_invalid_place(next_pos))
	{
		fruit.rotate_direction();
		fruit.set_dir();
		next_pos = fruit.move_dir();
	}
	fruit.set_position(next_pos);
	/*
	if (board.get_cell(curr_pos) == Entity::Shape::PACMAN)//TODO REMOVE AFTER RUNNING
	{
		board.set_cell(curr_pos, Entity::Shape::GHOST);
		print_move(curr_pos, Entity::Shape::GHOST);
	}
	else
		print_move(curr_pos, Entity::Shape::S);//deletes the previous symbol*/
	print_move(curr_pos, Entity::Shape::S);
	print_move(next_pos, Entity::Shape::P);
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
		cout << char(shape);//TODO MAYBE SET CELL 
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
bool Game::is_collided_ghost(const Position& curr_pos,const Position& next_pos,int direction) {
	for (int i = 0; i < board.get_num_of_ghosts(); i++)
		return ghosts[i].is_collided(curr_pos, next_pos, direction);
}

void Game::handle_teleport(Position& pacman_pos)//TODO
{
	int pacman_direction = pacman.get_direction();
	int num_of_lines = board.get_cols();
	int num_of_cols = board.get_rows();

	if (board.get_cell(pacman_pos) == Entity::Shape::S)
	{
		if (pacman_direction == int(Entity::Direction::DOWN))
			pacman.set_position(pacman_pos.get_x(), pacman_pos.get_y() % num_of_lines);
		if (pacman_direction == int(Entity::Direction::UP))
			pacman.set_position(pacman_pos.get_x(), pacman_pos.get_y() + num_of_lines);
		if (pacman_direction == int(Entity::Direction::LEFT))
			pacman.set_position(pacman_pos.get_x() + num_of_cols, pacman_pos.get_y());
		if (pacman_direction == int(Entity::Direction::RIGHT))
			pacman.set_position(pacman_pos.get_x() % num_of_cols, pacman_pos.get_y());
	}
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

void Game::handle_score(Position& next_pos) {
	int to_add = 0;
	if (board.get_cell(next_pos) == Entity::Shape::P)//TODO CHECK WAHT MORE GOOD
		to_add = 1;

	if(fruit.is_collided(next_pos,pacman.move_dir(),pacman.get_direction()))
	{
		board.set_cell(next_pos, Entity::Shape::S);
		to_add = fruit.get_fruit_val();
		//TODO TIMER
		fruit.generate_random_pos();
		fruit.generate_random_fruit_val();	
	}

	pacman.add_score(to_add);
	if (pacman.get_score() >= MAX_POINTS)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Board::Color::WHITE);
		win();
	}
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
}
void Game::win() {
	system("cls");
	cout << "you won." << endl;
	system("pause");
	loop_flag = true;
}

void Game::reset_game() {//TODO FIX 
	board.our_spacial_board();
	
	this->pacman = Pacman();
	fruit= Fruit();
	fruit.generate_random_pos();
	pause_flag = false;
	loop_flag = false;
	for (int i = 0; i < board.get_num_of_ghosts(); i++) {
		ghosts[i].set_position(INITAL_GHOST_X + (2 * i), INITAL_GHOST_Y);
		ghosts[i].set_board(board);
		ghosts[i].set_mode(ghosts_level_mode);
	}
	pacman.set_board(board);
	fruit.set_board(board);
	board.print_board(this->color_mode);

}

void Game::load_new_board_to_play(const string& file_name) {

	system("cls");
	_flushall();

	this->pacman = Pacman();
	fruit = Fruit();
	board.load_board(file_name);

	pause_flag = false;
	loop_flag = false;

	pacman.set_board(board);
	fruit.set_board(board);

	pacman.set_position(board.get_inital_pacman_pos());

	for (int i = 0; i < board.get_num_of_ghosts(); i++) {
		ghosts[i].set_position(board.inital_ghosts_pos[i].get_x() , board.inital_ghosts_pos[i].get_y());
		ghosts[i].set_board(board);
		ghosts[i].set_mode(ghosts_level_mode);
	}
	board.print_board(this->color_mode);
	
}



//----------- Menu Class: -----------//
void Game::Menu::handle_menu() { //TODO number table for user choice?
	Game run; 
	do {
		cursor_visibility(false); //hiding console cursor

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
			cout << "Please select the level of ghosts" << endl;//TODO PRINT MENU
			cout << "a ==> BEST" << endl << endl;
			cout << "b ==> GOOD" << endl << endl;
			cout << "c ==> NOVICE" << endl << endl;
		}//TO DO FUNCTION WHILE
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



//addition

//addition
Position& Game::my_teleport(Position& next_pos) {
	int Pacman_x = next_pos.get_x();
	int Pacman_y = next_pos.get_y();

	if (Pacman_x == TP_NORTH1_TOP_X && Pacman_y == TP_NORTH1_TOP_Y)
	{
		next_pos.set_xy(TP_NORTH1_BOT_X, TP_NORTH1_BOT_Y);
		pacman.set_direction((int)Entity::Direction::UP);
	}
	else if (Pacman_x == TP_NORTH2_TOP_X && Pacman_y == TP_NORTH2_TOP_Y)
	{
		next_pos.set_xy(TP_NORTH2_BOT_X, TP_NORTH2_BOT_Y);
		pacman.set_direction((int)Entity::Direction::UP);
	}
	else if (Pacman_x == TP_NORTH1_BOT_X && Pacman_y == TP_NORTH1_BOT_Y)
	{
		next_pos.set_xy(TP_NORTH1_TOP_X, TP_NORTH1_TOP_Y);
		pacman.set_direction((int)Entity::Direction::DOWN);
	}
	else if (Pacman_x == TP_NORTH2_BOT_X && Pacman_y == TP_NORTH2_BOT_Y)
	{
		next_pos.set_xy(TP_NORTH2_TOP_X, TP_NORTH2_TOP_Y);
		pacman.set_direction((int)Entity::Direction::DOWN);
	}
	else if (Pacman_x == TP_EAST_BOT_X && Pacman_y == TP_EAST_BOT_Y)
	{
		next_pos.set_xy(TP_WEST_TOP_X, TP_WEST_TOP_Y);
		pacman.set_direction((int)Entity::Direction::RIGHT);
	}
	else if (Pacman_x == TP_WEST_TOP_X && Pacman_y == TP_WEST_TOP_Y)
	{
		next_pos.set_xy(TP_EAST_BOT_X, TP_EAST_BOT_Y);
		pacman.set_direction((int)Entity::Direction::LEFT);
	}
	return next_pos;
}