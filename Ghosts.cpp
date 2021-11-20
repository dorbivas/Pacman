#include "Ghosts.h"

//--------Constructors------//

Ghosts::Ghost(){
    direction = STAY;
    pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
}

Ghosts::~Ghosts() {
}

Position Ghosts::get_position() {
    return this->pos;
}

void Ghosts::set_position(Position pos) {
    this->pos = pos;
}
void Ghosts::set_position(int x, int y)
{
    this->pos.set_xy(x, y);
}
void Ghosts::set_direction(int direction){
    this->direction = direction;
}

int Ghosts::get_direction(){
    return this->direction;
}

Position Ghost::rand_move()
{
	direction = rand() % 4;

}



Position Ghost::move_ghost()
{
	Position dir_pos;

	if (direction == UP)
	{
		dir_pos.set_xy(pos.get_X(), pos.get_Y() - 1);
	}
	else if (direction == DOWN)
	{
		dir_pos.set_xy(pos.get_X(), pos.get_Y() + 1);
	}
	else if (direction == LEFT)
	{
		dir_pos.set_xy(pos.get_X()-1, pos.get_Y());
	}
	else  //(direction == RIGHT){
		dir_pos.set_xy(pos.get_X()+1, pos.get_Y());
	}

	return dir_pos;
}



/*void Ghosts::set_direction_near()
{
    bool flag = false;
        int pacman_x=pacman_position.get_x();
    int pacman_y=pacman_position.get_y();
    
}*/


/*#include "Ghost.h"

//--------Constructors---------------------------------//

Ghost::Ghost() {
	curr_point.setPoint(16,5);
	color = RED;
	shape = (char)GHOST;
	v = UP;
	move_cntr = 0;

}

Ghost::Ghost(Point _p, Color c) {
	curr_point.setPoint(_p.getX(), _p.getY());
	color = c;
	shape = (char)GHOST;
	v = UP;
	move_cntr = 0;
}

//--------Getters and Setters---------------------------//

void Ghost::setGhost(Point p, Board& board) {
	prev_point = curr_point;
	unsigned char readVal = board.getCell(curr_point);
	switch (readVal) {
		case (unsigned char)BREAD:
			setTextColor(Color::LIGHTGREY);
			curr_point.draw((unsigned char)BREAD);
			break;
		default:
			curr_point.draw(' ');
			break;
	}
	curr_point.setPoint(p.getX(), p.getY());
	next_point = curr_point;
}

//--------Methods------------------------------------//

void Ghost::moveGhost(Board& board) {
	prev_point = next_point = curr_point;
	if (move_cntr == 20) {
		next_point.move();
		move_cntr = 0;
	}
	else
		next_point.move(v);

	unsigned char readVal = board.getCell(next_point);
	while (isEndBoard() || readVal == (unsigned char)WALL)
	 {
		if(move_cntr%5==0)
			v = (Move_Vector)(v - 1);
		else
			v = (Move_Vector)(v + 1);

		 if (v >= STAY)
			 v = UP;
		 if (v < UP)
			 v = DOWN;
		 next_point = curr_point;
		 next_point.move(v);
		 readVal = board.getCell(next_point);
	 }

	move_cntr++;
	setTextColor(Color::LIGHTGREY);
	curr_point.draw(board.getCell(curr_point));
	curr_point = next_point;
	printGhost();
}

void Ghost::printGhost() {
	setTextColor(color);
	curr_point.draw(shape);
}

bool Ghost::isEndBoard() {
	/*if*/ // return (next_point.getX() > WIDTH - 2 || next_point.getX() < 1 || next_point.getY() > HEIGHT - 1 || next_point.getY() < 1)

		;//	{
//		v = STAY;
//		return true;
//	}
//	return false;*/

/*#ifndef GHOST_H_
#define GHOST_H_
#include "Point.h"
#include "Color.h"
#include "Board.h"

class Ghost {
	Point curr_point;
	Color color;
	char shape;
	Move_Vector v;

public:
	//constructors
	Ghost();
	Ghost(Point _p, Color c);

	//setters and getters
	void setGhost(Point p, Board& board);
	Point getGhost() { return curr_point; }
	Point getGhostPrev() { return prev_point; }


	//methods
	void moveGhost(Board& board);
	void printGhost();
	void setColor(Color c) {color = c;}

private:
	int move_cntr;
	Point next_point;
	Point prev_point;

	bool isEndBoard();
};

#endif
*/