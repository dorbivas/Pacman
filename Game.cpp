#include "Game.h"
void Game::Menu()
{
	int userChoice = 0;
	cout << "Welcome to \"the\" Pacman !" << endl;
	do
	{
		cout << "Please select option : " << endl << endl;
		cout << "1 ==> Start a new game" << endl << endl;
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
			this->game();
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

void Game::handle_score(Position pacman_pos) {
	if (board.get_cell(pacman_pos) == POINT)
	{
		this->pacman.add_score();
		if (this->pacman.get_score() == MAX_POINTS)
			win();
	}
}
bool Game::lose() {
	if (this->pacman.get_souls() == 0)
	{
		cout << "you lost.";
		system("cls");
		system("pause");
		return true;
	}
	//reset_game()	
}
void Game::win() {
	cout << "you won.";
	//reset_game() TODO

}
void Game::reset_game() {
}

void Game::move(Position dir_pos) {
	if(is_teleporting(this->pacman.get_position()))
		print_move(this->pacman.get_position(),TELEPORT);
	else
		print_move(this->pacman.get_position(), ' ');

	int dir_x = dir_pos.get_x();
	int dir_y = dir_pos.get_y();

	int x = this->pacman.get_position().get_x() + dir_x;
	int y = this->pacman.get_position().get_y() + dir_y;
	Position next_pos(x, y);

	handle_move(next_pos);
}

void Game::handle_move(Position next_pos) {

	if (is_invalid_place(next_pos))
		return;
	else
	{
		if (is_teleporting(next_pos))
			next_pos=teleport(next_pos);
	
		if (is_collided_ghost())//with ghost
		{
			this->pacman.decrease_soul();
			next_pos.set_xy(INITIAL_X, INITIAL_Y);
		}
		else if(this->pacman.get_souls() == 0)
		{
			
		}
		else
			handle_score(next_pos);

		this->pacman.set_position(next_pos);
	}
}


void Game::game()
{
	bool loop_flag = false;
	Position inital(INITIAL_X, INITIAL_Y);
	Pacman pacman(NUM_OF_SOULS, STAY, inital, INIT_SCORE);
	Position dir_pos(0, 0);

	this->set_pacman(pacman);
	unsigned char currentKey;
	unsigned char temp;

	srand(time(NULL)); //start generating numbers

	//print_move(this->ghosts[0].get_position(), GHOST_SYMBOL);
	this->board.print_board(); //check if true

	currentKey = _kbhit();
	while (!is_valid_key(currentKey))
		currentKey = _getch();
	temp = currentKey;
	//if (is_valid_key(currentKey)) //TODO FIX other keys dont need to stop Pacman
	while (!loop_flag) //&& win condition)
	{
		Sleep(100);			//1 second between moves
		if (_kbhit())	// if any key was hit , only if a key was hit we read what key code it was
			currentKey = _getch();
		if (is_valid_key(currentKey))
		{
			dir_pos = handle_key_input(currentKey);
			if (this->pause_flag)
			{
				currentKey = temp;
				this->pause_flag = false;
			}
			move(dir_pos);
			print_move(this->pacman.get_position(), (unsigned char)PACMAN_SYMBOL);
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
}

bool Game::is_collided_ghost()
{
	int pacman_x = this->pacman.get_position().get_x();
	int pacman_y = this->pacman.get_position().get_y();

	for (int i = 0; i < NUM_OF_GHOSTS; i++)
		return (pacman_x == this->ghosts[i].get_position().get_x() && pacman_y == this->ghosts[i].get_position().get_y());
}
bool Game::is_invalid_place(Position next_pos){
	return (this->board.get_cell(next_pos) == (unsigned char)WALL);
}
bool Game::is_teleporting(Position next_pos)//teleporting the pacman and return if teleported
{
	int Pacman_x = next_pos.get_x();
	int Pacman_y = next_pos.get_y();

	if (Pacman_x == 53 && Pacman_y == HIGHT || Pacman_x == 53  && Pacman_y == 3)

	for (int i = 0; i < 3; i++) //bot and top teleports size is 3 blocks
	{
		if (Pacman_x == 53 + i && Pacman_y == HIGHT || Pacman_x == 53 + i && Pacman_y == 3)
			return true;
	}
	if (Pacman_y == 14 && Pacman_x == 17 || Pacman_x == WIDTH + 14)
		return true;

	return false;
}

Position Game::teleport(Position next_pos)//teleporting the pacman and return if teleported
{
	int Pacman_x = next_pos.get_x();
	int Pacman_y = next_pos.get_y();

	for (int i = 0; i < 2; i++)
	{
		if (Pacman_x == 1 && Pacman_y == 21 + i)
		{
			next_pos.set_xy(24, 21 + i); //TODO magik numbers
			this->pacman.set_direction(UP);
			//return;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (Pacman_x == 24 && Pacman_y == 21 + i)
		{
			next_pos.set_xy(1 , 21 + i); //TODO magik numbers
			this->pacman.set_direction(DOWN);
			//return;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (Pacman_x == 1 && Pacman_y == 53 + i)
		{
			next_pos.set_xy(24, 53 + i); //TODO magik numbers
			this->pacman.set_direction(UP);
			//return;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		//if (Pacman_x == 24 && Pacman_y == 53 + i)
		if (Pacman_y == 24 && Pacman_x == 53 + i)
		{
			next_pos.set_xy(1, 53 + i); //TODO magik numbers
			this->pacman.set_direction(DOWN);
			//return;
		}
	}

	if (Pacman_x == 1 && Pacman_y == 6)
	{
		next_pos.set_xy(23, 79); //TODO magik numbers
		this->pacman.set_direction(RIGHT);
		//return;
	}
	if (Pacman_x == 23 && Pacman_y == 79)
	{
		next_pos.set_xy(1, 6); //TODO magik numbers
		this->pacman.set_direction(LEFT);
		//return;
	}
	for (int i = 0; i < 2; i++)
	{
		if (Pacman_x == 53 + i && Pacman_y == 3)
		{
			next_pos.set_xy(1, 6); //TODO magik numbers
			this->pacman.set_direction(RIGHT);
			//return;
		}
	}
	return next_pos;
}

void Game::pause(){
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
void Game::print_move(Position pos, unsigned char c) //displaying
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.set_xy(pos.get_x(), pos.get_y());
	SetConsoleTextAttribute(hConsole, 6);  //TODO defines COLORS
	goto_xy(pos.get_x(), pos.get_y());
	if (c != 0)
		cout << c;
}

Position Game::handle_key_input(unsigned char currentKey)
{
	int dir_x = 0, dir_y = 0;
	Position pos(dir_x, dir_y);
	int pacman_x = this->pacman.get_position().get_x();
	int pacman_y = this->pacman.get_position().get_y();
	switch (currentKey)
	{
	case right_upper_case:
	case right_lower_case:
		dir_x = 1;
		dir_y = 0;
		this->pacman.set_direction(RIGHT);
		break;

	case left_upper_case:
	case left_lower_case:
		dir_x = -1;
		dir_y = 0;
		this->pacman.set_direction(LEFT);
		break;

	case up_upper_case:
	case up_lower_case:
		dir_x = 0;
		dir_y = -1;
		this->pacman.set_direction(UP);
		break;

	case down_upper_case:
	case down_lower_case:
		dir_x = 0;
		dir_y = 1;
		this->pacman.set_direction(DOWN);
		break;

	case stay_upper_case:
	case stay_lower_case:
		dir_x = 0;
		dir_y = 0;
		this->pacman.set_direction(STAY);
		break;

	case ESC://PAUSE
		pause();
		this->pause_flag = true;
		break;
	}
	pos.set_xy(dir_x, dir_y);
	return pos;

}


//void Game::board_init()
//{
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, 7); /*COLOR TABLE TODO*/
//	ifstream board1("Board.txt");
//	if (!board1) { // file couldn't be opened
//		cerr << "Error: file could not be opened" << endl;
//		exit(1);
//	}
//	string line;
//	getline(board1, line);
//	while (getline(board1, line))
//		cout << line << endl;
//}

//void Game::board_init()
//{
//}
//
//void Game::boarders()
//{
//	unsigned char brick = BRICK;
//	Position b1(0, 0);
//	for (int i = 0; i < WIDTH; i++)
//	{
//		b1.set_xy(i, 0);
//		//SetConsoleTextAttribute(hConsole, 120); TODO coloring
//		cout << brick;
//		b1.set_xy(i, HIGHT - 1);
//		cout << brick;
//	}
//	for (int i = 0; i < HIGHT; i++)
//	{
//		//SetConsoleTextAttribute(hConsole, 250);TODO coloring
//		b1.set_xy(0, i);
//		cout << brick;
//		b1.set_xy(WIDTH - 1, i);
//		cout << brick;
//	}
//}
