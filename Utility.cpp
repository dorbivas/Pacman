#include "Utility.h"

void goto_xy(int x, int y)
{
    cout.flush(); // TODO maybe other place 
    Position pos = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}