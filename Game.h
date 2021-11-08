#include <random>
#include <Windows.h> 
#include "Packman.h"
#include <iostream>
using namespace std;

#include <conio.h>


#define INITIAL_X 40
#define INITIAL_Y 12
#define MAX_BORDER_X_SIDE 79
#define MAX_BORDER_Y_SIDE 24
#define BRICK 219
#define INSIDE_BRICK 178

enum Keys {
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
};

class Game {


public:
    //void set_xy(int y, int x);
    void board_init();
    void boarders();
    void board_inside(Position b1, char brick);
    void Menu();
    void game();
    void Move(Packman& packman, int dir_x, int dir_y);
    bool is_valid_key(char c);
    void PrintMove(Position pos);
    //Game();

};