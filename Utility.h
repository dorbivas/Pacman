#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Position.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::srand;

enum Keys {
	up_upper_case = 87		,
	up_lower_case = 119		,
	down_upper_case = 88	,
	down_lower_case = 120	,
	right_upper_case = 68	,
	right_lower_case = 100	,
	left_upper_case = 65	,
	left_lower_case = 97	,
	stay_upper_case = 83	,
	stay_lower_case = 115	,
	ESC = 27
};

enum direction {
	UP		,
	DOWN	,
	LEFT	,
	RIGHT	,
	STAY
};
	//--Game Logic Fucns: --//
void goto_xy(const int x, const int y);
bool is_valid_key(const unsigned char c);

void conceel_cursor();
void cursor_visibility(bool showFlag);






