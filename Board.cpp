#include "Board.h"

const static unsigned char default_board[HEIGHT][WIDTH] =
{
	{S,  S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,},
	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W },
	{ W, W, P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, S, S, P, W, P, P, P, P, P, P, P, P , P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P,  S, S, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
	{ W, W, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W , P, P, W, P, P, P, P, P, P, P, W, W, S, W, W, W, W, S, W, W, P, P, P, P, P, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
	{ W, W, P, P, W, P, P, W, W, W, P, P, W, S, S, S, S, S, S, S, S, S, S, S, S, W, W, P, P, W, P, P, W , P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, S, W, W, W, S, W, W,   },
	{ W, T, S, P ,P, P, P, P, P, P, P, P, W, S, S, S, S, S, S, S, S,  S, S, S,S, W, W, P, P, P, P, P, W , P, P ,P, P, P, P, P, P, P, P, W, W, S, S, S, S, S, S, W, W, P, P, P, P, P, P, P, P, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, S, W, W, W, W, W, W, W, P, P, W, P, P, W , P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W , P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, S, W, W, W, W, W, W, S, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, S, S, S, S, S, S, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, S, W, W, W, S, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, S, S, S, S, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
	{ W, W, P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, S, S, P, W, P, P, P, P, P, P, P, P , P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P,  S, S, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, S, T,   },
	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W },
	{ S, 'S', 'c', 'o', 'r', 'e', ':', S , S, S, S, S, S, S, S, S,  S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,  S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,   },
	{ S, 'S', 'o', 'u', 'l', 's', ':', S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,   },
};

void Board::init_board() {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			this->board[i][j] = default_board[i][j];
		}
	}
}

void Board::print_board(const bool color_mode) 
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

