#include "Board.h"

void Board::print_board(bool color_mode) 
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++) 
		{
			if (board[i][j] == (unsigned char) WALL)
			{
				if (color_mode)
					set_color(LIGHTCYAN);
				cout << board[i][j];
			}
			else if (board[i][j] == (unsigned char) POINT) 
			{
				if (color_mode)
					set_color(LIGHTGREY);
				cout << board[i][j];
				
			}
			else if(board[i][j] == (unsigned char) TELEPORT)
			{	
				if (color_mode)
					set_color(LIGHTBLUE);
				cout << board[i][j];
				//cout << endl << i << " : " << j << endl; "TODO remove";
			}
			else {
				if (color_mode)
					set_color(WHITE);
				cout << board[i][j];
			}
		}
		cout << endl;
	}
	set_color(WHITE);
}

