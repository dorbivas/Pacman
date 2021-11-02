#include <iostream>
#include <random>
#include "Position.h"
using namespace std;

class Packman {
	
	
private:
	int souls;
public:
	Position pos;
	int direction;
	int get_souls()
	{
		return this->souls;
	}

	Packman() {
		gotoxy(33, 33); //TODO recalebrait
	}
	


};