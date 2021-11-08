#include "Game.h"
//#include "Packman.h"


#define MAX_BORDER_X_SIDE 79
#define MAX_BORDER_Y_SIDE 24
#define BRICK 219
#define INSIDE_BRICK 178
/// <summary>
//blabla
/// </summary>
void Game::board_init()
{
	char brick = BRICK;
	Position p1(0, 0);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < MAX_BORDER_X_SIDE; i++)
	{
		p1.set_xy(i, 0);
		//SetConsoleTextAttribute(hConsole, 120); TODO coloring
		cout << brick;
		p1.set_xy(i, MAX_BORDER_Y_SIDE - 1);
		cout << brick;
	}
	for (int i = 0; i < MAX_BORDER_Y_SIDE; i++)
	{
		//SetConsoleTextAttribute(hConsole, 250);TODO coloring
		p1.set_xy(0, i);
		cout << brick;
		p1.set_xy(MAX_BORDER_X_SIDE - 1, i);
		cout << brick;
	}
	board_inside();
}

void Game::board_inside()
{
	char brick = INSIDE_BRICK;
	Position p1(0, 0);
	for (int i = 10; i < 60; i++)
	{
		p1.set_xy(i, 10);
		cout << brick;
		p1.set_xy(i, 10 - 1);
		cout << brick;
	}
	for (int i = 10; i < 10; i++)
	{
		p1.set_xy(10, i);
		cout << brick;
		p1.set_xy(60 - 1, i);
		cout << brick;
	}
}

bool Game::is_valid_key(char c)
{
	if (c == 'a' || c == 'd' || c == 'w' || c == 's' || c == 'x' || c == 'A' || c == 'D' || c == 'W' || c == 'X' || c == 'S')
		return true;

	return false;
}


void Game::Menu()
{
	int userChoice = 0;
	Position pos(1, 2);
	//this->player.set_position(pos);
	cout << "\n\tWelcome to Snake. (press any key to continue)\n";
	do
	{
		cout << "Please choose LVL or 0 to escape \n\n";
		cout << "0 ==> Exit \n\n";
		cout << "1 ==> Basic    \n\n";
		cout << "2 ==> Advenced \n\n";
		cout << "3 ==> Master \n\n";

		cin >> userChoice;
		if (userChoice == 0)
			exit(0);
		else
		{
			//this->player.get_position().set_xy(33, 33);
			pos.set_xy(33, 33);
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
	char currentKey;
	//Pos* food = (Pos*)malloc(sizeof(Pos));

	currentKey = _kbhit();
	while (!is_valid_key(currentKey))
		currentKey = _getch();
	//Initiate(snake);
	//FoodSpread(snake, food);
	packman.get_position().set_xy(INITIAL_X, INITIAL_Y);
	//gotoxy(food->x, food->y);
	//printf("\x1b[31m$"); //first food

	while (currentKey != ESC) //&& win condition)
	{
		int dir_x = 0, dir_y = 0;   //holding the directions
		Sleep(500);			//1 second between moves
		if (_kbhit())		// if any key was hit , only if a key was hit we read what key code it was
			currentKey = _getch();

		switch (currentKey)
		{
		case right_lower_case:
		case right_upper_case:
			dir_x = 1;
			dir_y = 0;
			break;

		case left_lower_case:
		case left_upper_case:
			dir_x = -1;
			dir_y = 0;
			break;

		case up_lower_case:
		case up_upper_case:
			dir_x = 0;
			dir_y = -1;
			break;

		case down_lower_case:
		case down_upper_case:
			dir_x = 0;
			dir_y = 1;
			break;

		case stay_lower_case:
		case stay_upper_case:
			dir_x = 0;
			dir_y = 0;
			break;
		}

		Move(packman, dir_x, dir_y);//food TODO
		PrintMove(packman.get_position());
		//set_xy(150, 150);
	}
}

void Game::PrintMove(Position pos) //displaying snake
{
	char c = 230;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.set_xy(pos.get_x(), pos.get_y());
	SetConsoleTextAttribute(hConsole, 120);
	cout << c;

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