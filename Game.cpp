#include "Game.h"
void Game::Menu()
{
	int userChoice = 0;
	cout << "Welcome to \"the\" Pacman !" << endl;
	do
	{
		//HANDLE hConsole; //COLOR DEBUG
		//int k;
		//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//for (k = 1; k < 255; k++)
		//{
		//	SetConsoleTextAttribute(hConsole, k);
		//	cout << k << " I want to be nice today!  " << k << endl;
		//}
		cout << "Please select option : "<< endl << endl;
		cout << "1 ==> Start a new game" << endl << endl;
		cout << "8 ==> Present instructions and keys" << endl << endl;
		cout << "9 ==> Exit" << endl;

		cin >> userChoice;
		if (userChoice == 9)
			exit(0);
		else if (userChoice == 8)
			print_ruls();
		else
		{
			system("cls");
			this->game();
		}

	} while (userChoice != 0);
	system("cls");
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

void Game::move(Position dir_pos)// Pos* food) intreract with food TODO
{
	int dir_x = dir_pos.get_x();
	int dir_y = dir_pos.get_y();
	int x = this->pacman.get_position().get_x() + dir_x;
	int y = this->pacman.get_position().get_y() + dir_y;
	Position nextPos(x, y); //holding cordinate the snake heading to

	//if (if_move_towards_ghost(ghost.pos, const nextPos) || if_move_towards_wall(const nextPos)) //losing conditaions
	//	LoseSituation(snake, food);
	// minus soul or pressing s' - stop
	if (is_teleporting(this->pacman.get_position()))
		teleport(this->pacman);

	else if (is_collided())//with ghost
	{
		this->pacman.decrease_soul();
		//pacman.set_position(inital);
		//currentKey = stay_upper_case;
	}
	this->pacman.set_position(nextPos);
}


void Game::game()
{
	srand(time(NULL)); //start generating numbers
	Board board;
	Position inital(INITIAL_X, INITIAL_Y);
	Pacman pacman(3, 0, inital, 0);
	Position dir_pos(0, 0);

	this->set_pacman(pacman);
	unsigned char currentKey;
	unsigned char temp;

	board.printBoard();

	currentKey = _kbhit();
	while (!is_valid_key(currentKey))
		currentKey = _getch();
	 temp= currentKey;

	while (currentKey != '9') //&& win condition)
	{
		Sleep(200);			//1 second between moves
		if (_kbhit()){		// if any key was hit , only if a key was hit we read what key code it was
			currentKey = _getch();
		
		}
		if (currentKey != '9')
		{
			dir_pos = handle_movement(currentKey);
			if (this->pause_flag)
			{
				currentKey = temp;
				this->pause_flag = false;
			}
			move(dir_pos);//food TODO
			print_move(this->pacman.get_position(), (unsigned char)PACMAN_SYMBOL);
			temp = currentKey;
			if (this->pacman.get_souls() == 0)
			{
				system("cls");
				cout << "GAME OVER!!!!!" << endl;
				system("pause");
				break;
			}
		}
	}
	system("cls");
}
bool Game::is_collided()
{
	int pacman_x = this->pacman.get_position().get_x();
	int pacman_y = this->pacman.get_position().get_y();
	for (int i = 0; i < NUM_OF_GHOSTS; i++)
		return (pacman_x == this->ghosts[i].get_position().get_x() && pacman_y == this->ghosts[i].get_position().get_y());
}
bool Game::is_teleporting(Position curr_pos)//teleporting the pacman and return if teleported
{
	int Pacman_x = curr_pos.get_x();
	int Pacman_y = curr_pos.get_y();

	for (int i = 0; i < 3; i++) //bot and top teleports size is 3 blocks
	{
		if (Pacman_x == 53 + i && Pacman_y == HIGHT || Pacman_x == 53 + i && Pacman_y == 3)
			return true;
	}
	if (Pacman_y == 14 && Pacman_x == 17 || Pacman_x == WIDTH + 14)
		return true;

	return false;
}


void Game::teleport(Pacman& pacman)//teleporting the pacman and return if teleported
{
	int Pacman_x = pacman.get_position().get_x();
	int Pacman_y = pacman.get_position().get_y();

	for (int i = 0; i < 3; i++) //bot and top teleports size is 3 blocks
	{
		if (Pacman_x == 53 + i && Pacman_y == HIGHT)
		{
			pacman.set_position(Pacman_x, 3);
			//pacman.set_direction(DOWN) TODO 
		}

		if (Pacman_x == 53 + i && Pacman_y == 3)
		{
			pacman.set_position(Pacman_x, HIGHT);
			//pacman.set_direction(UP) TODO 
		}
	}

	if (Pacman_y == 14 && Pacman_x == 17)
	{
		pacman.set_position(WIDTH + 14, Pacman_y);
		//pacman.set_direction(left) TODO 
	}
	if (Pacman_y == 14 && Pacman_x == WIDTH + 14)
	{
		pacman.set_position(17, Pacman_y);
		//pacman.set_direction(right) TODO 
	}
}

void Game::pause()
{
	Position pos;
	pos.set_xy(0, 0);
	print_move(pos,0);
	cout << "\rPAUSE";
	unsigned unsigned char c = _getch();
	while (c != ESC)
	{
		c = NULL;
		c = _getch();
	}
	cout << "\r     ";
}
void Game::print_move(Position pos,unsigned char c) //displaying
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.set_xy(pos.get_x(), pos.get_y());
	SetConsoleTextAttribute(hConsole, 6);  //TODO defines COLORS
	goto_xy(pos.get_x(), pos.get_y());
	if(c!=0)
		cout << c;
}

Position Game::handle_movement(unsigned char currentKey)
{
	int dir_x = 0, dir_y = 0;
	Position pos(dir_x, dir_y);
	int pacman_x = this->pacman.get_position().get_x();
	int pacman_y = this->pacman.get_position().get_y();


	if (is_valid_key(currentKey)) //TODO FIX other keys dont need to stop Pacman
	{
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
