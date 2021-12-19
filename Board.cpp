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
		{ W, T, S, P ,P, P, P, P, P, P, P, P, W, S, S, S, S, S, S, S, S,  S, S,S ,S, W, W, P, P, P, P, P, W , P, P ,P, P, P, P, P, P, P, P, W, W, S, S, S, S, S, S, W, W, P, P, P, P, P, P, P, P, P, P, W, W, W, W, W, W, W, W, W, W, W, W, W, W, S, W, W,   },
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
			if (board[i][j] == (unsigned char)WALL)
			{
				if (color_mode)
					set_color((int)Color::LIGHTCYAN);
				cout << board[i][j];
			}
			else if (board[i][j] == (unsigned char)P)
			{
				if (color_mode)
					set_color((int)Color::LIGHTGREY);
				cout << board[i][j];

			}
			else if (board[i][j] == (unsigned char)TELEPORT)
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



void Board::load_board(const string& file_name)
{
	ifstream file(file_name, ios::ate);
	//file.open(file_name);
	//file.open("pacman_02.screen.txt");
	if (!file)
		cout << "file empty"; //TODO

	//std::ifstream f(file_name);

	//if (f.is_open())
	//	std::cout << f.rdbuf();

	make_board_empty();
	points_valid_positions.clear();
	board_from_file(file);

	file.close();
}


void Board::board_from_file(ifstream& file_input)
{
	int char_counter = 0, curr_col = 0, legend_flag = 0, is_first_line = 0, size;
	unsigned char prev_char = 'x'; 

	size = file_input.tellg();
	file_input.seekg(0, file_input.beg);

	while (char_counter < size)
	{
		if (rows == 1)
			curr_col = curr_col; // TODO what??
		unsigned char curr_char = file_input.get();
		if (is_first_line != 0 && curr_col >= cols) // if the line is over the first line of the board
		{
			while (curr_char != '\n' && char_counter <= size) {
				char_counter++;
				curr_char = file_input.get();
			}
			if (char_counter < size)
			{
				rows++;
			}
			char_counter += 2;
			curr_col = 0;
		}
		else
		{
			if (curr_char == '#')
				board[rows][curr_col] = '#';
			
			else if (curr_char == '@')
			{
				inital_pacman_pos.set_xy(curr_col, rows);
				board[rows][curr_col] = S; // pac start on empty space so he wont add score
			}
			else if (curr_char == '%')
				board[rows][curr_col] = S;

			else if (curr_char == '$')
			{
				inital_ghosts_pos[num_of_ghosts + 1].set_xy(curr_col, rows);
				board[rows][curr_col] = S;
				num_of_ghosts++;
			}
			
			else if (curr_char == S)
			{
				max_score++;
				curr_char = POINT;
				board[rows][curr_col] = curr_char;
			}
			else if (curr_char == '&')
			{
				legend_pos.set_xy(curr_col, rows);
				board[rows][curr_col] = S;
				legend_flag = 1; // TODO
			}
			else if (curr_char == '\n')
			{
				if (is_first_line == 0 && legend_flag == 1) 
				{
					if (legend_pos.get_x() + 19 > cols) 
						cols = legend_pos.get_x() + 19; 
				}
				if (is_first_line != 0 && curr_col < cols) 
				{
					insert_single_line(curr_col);
					curr_col = 0;
				}
				else
				{
					is_first_line = 1;
					curr_col = 0;
				}
				char_counter++;
				rows++;
			}
			else // if its unvalid char
			{
				board[rows][curr_col] = S; 
				char_counter++;
			}

			if (char_counter + 1 == size && curr_col + 1 < cols) 
				insert_single_line(curr_col + 1);

			if (is_first_line == 0)
				cols++;

			if (curr_char != '\n')
			{
				curr_col++;
				prev_char = curr_char;
			}
			char_counter++;
		}
	}
	insert_teleports();
	handle_legend(legend_pos);
	search_points();
}


void Board::insert_single_line(int curr_col)
{
	while (curr_col < cols)
	{
		board[rows][curr_col] = S;
		curr_col++;
	}
	//TODO 		
	//while (curr_col < cols)
	//	board[rows][curr_col++] = S;
}

void Board::handle_legend(const Position& legend_pos)
{
	if (legend_pos.get_y() == rows) // if the legend is the last line
		rows += 2;

	for (int i = 0; i < MAX_LEGEND_ROWS; i++)
	{
		for (int j = 0; j < MAX_LEGEND_COLS; j++)
		{
			if (board[legend_pos.get_y() + i][legend_pos.get_x() + j] == POINT)
				max_score--;

			board[legend_pos.get_y() + i][legend_pos.get_x() + j] = S; // clear the legend space.	
		}
		if (legend_pos.get_y() + i > rows)
			rows++;
	}
}

void Board::make_board_empty() {
	for (int i = 0; i < MAX_HEIGHT; i++) {
		for (int j = 0; j < MAX_WIDTH; j++)
			board[i][j] = S;
	}
	rows = 0; cols = 0; num_of_ghosts = 0; max_score = 0;
}


void Board::search_points() {
	for (int i = 0; i <= rows; i++) {
		for (int j = 0; j <= cols; j++)
		{
			if (board[i][j] == POINT)
				points_valid_positions.push_back({ j, i });

		}
	}
}

void Board::insert_teleports()
{
	for (int i = 0; i <= rows; i++)
	{
		if (board[i][0] == POINT) 
		{
			max_score--;
			board[i][0] = S;
		}
		if (board[i][cols - 1] == POINT)
		{
			board[i][cols - 1] = S;
			max_score--;
		}
	}
	for (int i = 0; i <= cols; i++)
	{
		if (board[0][i] == POINT)
		{
			max_score--;
			board[0][i] = S;
		}
		if (board[rows][i] == POINT)
		{
			max_score--;
			board[rows][i] = S;
		}
	}

}


bool Board::is_valid_move(const Position new_pos)
{
	int x = new_pos.get_x();
	int y = new_pos.get_y();
	unsigned char curr = board[x][y];

	if (x >= cols || y >= rows || x <= 0 || y <= 0)
		return false;

	if (curr == Board::WALL)
		return false;

	return true;

}






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