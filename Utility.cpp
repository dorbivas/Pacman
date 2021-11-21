#include "Utility.h"

void goto_xy(const int x,const int y){
    cout.flush();                                   //clean the buffer before printing in this coordinate                          
    COORD pos{ (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
bool is_valid_key(const unsigned char c) {
	return (c == 'a' || c == 'd' || c == 'w' || c == 's' || c == 'x' 
         || c == 'A' || c == 'D' || c == 'W' || c == 'S' || c == 'X' || c == ESC);
}   

