#include "Packman.h"

Packman::Packman()
{

}

int Packman::get_souls()
{
    return this->souls;
}

void Packman::set_souls(int souls)
{
    this->souls = souls;
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
void Packman::decrease_soul()
{
    this->souls--;
}