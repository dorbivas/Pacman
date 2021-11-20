#include "Game.h"


void Game::game(){
	Position starting_point(INITIAL_X, INITIAL_Y);
	Pacman pacman_temp(NUM_OF_SOULS, STAY, starting_point, ZERO_POINTS);
	Position dir_pos(0, 0);
	unsigned char currentKey;
	unsigned char temp;

	this->set_pacman(pacman_temp);

	srand(time(NULL)); //start generating rand numbers for ghost dir

	board.print_board(this->color_mode); 

	currentKey = _kbhit();
	while (!is_valid_key(currentKey))
		currentKey = _getch();
	temp = currentKey;

	ghosts[1].set_position(INITAL_GHOST_X + 2, INITAL_GHOST_Y);

	while (!loop_flag)
	{
		
		handle_ghost_move();
		Sleep(150);			//1 ms between moves
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
			print_move(pacman.get_position(), (unsigned char)PACMAN_ICON);
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
//--Game Logic Fucns: --//
void Game::pacman_move(Position dir_pos) {
	if(is_collided_ghost())
		print_move(pacman.get_position(), GHOST_ICON);

	else if (is_teleporting(pacman.get_position()))
	{
	
		board.set_cell(pacman.get_position(), (unsigned char)TELEPORT);
		print_move(pacman.get_position(), (unsigned char)TELEPORT);
	}
	else
	{
		board.set_cell(pacman.get_position(), ' ');
		print_move(pacman.get_position(), ' ');
	}
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
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				lose();
			}
				
		}
		handle_score(next_pos);

		pacman.set_position(next_pos);
	}
}

void Game::handle_ghost_move()
{
	Position curr_pos, next_pos;
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
	{
		curr_pos = ghosts[i].get_position();
		next_pos=ghosts[i].move_ghost();
		if (is_invalid_place(next_pos) || board.get_cell(next_pos) == (unsigned char)TELEPORT)
		{
			return;
		}
		else
		{
			ghosts[i].set_position(next_pos);
			if (board.get_cell(curr_pos) == (unsigned char)POINT)
			{
				board.set_cell(curr_pos, (unsigned char)POINT);
				print_move(curr_pos, (unsigned char)POINT);
			}
			else
			{
				print_move(curr_pos, ' ');
			}
			print_move(next_pos, GHOST_ICON);
		}
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
	pos.set_xy(pos.get_x(), pos.get_y());
	
	if (this->color_mode)
	{
		if (c == TELEPORT)
			board.set_color(LIGHTBLUE);
		else if (c == PACMAN_ICON)
			board.set_color(YELLOW);
		else // (c == GHOST_ICON)
			board.set_color(RED);
	}
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	goto_xy(11, 23);
	cout << "Pause . . .";
	unsigned char c = _getch();
	while (c != ESC)
		c = _getch();
	goto_xy(11, 23);
	cout << "           ";
}
void Game::handle_score(Position pacman_pos) {
	if (board.get_cell(pacman_pos) == POINT)
	{
		pacman.add_score();
		if (pacman.get_score() == MAX_POINTS)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			win();
		}
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
	cout << "you won."<<endl;
	system("pause");
	loop_flag = true;
}
void Game::display_score_souls() {
	goto_xy(7, 23);
	if (color_mode)
		board.set_color(LIGHTGREEN);
	cout << pacman.get_score();
	goto_xy(7, 24);
	if (color_mode)
		board.set_color(RED);
	cout << pacman.get_souls();
}
void Game::Menu()
{
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
				Menu();
			}
			else {
				cout << "color on!" << endl << endl;
				set_color_mode(true);
				Menu();
			}
		}
		else{
			if (userChoice != 9)
			{
				cout << "pick valid choice." << endl;
				Sleep(250);
				system("cls");
				Menu();
			}
		}

	} while (userChoice != 9);
	system("cls");
	return;
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
void Game::reset_game() {//TODO
}

