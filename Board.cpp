#include "Board.h"

void Board::our_spacial_board() {
	unsigned char default_board[MAX_HEIGHT][MAX_WIDTH] =
	{
		{S,  S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,},
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W },
		{ W, W, P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, S, S, P, W, P, P, P, P, P, P, P, P , P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P,  S, S, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W,  },
		{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
		{ W, W, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W , P, P, W, P, P, P, P, P, P, P, W, W, S, W, W, W, W, S, W, W, P, P, P, P, P, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
		{ W, W, P, P, W, P, P, W, W, W, P, P, W, S, S, S, S, S, S, S, S, S, S, S, S, W, W, P, P, W, P, P, W , P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, S, W, W, W, S, W, W,   },
		{ W, T, S, P ,P, P, P, P, P, P, P, P, W, S, S, S, S, S, S, S, S,  S, S, S,S, W, W, P, P, P, P, P, W , P, P ,P, P, P, P, P, P, P, P, W, W, S, S, S, S, S, S, W, W, P, P, P, P, P, P, P, P, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, S, W, W, W, W, W, W, W, P, P, W, P, P, W , P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W , P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W, W, W, W, W, S, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, S, S, S, S, S, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, S, W, W, W, S, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, S, S, S, S, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
		{ W, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, S, S, P, W, P, P, P, P, P, P, P, P , P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P,  S, S, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, S, T,   },
		{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W },
		{ S, 'S', 'c', 'o', 'r', 'e', ':', S , S, S, S, S, S, S, S, S,  S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,  S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,   },
		{ S, 'S', 'o', 'u', 'l', 's', ':', S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,   },

	};

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			this->board[i][j] = default_board[i][j];
		}
	}
}


void Board::print_board(const bool color_mode) {
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++) 
		{
			if (board[i][j] == (unsigned char) WALL)
			{
				if (color_mode)
					set_color((int)Color::LIGHTCYAN);
				cout << board[i][j];
			}
			else if (board[i][j] == (unsigned char) P) 
			{
				if (color_mode)
					set_color((int)Color::LIGHTGREY);
				cout << board[i][j];
				
			}
			else if(board[i][j] == (unsigned char) TELEPORT)
			{	
				if (color_mode)
					set_color((int)Color::LIGHTBLUE);
				cout << board[i][j];
			}
			else {
				if (color_mode)
					set_color((int)Color::WHITE);
				cout << board[i][j];
			}
		}
		cout << endl;
	}
	set_color((int)Color::WHITE);
}





//----------Methods-----------//

//Point Board::getRandomPoint() {
//	Point res;
//	res.setPoint(rand() % (width - 3), rand() % (height - 3));
//
//	while (getCell(res) == (char)WALL || getCell(res) == (char)PACMAN)
//		res.setPoint(rand() % (width - 3), rand() % (height - 3));
//
//	return res;
//}
/*
void Board::init_board_from_file(const char* file_name, bool& is_valid_file)
{
	// TODO: filename input check

	int size ,col = 0, row = 0, countChars = 0;
	char read;
	ifstream in_file(file_name, ios::ate);

	if (in_file.is_open() == false) 
	{
		is_valid_file = false;
		return;
	}
	else
		is_valid_file = true;
	size = in_file.tellg();
	in_file.seekg(0, in_file.beg);

	while ((countChars <= size) && (row <= MAX_HEIGHT) && (col <= MAX_WIDTH))
	{
		read = in_file.get();
		handle_board_input(read, row, col, countChars);
		col++;
		countChars++;
	}

	height = row;
	//initLegend();
	in_file.close();
}
*/
//void Board::initLegend() {
//
//	int row = legendPos.getY();
//	int col = legendPos.getX();
//
//	/*if (row >= height - 1)
//		height += 2;
//	if (col == width - 1)
//		width += 19;*/
//
//	for (int j = 0; j < 3; j++)
//		for (int i = 0; i < 20; i++)
//			board[row + j][col + i] = ' ';
//}
//
//void Board::handle_board_input(const unsigned char curr_char, int& curr_row, int& curr_col, int& countChars) 
//{
//	switch (curr_char)
//	{
//	case '\n':
//		if (curr_row == 0)
//			width = curr_col;	  // first line sets the board's width	
//		while (curr_col < width) { // handle case where current row length < first row
//			board[curr_row][curr_col] = ' ';
//			curr_col++;
//		}
//		curr_row++;
//		curr_col = -1;
//		countChars++;		  // '\n' weight as 2 chars when read from file
//		break;
//	case '@':
//		
//		pacmanPos.setPoint(curr_col, curr_row);
//		board[curr_row][curr_col] = ' ';
//		break;
//	case '$':
//		if (num_of_ghosts < 4) {
//			ghostsPos[num_of_ghosts].setPoint(curr_col, curr_row);
//			num_of_ghosts++;
//		}
//		board[curr_row][curr_col] = ' ';
//		break;
//	case '&':
//		legendPos.setPoint(curr_col, curr_row);
//		board[curr_row][curr_col] = ' ';
//		break;
//	case '%':
//		board[curr_row][curr_col] = ' ';
//		break;
//	case '#':
//		board[curr_row][curr_col] = WALL;
//		break;
//	case ' ':
//		board[curr_row][curr_col] = BREAD;
//		num_of_bread_crumbs++;
//		break;
//	default:
//		board[curr_row][curr_col] = ' ';
//		break;
//	}
//}





//const static unsigned char default_board[HEIGHT][WIDTH] =
//{
//	{S,  S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,},
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W },
//	{ W, W, P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, S, S, P, W, P, P, P, P, P, P, P, P , P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P,  S, S, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W,   },
//	{ W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
//	{ W, W, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W , P, P, W, P, P, P, P, P, P, P, W, W, S, W, W, W, W, S, W, W, P, P, P, P, P, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
//	{ W, W, P, P, W, P, P, W, W, W, P, P, W, S, S, S, S, S, S, S, S, S, S, S, S, W, W, P, P, W, P, P, W , P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, S, W, W, W, S, W, W,   },
//	{ W, T, S, P ,P, P, P, P, P, P, P, P, W, S, S, S, S, S, S, S, S,  S, S, S,S, W, W, P, P, P, P, P, W , P, P ,P, P, P, P, P, P, P, P, W, W, S, S, S, S, S, S, W, W, P, P, P, P, P, P, P, P, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, S, W, W, W, W, W, W, W, P, P, W, P, P, W , P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W , P, P, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W, W, W, W, W, S, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, S, S, S, S, S, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, S, W, W, W, W, S, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, S, W, W, W, S, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, S, S, S, S, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W , P, P, W, W, W, P, P, W, P, P, W, W, W, W, W, W, W, W, W, W, P, P, W, P, P, W, W, W, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,   },
//	{ W, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, S, S, P, W, P, P, P, P, P, P, P, P , P, P, P, P, P, P, P, W, P, P, P, P, P, P, P, P, P, P, P, P,  S, S, W, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, S, T,   },
//	{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, T, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,  W , W, W, W, W, W, W, W, W, W, W },
//	{ S, 'S', 'c', 'o', 'r', 'e', ':', S , S, S, S, S, S, S, S, S,  S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,  S, S, S, S, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,   },
//	{ S, 'S', 'o', 'u', 'l', 's', ':', S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S , S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S,   },
//};
