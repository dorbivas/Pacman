#include "Game.h"

void Game::board_init()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7); /*COLOR TABLE TODO*/
	ifstream board("Board.txt");
	if (!board) { // file couldn't be opened
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	string line;
	getline(board, line);
	while (getline(board , line))
		cout << line << endl;


}

void Game::boarders() 
{
	char brick = BRICK;
	Position b1(0, 0);
	for (int i = 0; i < WIDTH; i++)
	{
		b1.set_xy(i, 0);
		//SetConsoleTextAttribute(hConsole, 120); TODO coloring
		cout << brick;
		b1.set_xy(i, HIGHT - 1);
		cout << brick;
	}
	for (int i = 0; i < HIGHT; i++)
	{
		//SetConsoleTextAttribute(hConsole, 250);TODO coloring
		b1.set_xy(0, i);
		cout << brick;
		b1.set_xy(WIDTH - 1, i);
		cout << brick;
	}
}


bool Game::is_valid_key(char c)
{
	if (c == 'a' || c == 'd' || c == 'w' || c == 's' || c == 'x' || c == 'A' || c == 'D' || c == 'W' || c == 'X' || c == 'S'|| c == ESC||c == 9)
		return true;

	return false;
}


void Game::Menu()
{
	int userChoice = 0;
	Position pos(1, 2);
	//this->player.set_position(pos);
	
	cout << "Welcome to Ppackman. (press any key to continue)\n";
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

		cout << "Please choose LVL or 0 to escape \n\n";
		cout << "1 ==> Start a new game    \n\n";
		cout << "8 ==> Present instructions and keys \n\n";
		cout << "9 ==> EXIT \n\n";

		cin >> userChoice;
		if (userChoice == 9)
			exit(0);
		else
		{
			system("cls");
			this->board_init();
			this->game();
		}

	} while (userChoice != 0);
	system("cls");
	//Game g;
	//g.board_init(); 
}

void Game::Move(Packman& packman, int dir_x, int dir_y)// Pos* food) intreract with food TODO
{
	int x = packman.get_position().get_x() + dir_x;
	int y = packman.get_position().get_y() + dir_y;
	Position nextPos(x, y); //holding cordinate the snake heading to

	//if (if_move_towards_ghost(ghost.pos, const nextPos) || if_move_towards_wall(const nextPos)) //losing conditaions
	//	LoseSituation(snake, food);
	// minus soul or pressing s' - stop


	// bool ifAteFood = PosEqual(nextPos, *food); TODO future fruit
		//if (ifAteFood)
			//FoodInteract(snake, food);

	packman.set_position(nextPos);
}


void Game::game()
{
	srand(time(NULL)); //start generating numbers
	Packman packman;
	Position inital(INITIAL_X, INITIAL_Y);
	packman.set_direction(0);
	packman.set_souls(3);
	packman.set_position(inital);
	char currentKey;
	//Pos* food = (Pos*)malloc(sizeof(Pos));

	currentKey = _kbhit();
	while (!is_valid_key(currentKey))
		currentKey = _getch();
	char temp = currentKey;
	//Initiate(snake);
	//FoodSpread(snake, food);
	//packman.get_position().set_xy(INITIAL_X, INITIAL_Y);
	//gotoxy(food->x, food->y);
	//printf("\x1b[31m$"); //first food

	while (currentKey != '9') //&& win condition)
	{
		int dir_x = 0, dir_y = 0;   //holding the directions
		Sleep(400);			//1 second between moves
		if (_kbhit())		// if any key was hit , only if a key was hit we read what key code it was
			currentKey = _getch();
		if (is_valid_key(currentKey)) //TODO FIX other keys dont need to stop packman
		{
			switch (currentKey)
			{
				case right_lower_case:
				case right_upper_case:
					if (!this->right_hit)
					{
						dir_x = 1;
						dir_y = 0;
					}
					else
						currentKey = stay_lower_case;
					break;

				case left_lower_case:
				case left_upper_case:
					if (!this->left_hit)
					{
						dir_x = -1;
						dir_y = 0;
					}
					else
						currentKey = stay_lower_case;
					break;
				case up_lower_case:
				case up_upper_case:
					if (!this->top_hit)
					{
						dir_x = 0;
						dir_y = -1;
					}
					else
						currentKey = stay_lower_case;
					break;
				case down_lower_case:
				case down_upper_case:
					if (!this->bottom_hit)
					{
						dir_x = 0;
						dir_y = 1;
					}
					else
						currentKey = stay_lower_case;
					break;
				case stay_lower_case:
				case stay_upper_case:
					dir_x = 0;
					dir_y = 0;
					break;
				case ESC://PAUSE
					cout << "pause" << endl;//fflush
					char c = _getch();
					while (c != ESC)
					{
						c = NULL;
						c = _getch();
					}
					currentKey = temp;	
			}
			temp = currentKey;
		}
		Move(packman, dir_x, dir_y);//food TODO
		print_move(packman.get_position());
		/*if (packman.get_position().get_y() == HIGHT)
			this->top_hit = true;
		if (packman.get_position().get_x() == WIDTH)
			this->right_hit = true;*/
		if (is_collided(packman))//with ghost
		{
			packman.decrease_soul();
			packman.set_position(inital);
			currentKey = stay_upper_case;
		}
		if (packman.get_souls() == 0)
		{
			system("cls");
			cout << "GAME OVER!!!!!" << endl;
			system("pause");
			break;
		}
	}
	system("cls");
}
bool Game::is_collided(Packman& packman)//with ghost
{
	int packman_x = packman.get_position().get_x();
	int packman_y = packman.get_position().get_y();
	if (packman_x == WIDTH + 14 || packman_x == 17 || packman_y == HIGHT || packman_y == 3)
	{
		//if (!is_telepoting(packman))
			return true;
	}
	return false;
}

bool Game::is_telepoting(Packman& packman)//with ghost
{
	int packman_x = packman.get_position().get_x();
	int packman_y = packman.get_position().get_y();
	
	for (int i = 0; i < 3; i++) //bot and top teleports size is 3 blocks
	{
		if (packman_x == 53 + i && packman_y == HIGHT || packman_x == 53 + i && packman_y == 3)
			return true;
	}
	
	if (packman_y == 15 && packman_x == 17 || packman_x == WIDTH + 14)
		return true;

	return false;

}

void Game::print_move(Position pos) //displaying snake
{
	char c = 233; //TODO defines
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.set_xy(pos.get_x(), pos.get_y());
	SetConsoleTextAttribute(hConsole, 6);  //TODO defines COLORS
	cout << c;

}


void Game::LosePring() //displaying snake
{

}


//set_xy(food->x, food->y);
//cout << " ";
//if (currentKey == ESC)
//{
//	printf("\x1b[0m");
//	system("cls");
//	Menu();
//}
//if (snake->size == MAX_SNAKE_SIZE)
//{
//	FreeAll(snake, food);
//	WinPrinter();
//}
//	}
//}