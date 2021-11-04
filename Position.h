using namespace std;
#include <iostream>
//TODO valid check
class Position {

private:
	int x, y;
public:
	void gotoxy(int y, int x);
	int get_x() { return this->x; }
	int get_y() { return this->y; }

	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

};