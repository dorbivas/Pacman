#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Position.h"
#include <filesystem>
#include <istream>
#include <fstream>
#include <charconv>
#include<set>
using std::set;
using std::ifstream;
using std::ios;
using std::cout;
using std::cin;
using std::endl;
using std::string;

using std::srand;
using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::filesystem::current_path;


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

	//--Game Logic Fucns: --//
void goto_xy(const int x, const int y);
bool is_valid_key(const unsigned char c);

void cursor_visibility(bool showFlag);
void my_print(string str);
void my_print(unsigned char c);
