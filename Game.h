#include <random>
#include <Windows.h> //Sleep
#include "Packman.h"

#define INITIAL_X 40
#define INITIAL_Y 12

enum keyCode {
	up_uper_case = 87,
	up_lower_case = 119,
	down_uper_case = 88,
	down_lower_case = 120,
	right_uper_case = 68,
	right_lower_case = 100,
	left_uper_case = 65,
	left_lower_case = 97,
	stay_uper_case = 83,
	stay_lower_case = 115,
	ESC = 27
}keyCode;

class Game {


public:
	//void gotoxy(int y, int x);
	void board_init();
	//Game();

};
