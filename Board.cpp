#include "Board.h"

void Board::print_board(const bool color_mode) {
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			if (board[i][j] == (unsigned char)WALL)
			{
				if (color_mode)
					set_color((int)Color::LIGHTCYAN);
				my_print(board[i][j]);
			}
			else if (board[i][j] == (unsigned char)P)
			{
				if (color_mode)
					set_color((int)Color::LIGHTGREY);
				my_print(board[i][j]);

			}
			else if (board[i][j] == (unsigned char)TELEPORT)
			{
				if (color_mode)
					set_color((int)Color::LIGHTBLUE);
				my_print(board[i][j]);
			}
			else {
				if (color_mode)
					set_color((int)Color::WHITE);
				my_print(board[i][j]);
			}
		}
		cout << endl;
	}
	set_color((int)Color::WHITE);
}

void Board::load_board(const string& file_name)
{
	ifstream file(file_name, ios::ate);
	if (file.is_open())
	{
			make_board_empty();
			points_valid_positions.clear();
			board_from_file(file);
	}
	else
		//throw "B: unable to open file "; 
	
	file.close();
}

void Board::board_from_file(ifstream& file_input)
{
	int char_counter = 0, curr_col = 0, legend_flag = 0, file_size;

	bool is_first_line = false;
	unsigned char prev_char = 32;

	file_input.seekg(0, ios::end);
	file_size = file_input.tellg(); 
	file_input.seekg(0, file_input.beg);

	while (char_counter < file_size)
	{
		unsigned char curr_char = file_input.get();
		if (is_first_line == true && curr_col >= cols)
		{
			while (curr_char != '\n' && char_counter <= file_size)
			{
				char_counter++;
				curr_char = file_input.get();
			}
			if (char_counter <= file_size)
				rows++;
			
			char_counter = char_counter + 2;
			curr_col = 0;
		}
		else
		{
			if (curr_char == '#')
				board[rows][curr_col] = WALL;

			else if (curr_char == '@')
			{
				if (how_many_pacmans >= 1)
				{
					//throw ("B: more than one pacman exception ");
					
				}

				inital_pacman_pos.set_xy(curr_col, rows);
				board[rows][curr_col] = S; // pac start on empty space so he wont add score
				how_many_pacmans++;
			}

			else if (curr_char == '$')
			{
				if (num_of_ghosts >= 3)
				{
					//throw ("B: more than four ghost exception ");
			
				}

				inital_ghosts_pos[num_of_ghosts++].set_xy(curr_col, rows);
				board[rows][curr_col] = S;
			}
		
			else if (curr_char == '%')
				board[rows][curr_col] = S;

			else if (curr_char == S)
			{
				max_score++;
				curr_char = POINT;
				board[rows][curr_col] = curr_char;
			}

			else if (curr_char == '&')
			{
				if (how_many_legends >= 1)
				{
					//throw ("B: more than one legend exception ");
				 
				}

				if (is_first_line && MAX_LEGEND_COLS + curr_col > cols) // the legend_pos is out of bound
				{
					//throw ("B: out of bound exception: legend");

				}
				
				legend_pos.set_xy(curr_col, rows);
				board[rows][curr_col] = S;
				legend_flag = 1;
				how_many_legends++;
			}
			else if (char_counter + 1 == file_size || curr_char == '\n')
			{
				if (!is_first_line) 
				{
					if (curr_col > MAX_WIDTH)
					{
						//throw ("B: out of bound exception: first col ");

					}
					
					else if (legend_flag == 1 && MAX_WIDTH - legend_pos.get_x() < 20) // no space for legend_pos
					{
						//throw ("B: out of bound exception: legend");

					}
					
					if (legend_flag == 1 && legend_pos.get_x() + 19 > cols) 
						cols = legend_pos.get_x() + 19; 
					
				}
				if (is_first_line && curr_col < cols) 
				{
					insert_single_line(curr_col);
					curr_col = 0;
				}
				else
				{
					is_first_line = true;
					curr_col = 0;
				}
				char_counter++;
				rows++;

			}
			else 
			{
				board[rows][curr_col] = S; 
				char_counter++;
			}

			if (!is_first_line)
				cols++;

			if (file_size == char_counter + 1 && curr_col + 1 < cols)
				insert_single_line(curr_col + 1);
			
			if (curr_char != '\n')
			{
				curr_col++;
				prev_char = curr_char;
			}
			char_counter++;
		}
	}
	//TODO
	//system("cls");
	//board_errors.print_exceptions();
	//system("PAUSE");
	//system("cls");

	insert_teleports();
	handle_legend();
	search_points();

	
}

void Board::insert_single_line(int curr_col){
	while (curr_col < cols)
		board[rows][curr_col++] = S;
}

void Board::handle_legend()
{
	if (legend_pos.get_y() + 1 == rows)
		rows = rows + 2;
	else
		rows++;

	for (int i = 0; i < MAX_LEGEND_ROWS; i++)
	{
		for (int j = 0; j < MAX_LEGEND_COLS; j++)
		{
			if (board[legend_pos.get_y() + i][legend_pos.get_x() + j] == POINT)
				max_score--;

			board[legend_pos.get_y() + i][legend_pos.get_x() + j] = S; 
		}

		if (legend_pos.get_y() + i >= rows)
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
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			if (board[i][j] == POINT)
				points_valid_positions.push_back({ j, i });
	}
}

void Board::insert_teleports()
{

	for (int i = 0; i < cols; i++)
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

	for (int i = 0; i < rows; i++)
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
}

bool Board::is_valid_move(const Position new_pos)
{
	int x = new_pos.get_x();
	int y = new_pos.get_y();
	unsigned char curr = board[y][x];

	if (x >= cols || y >= rows || x <= 0 || y <= 0)
		return false;

	if (curr == Board::WALL)
		return false;

	return true;

}

void Board::our_spacial_board() {//EXTRA

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

