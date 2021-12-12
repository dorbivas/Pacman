﻿#include "Game.h"

Game::Game(){
	srand(time(NULL)); //start generating rand numbers for ghost dir
}

void Game::game() {
	reset_game();
	Position move_vector(0, 0);
	unsigned char current_key, temp;
	current_key = _kbhit();

	while (!is_valid_key(current_key) || current_key == ESC)
		current_key = _getch();
	temp = current_key;

	while (!loop_flag)
	{
		Sleep(100);//game speed	
		handle_ghost_move();
		if (_kbhit())	
			current_key = _getch();
		if (is_valid_key(current_key))
		{
			move_vector = handle_key_input(current_key);
			if (pause_flag)
			{
				current_key = temp;
				pause_flag = false;
			}

			if (is_collided_ghost(pacman.get_position()))
			{
				handle_collision();
				current_key = stay_lower_case;
				continue; // no need to cheeck other conditions.
			}
			check_pacman_move(move_vector);
			print_move(pacman.get_position(), PACMAN_ICON,color_mode,pacman.get_score(),pacman.get_souls());
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
void Game::check_pacman_move(const Position move_vector) {
	if (is_teleporting(pacman.get_position()))
	{
		board.set_cell(pacman.get_position(), (unsigned char)TELEPORT);
		print_move(pacman.get_position(), TELEPORT, color_mode, pacman.get_score(), pacman.get_souls());
	}
	else
	{
		board.set_cell(pacman.get_position(), S);
		print_move(pacman.get_position(), S,color_mode, pacman.get_score(), pacman.get_souls());
	}

	int next_x = pacman.get_position().get_x() + move_vector.get_x();
	int next_y = pacman.get_position().get_y() + move_vector.get_y();
	Position next_pos(next_x, next_y);

	handle_move(next_pos);
}

void Game::handle_collision() {
	pacman.decrease_soul();//decreases soul from the pacman
	print_move(pacman.get_position(), GHOST_ICON, color_mode, pacman.get_score(), pacman.get_souls());
	pacman.set_position(INITIAL_X, INITIAL_Y); //returns the pacman to its original position
	pacman.set_direction(STAY);
	if (pacman.get_souls() == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		lose();
	}
}

void Game::handle_move(Position next_pos) {
	if (is_invalid_place(next_pos))
		return;
	else
	{
		if (is_teleporting(next_pos))
			next_pos = handle_teleport(next_pos);

		handle_score(next_pos);
		pacman.set_position(next_pos);
	}
}

void Game::handle_ghost_move() {
	Position curr_pos, next_pos;
	int souls = pacman.get_souls();
	int score = pacman.get_score();
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
	{
		curr_pos = ghosts[i].get_position();
		next_pos = ghosts[i].move_ghost();
		while (is_invalid_place(next_pos) || board.get_cell(next_pos) == TELEPORT)
		{
			ghosts[i].rotate_direction();
			next_pos = ghosts[i].move_ghost();
		}

		ghosts[i].set_position(next_pos);

		if (board.get_cell(curr_pos) == P)
		{
			board.set_cell(curr_pos, P);
			print_move(curr_pos, P, color_mode, score, souls);
		}
		else
			print_move(curr_pos, S, color_mode, score, souls);//deletes the previous symbol
		
		print_move(next_pos, GHOST_ICON, color_mode, score, souls);
	}
}


bool Game::is_collided_ghost(const Position pacman_pos) {
	int d1, d2, x_dif, y_dif;
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
	{
		if (ghosts[i].get_position() == pacman.get_position())
			return true;
		
		//edge cases
		d1 = ghosts[i].get_direction();
		d2 = pacman.get_direction();
		x_dif = pacman_pos.get_x() - ghosts[i].get_position().get_x();
		y_dif = pacman_pos.get_y() - ghosts[i].get_position().get_y();
		Position dif(x_dif, y_dif);

		if ((d1 == UP && d2 == DOWN && dif == Position(0, 1) ||
			d1 == DOWN && d2 == UP && dif == Position(0, -1) ||
			d1 == LEFT && d2 == RIGHT && dif == Position(-1, 0) ||
			d1 == RIGHT && d2 == LEFT && dif == Position(1, 0)))
				return true;		
	}
	return false;
}

bool Game::is_invalid_place(const Position next_pos) {
	return (board.get_cell(next_pos) == (unsigned char)WALL);
}

bool Game::is_teleporting(const Position next_pos) {
	return (board.get_cell(next_pos) == (unsigned char)TELEPORT);
}

Position Game::handle_teleport(Position next_pos) { 
	int Pacman_x = next_pos.get_x();
	int Pacman_y = next_pos.get_y();

	if (Pacman_x == TP_NORTH1_TOP_X && Pacman_y == TP_NORTH1_TOP_Y)
	{
		next_pos.set_xy(TP_NORTH1_BOT_X, TP_NORTH1_BOT_Y);
		pacman.set_direction(UP);
	}
	else if (Pacman_x == TP_NORTH2_TOP_X && Pacman_y == TP_NORTH2_TOP_Y)
	{
		next_pos.set_xy(TP_NORTH2_BOT_X, TP_NORTH2_BOT_Y);
		pacman.set_direction(UP);
	}
	else if (Pacman_x == TP_NORTH1_BOT_X && Pacman_y == TP_NORTH1_BOT_Y)
	{
		next_pos.set_xy(TP_NORTH1_TOP_X, TP_NORTH1_TOP_Y);
		pacman.set_direction(DOWN);
	}
	else if (Pacman_x == TP_NORTH2_BOT_X && Pacman_y == TP_NORTH2_BOT_Y)
	{
		next_pos.set_xy(TP_NORTH2_TOP_X, TP_NORTH2_TOP_Y);
		pacman.set_direction(DOWN);
	}
	else if (Pacman_x == TP_EAST_BOT_X && Pacman_y == TP_EAST_BOT_Y)
	{
		next_pos.set_xy(TP_WEST_TOP_X, TP_WEST_TOP_Y);
		pacman.set_direction(RIGHT);
	}
	else if (Pacman_x == TP_WEST_TOP_X && Pacman_y == TP_WEST_TOP_Y)
	{
		next_pos.set_xy(TP_EAST_BOT_X, TP_EAST_BOT_Y);
		pacman.set_direction(LEFT);
	}
	return next_pos;
}

void Game::pause() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	goto_xy(11, 24);  // location of "pause..." in the console
	cout << "Pause . . .";
	unsigned char c = _getch();
	while (c != ESC)
		c = _getch();

	goto_xy(11, 24);
	cout << "           ";
}

void Game::handle_score(Position pacman_pos) {
	if (board.get_cell(pacman_pos) == P)
	{
		pacman.add_score();
		if (pacman.get_score() == MAX_POINTS)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			win();
		}
	}
}

Position Game::handle_key_input(const unsigned char current_key) {  //return the direction vectors
	int dir_x = 0, dir_y = 0;
	Position pos(dir_x, dir_y);
	int pacman_x = pacman.get_position().get_x();
	int pacman_y = pacman.get_position().get_y();
	switch (current_key)
	{
	case right_upper_case:
	case right_lower_case:
		dir_x = 1;
		dir_y = 0;
		pacman.set_direction(RIGHT);
		break;

	case left_upper_case:
	case left_lower_case:
		dir_x = -1;
		dir_y = 0;
		pacman.set_direction(LEFT);
		break;

	case up_upper_case:
	case up_lower_case:
		dir_x = 0;
		dir_y = -1;
		pacman.set_direction(UP);
		break;

	case down_upper_case:
	case down_lower_case:
		dir_x = 0;
		dir_y = 1;
		pacman.set_direction(DOWN);
		break;

	case stay_upper_case:
	case stay_lower_case:
		dir_x = 0;
		dir_y = 0;
		pacman.set_direction(STAY);
		break;

	case ESC:
		pause();
		pause_flag = true;
		break;
	}
	pos.set_xy(dir_x, dir_y);
	return pos;
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


void Game::Menu(){
	int userChoice = 0;
	do
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		cout << "Welcome to \"the\" Pacman !" << endl;
		cout << "Please select option : " << endl << endl;
		cout << "1 ==> Start a new game" << endl << endl;
		cout << "2 ==> switch color mode ON\\\OFF" << endl << endl;
		cout << "8 ==> Present instructions and keys" << endl << endl;
		cout << "9 ==> Exit" << endl;
		cin >> userChoice;

		if (userChoice == 8)
		{
			print_ruls();
			system("PAUSE");
			system("cls");
		}
		else if (userChoice == 1)
		{
			system("cls");
			game();
		}
		else if (userChoice == 2)
		{
			if (this->color_mode == true)
			{
				cout << "color off!" << endl << endl;
				set_color_mode(false);
				Sleep(200);
				system("cls");
				Menu();
			}
			else 
			{
				cout << "color on!" << endl << endl;
				set_color_mode(true);
				Sleep(200);
				system("cls");
				Menu();
			}
		}
		else
		{
			if (userChoice != 9)
			{
				cout << "pick valid choice." << endl;
				Sleep(250);
				system("cls");
				continue;
			}
		}

	} while (userChoice != 9);
	system("cls");
	return;
}

void Game::print_ruls() const {
	cout << "Welcome to \"the\" Pacman !" << endl << "Your goal is to eat 'em all inorder to accumulate scroe" << endl
		<< "Each point equal to +1 for your score" << endl
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

void Game::reset_game() {
	board.init_board();
	board.print_board(this->color_mode);
	this->pacman = Pacman();
	pause_flag = false;
	loop_flag = false;
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
		ghosts[i].set_position(INITAL_GHOST_X + (2 * i), INITAL_GHOST_Y);
}

