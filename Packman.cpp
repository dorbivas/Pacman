#include "Packman.h"

/*void Packman::gotoxy(int y, int x) {
	cout << "\x1b[%d;%df" << x + 1 << y + 1;
}*/

int Packman::get_souls()
{
    return this->souls;
}
int Packman::get_direction()
{
    return this->direction;
}
void Packman::set_direction(int direction)
{
    this->direction = direction;
}
Position Packman::get_position()
{
    return this->pos;
}
void Packman::set_position(Position pos)
{
    this->pos = pos;
}
/* void Packman::set_xy(int y, int x) {
    cout << "\x1b[%d;%df" << x + 1 << y + 1;
} */