#include <random>
#include <Windows.h> 
#include "Packman.h"

#include <iostream>
using namespace std;


#define INITIAL_X 40
#define INITIAL_Y 12
/*
enum keyCode {
	up_upper_case = 87,
	up_lower_case = 119,
	down_upper_case = 88,
	down_lower_case = 120,
	right_upper_case = 68,
	right_lower_case = 100,
	left_upper_case = 65,
	left_lower_case = 97,
	stay_upper_case = 83,
	stay_lower_case = 115,
	ESC = 27
}keyCode;
*/
class Game {


public:
    //void set_xy(int y, int x);
    void board_init();
    void board_inside();
    void Menu();
		
    //Game();

};