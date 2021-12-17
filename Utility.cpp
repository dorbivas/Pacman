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

string get_path() {
	string path_name;
	getcwd(path_name, 256);
	return path_name;
}
set<fs::path> get_files()
{
	string path_name = get_path();
	//string path_name = "c:\users\user\source\repos\pacman";
	int is_found = -1; //start as false
	// filenames are unique so we can use a set
	set<fs::path> sorted_by_name;
	for (auto& entry : fs::directory_iterator(path_name))
	{
		is_found = entry.path().string().find(".screen");
		if (is_found != -1)
		{
			sorted_by_name.insert(entry.path());
			is_found = -1;
		}
	}
	return sorted_by_name;
}
void print_files(set<fs::path> sorted_by_name)
{
	// print the files sorted by filename
	for (auto& filename : sorted_by_name)
		cout << filename.string() << endl;
}