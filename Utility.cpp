#include "Utility.h"

void goto_xy(int x, int y)
{
    cout.flush(); // TODO maybe other place 
    COORD pos{ (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
bool is_valid_key(unsigned char c) {
	return (c == 'a' || c == 'd' || c == 'w' || c == 's' || c == 'x' || c == 'A' || c == 'D' || c == 'W' || c == 'X' || c == 'S' || c == ESC);
}   

