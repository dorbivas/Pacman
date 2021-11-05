#include <iostream>
#include <random>
#include "Position.h"
using namespace std;

class Packman {


private:
    int souls;
    int direction;
    Position pos;
public:
    //Packman(int s,int drection);
    int get_souls();
    int get_direction();
    void set_direction(int direction);
    Position get_position();
    void set_position(Position pos);
	int souls;
	int direction;
	Position pos;
public:
	//Packman(int s,int drection);
	int get_souls();
	int get_direction();
	void set_direction(int direction);
	Position get_position();
	void set_position(Position pos);


	//Packman();//gotoxy(33, 33); //TODO recalebrait/
	


    //Packman();//gotoxy(33, 33); //TODO recalebrait/
};