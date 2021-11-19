#include "Utility.h"

/*
Kirsh corner ; the dungion for anciant syntax
- enum char replace define of an ascii memer
- getline include std? using std::basic_istream;

*/

void goto_xy(int x, int y)
{
    cout.flush(); // TODO maybe other place 
    COORD pos{ x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
bool is_valid_key(unsigned char c) {
	return (c == 'a' || c == 'd' || c == 'w' || c == 's' || c == 'x' || c == 'A' || c == 'D' || c == 'W' || c == 'X' || c == 'S' || c == ESC);
}
bool compare_pos(Position A, Position B){
return ((A.get_x() == B.get_x()) && (A.get_y() == B.get_y())); }
