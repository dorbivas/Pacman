#include "Utility.h"

bool IS_SILENT = false; // TODO: comment

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

void my_print(string str)
{
    if (!IS_SILENT)
        cout << str;
}

void my_print(unsigned char c)
{
    if (!IS_SILENT)
        cout << c;
}