#include "Game.h"

Game::Game(){
	srand(time(NULL)); //start generating rand numbers for ghost dir
}

void Game::game() {
	reset_game();
	Position move_vector(0, 0);
	unsigned char currentKey, temp;
	currentKey = _kbhit();

	while (!is_valid_key(currentKey))
		currentKey = _getch();
	temp = currentKey;

	while (!loop_flag)
	{
		Sleep(200);	
		handle_ghost_move();
		if (_kbhit())	
			currentKey = _getch();
		if (is_valid_key(currentKey))
		{
			move_vector = handle_key_input(currentKey);
			if (pause_flag)
			{
				currentKey = temp;
				pause_flag = false;
			}

			if (is_collided_ghost(pacman.get_position()))
			{
				pacman.decrease_soul();
				print_move(pacman.get_position(), (unsigned char)GHOST_ICON);
				pacman.set_position(Position(INITIAL_X, INITIAL_Y));
				if (pacman.get_souls() == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					lose();
				}
				continue;
			}
			check_pacman_move(move_vector);
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
void Game::check_pacman_move(const Position move_vector) {
	if (is_teleporting(pacman.get_position()))
	{
		board.set_cell(pacman.get_position(), (unsigned char)TELEPORT);
		print_move(pacman.get_position(), (unsigned char)TELEPORT);
	}
	else
	{
		board.set_cell(pacman.get_position(), ' ');
		print_move(pacman.get_position(), ' ');
	}

	int next_x = pacman.get_position().get_x() + move_vector.get_x();
	int next_y = pacman.get_position().get_y() + move_vector.get_y();
	Position next_pos(next_x, next_y);

	handle_move(next_pos);
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
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
	{
		curr_pos = ghosts[i].get_position();
		next_pos = ghosts[i].move_ghost();
		while (is_invalid_place(next_pos) || board.get_cell(next_pos) == (unsigned char)TELEPORT)
		{
			ghosts[i].rotate_direction();
			next_pos = ghosts[i].move_ghost();
		}

		ghosts[i].set_position(next_pos);

		if (board.get_cell(curr_pos) == (unsigned char)POINT)
		{
			board.set_cell(curr_pos, (unsigned char)POINT);
			print_move(curr_pos, (unsigned char)POINT);
		}
		else
			print_move(curr_pos, ' ');
		
		print_move(next_pos, GHOST_ICON);
	}
}

void Game::print_move(const Position pos, const unsigned char c) const {
	display_score_souls();
	if (this->color_mode)
	{
		if (c == POINT)
			board.set_color(WHITE);
		else if (c == TELEPORT)
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

bool Game::is_collided_ghost(const Position pacman_pos) {
	int d1, d2, x_dif, y_dif;
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
	{
		if (ghosts[i].get_position() == pacman.get_position())
			return true;

		d1 = ghosts[i].get_direction();
		d2 = pacman.get_direction();
		x_dif = pacman_pos.get_x() - ghosts[i].get_position().get_x();
		y_dif = pacman_pos.get_y() - ghosts[i].get_position().get_y();
		Position dif(x_dif, y_dif);

		if (d1 == UP && d2 == DOWN && dif == Position(0, 1) ||
			d1 == DOWN && d2 == UP && dif == Position(0, -1) ||
			d1 == LEFT && d2 == RIGHT && dif == Position(-1, 0) ||
			d1 == RIGHT && d2 == LEFT && dif == Position(1, 0))
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
Position Game::handle_teleport(Position next_pos) { //teleporting the pacman and return if teleported
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

Position Game::handle_key_input(const unsigned char currentKey) {
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
void Game::display_score_souls() const {
	goto_xy(7, 23);
	if (color_mode)
		board.set_color(LIGHTGREEN);
	cout << pacman.get_score();
	goto_xy(7, 24);
	if (color_mode)
		board.set_color(RED);
	cout << pacman.get_souls();
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
				Menu();
			}
			else 
			{
				cout << "color on!" << endl << endl;
				set_color_mode(true);
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

