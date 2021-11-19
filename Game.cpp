#include "Game.h"
void Game::Menu()
{
	int userChoice = 0;
	cout << "Welcome to \"the\" Pacman !" << endl;
	do
	{
		cout << "Please select option : " << endl << endl;
		cout << "1 ==> Start a new game" << endl << endl;
		cout << "2 ==> Color mode" << endl << endl;
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
			if (color_mode == true)
			{
				cout << "color off!" << endl << endl;
				set_color_mode(false);
				system("cls");
			}
			else {
				cout << "color on!" << endl << endl;
				set_color_mode(true);
				system("cls");
			}

			game();
		}

	} while (userChoice != 9);
	system("cls");
	return;
}

void Game::game()
{
	//VAR
	Position starting_point(INITIAL_X, INITIAL_Y);
	Pacman pacman_temp(NUM_OF_SOULS, STAY, starting_point, ZERO_POINTS);
	this->set_pacman(pacman_temp);
	Position dir_pos(0, 0);
	unsigned char currentKey;
	unsigned char temp;


	srand(time(NULL)); //start generating numbers

	board.print_board(); 


	//GHOSTS
	/*for (int = 0; i < NUM_OF_GHOSTS; i++)
	{
		ghosts[i].set_position(INITAL_GHOST_X, INITAL_GHOST_Y);
		//ghost_move();
		print_move(ghosts[i].get_position(), GHOST_SYMBOL);
	}*/
	ghosts[0].set_position(INITAL_GHOST_X, INITAL_GHOST_Y);
	print_move(ghosts[0].get_position(), GHOST_SYMBOL);
	ghosts[1].set_position(INITAL_GHOST_X+30, INITAL_GHOST_Y);
	print_move(ghosts[1].get_position(), GHOST_SYMBOL);


	currentKey = _kbhit();
	while (!is_valid_key(currentKey))
		currentKey = _getch();
	temp = currentKey;
	while (!loop_flag)
	{
		Sleep(100);			//1 ms between moves
		if (_kbhit())	// if any key was hit , only if a key was hit we read what key code it was
			currentKey = _getch();
		if (is_valid_key(currentKey))
		{
			dir_pos = handle_key_input(currentKey);
			if (pause_flag)
			{
				currentKey = temp;
				pause_flag = false;
			}
			pacman_move(dir_pos);
			print_move(pacman.get_position(), (unsigned char)PACMAN_SYMBOL);
			temp = currentKey;
		}
		else
		{
			if (currentKey != '9')
				currentKey = temp;
			else
				loop_flag = true;
		}
	}
	system("cls");
	return;
}

void Game::pacman_move(Position dir_pos) {

	if (board.get_cell(pacman.get_position()) == (unsigned char)POINT)
		board.set_cell(pacman.get_position(), ' ');
	//if (board.get_cell(pacman.get_position()) != (unsigned char)GHOST)) TODO 
	print_move(pacman.get_position(), ' ');

	//only for example
	if(is_collided_ghost())
		print_move(pacman.get_position(), GHOST_SYMBOL);

	if (is_teleporting(pacman.get_position()))
		print_move(pacman.get_position(), TELEPORT);

	int dir_x = dir_pos.get_x();
	int dir_y = dir_pos.get_y();

	int x = pacman.get_position().get_x() + dir_x;
	int y = pacman.get_position().get_y() + dir_y;
	Position next_pos(x, y);

	handle_move(next_pos);
}

void Game::handle_move(Position next_pos) {

	if (is_invalid_place(next_pos))
		return;
	else
	{
		if (is_teleporting(next_pos))
			next_pos = teleport(next_pos);

		if (is_collided_ghost())//with ghost
		{
			pacman.decrease_soul();
			next_pos.set_xy(INITIAL_X, INITIAL_Y);
			if (pacman.get_souls() == 0)
				lose();
		}
		handle_score(next_pos);

		pacman.set_position(next_pos);
	}
}

Position Game::handle_key_input(unsigned char currentKey)
{
	int dir_x = 0, dir_y = 0;
	Position pos(dir_x, dir_y);
	int pacman_x = pacman.get_position().get_x();
	int pacman_y = pacman.get_position().get_y();
	switch (currentKey)
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

	case ESC://PAUSE
		pause();
		pause_flag = true;
		break;
	}
	pos.set_xy(dir_x, dir_y);
	return pos;

}

void Game::print_move(Position pos, unsigned char c) {
	display_score_souls();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.set_xy(pos.get_x(), pos.get_y());
	SetConsoleTextAttribute(hConsole, 6);
	goto_xy(pos.get_x(), pos.get_y());
	if (c != 0)
		cout << c;
}

bool Game::is_collided_ghost() {
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
	{
		if (compare_pos(ghosts[i].get_position(), pacman.get_position()))
			return true;
	}
	return false;
}
bool Game::is_invalid_place(Position next_pos) {
	return (board.get_cell(next_pos) == (unsigned char)WALL);
}
bool Game::is_teleporting(Position next_pos) {
	return (board.get_cell(next_pos) == (unsigned char)TELEPORT);
}


Position Game::teleport(Position next_pos)//teleporting the pacman and return if teleported
{
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
	Position pos;
	pos.set_xy(0, 0);
	print_move(pos, 0);
	cout << "\rPAUSE";
	unsigned unsigned char c = _getch();
	while (c != ESC)
	{
		c = NULL;
		c = _getch();
	}
	cout << "\r     ";
}

void Game::handle_score(Position pacman_pos) {
	if (board.get_cell(pacman_pos) == POINT)
	{
		pacman.add_score();

		if (pacman.get_score() == MAX_POINTS)
			win();
	}
}
void Game::lose() {
	system("cls");
	cout << "you lost." << endl;
	system("pause");
	loop_flag = true;
	//reset_game()	
}
void Game::win() {
	system("cls");
	cout << "you won."<<endl;
	system("pause");
	loop_flag = true;
	//reset_game() TODO

}
void Game::display_score_souls() {
	goto_xy(7, 23);
	cout << pacman.get_score();
	goto_xy(7, 24);
	cout << pacman.get_souls();
}
void Game::print_ruls() {
	cout << "Welcome to \"the\" Pacman !" << endl << "Your goal is to eat 'em all inorder to accumulate scroe" << endl
		<< "Each point equal to +1 for your score" << endl
		<< "Once you ate 'em all you won." << endl << endl
		<< "Keys:" << endl
		<< "UP --> w or W" << endl
		<< "DOWN --> x or X" << endl
		<< "LEFT --> a or A" << endl
		<< "RIGHT --> d or D" << endl
		<< "STAY --> s or S" << endl
		<< "ESC --> Pause" << endl << endl;
}

void Game::ghost_move()//TODO
{
	/*if (board.get_cell(pacman.get_position()) == (unsigned char)POINT)
		board.set_cell(pacman.get_position(), (unsigned char)POINT);
	//if (board.get_cell(pacman.get_position()) != (unsigned char)GHOST)) TODO
	print_move(pacman.get_position(), ' ');

	if (is_teleporting(pacman.get_position()))
		print_move(pacman.get_position(), TELEPORT);

	int x = pacman.get_position().get_x() + dir_x;
	int y = pacman.get_position().get_y() + dir_y;
	Position next_pos(x, y);

	//handle_move(next_pos);*/
}
void Game::reset_game() {//TODO
}

