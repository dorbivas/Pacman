#include "Board.h"

void Board::print_board() 
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++) 
		{
			if (board[i][j] == (unsigned char) WALL)
			{
				set_color(LIGHTMAGENTA);
				cout << board[i][j];
			}
			else if (board[i][j] == (unsigned char) POINT) 
			{
				set_color(LIGHTGREY);
				cout << board[i][j];
			}
			else if(board[i][j] == (unsigned char) TELEPORT)
			{	set_color(LIGHTBLUE);
				cout << board[i][j];
				//cout << endl << i << " : " << j << endl; "TODO remove"
			}
			else {
				set_color(WHITE);
				cout << board[i][j];
			}
		}
		cout << endl;
	}
	set_color(WHITE);
}

