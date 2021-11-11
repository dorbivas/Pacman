#include <random>
#include <Windows.h> 
#include "Packman.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <conio.h>

#define INITIAL_X 40
#define INITIAL_Y 12
#define WIDTH 79
#define HIGHT 24
#define OFFSET 14
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

private:
    bool bottom_hit = false, top_hit = false, right_hit = false, left_hit = false;

public:
    //void set_xy(int y, int x);
    void boarders();
    void board_init();
    void Menu();
    void game();
    void Move(Packman& packman, int dir_x, int dir_y);
    bool is_valid_key(char c);
    void print_move(Position pos);
    bool is_collided(Packman& packman);
    bool is_telepoting(Packman& packman);
    void LosePring();
    //Game();

};