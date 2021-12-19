#include "Utility.h"

void goto_xy(const int x,const int y){
    cout.flush();      //clean the buffer before printing in this coordinate                          
    COORD pos{ (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor_visibility(bool visibility)
{
	CONSOLE_CURSOR_INFO cursor_state;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_state);
	cursor_state.bVisible = visibility; // set the cursor visibility
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_state);
}

bool is_valid_key(const unsigned char c) {
	return (c == 'a' || c == 'd' || c == 'w' || c == 's' || c == 'x' 
         || c == 'A' || c == 'D' || c == 'W' || c == 'S' || c == 'X' || c == ESC);
}   


/*
int get_num_of_lines(ifstream file)
{
	int sum=0;



	return sum;
}
int get_num_of_cells(ifstream file)
{
	int sum = 0;


	return sum;
}*/

/*
char** create_board()
{
	char** board_matrix;
	char symbol;
	//set<fs::path> get_files();
	//file1
	//

	ifstream infile;
	infile.open("test.txt");
	if (!infile) {
		cout  << "Error with infile" << endl;
		exit(-1);
	infile.getline(buf, 1024);
	infile  >> x  >> y;
	infile.close();
	int i = 0, j = 0;
	while (curr != EOF)
	{
		infile.getline(board[i], max);
		i++;
		while (curr != '\n')
		{
			//symbol = getchar
			board_matrix[i][j] = symbol;

			j++;
		}
		i++;
	}







	return board_matrix;
}
*/