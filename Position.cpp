#include "Position.h"
#include <windows.h>

Position::Position()
{
}

void Position::set_xy(int x, int y)
{
    cout.flush(); // TODO maybe other place 
    this->x = x;
    this->y = y;
    COORD pos = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}
void Position::set_x(int x)
{
    this->x = x;
}
void Position::set_y(int y)
{
    this->y = y;
}