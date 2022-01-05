#pragma once
#include "Utility.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::vector;


class Exceptions
{
private:
	//int how_many_pacmans, num_of_ghosts, how_many_legends;
	string screen;
	vector<string> msg;

public:
	//-----member funcs----------//
	Exceptions() {};
	Exceptions(const string& _msg, const string& _screen) :
		screen(_screen) {
		msg.push_back(_msg);
	}

	//-----getters----------//
	const vector<string>& get_all_msgs() const { return msg; }
	const string& get_msg(int i) const { return msg[i]; }
	size_t get_msg_len() const { return msg.size(); }

	//-----setters----------//
	void set_msg(const string& _msg) { msg.push_back(_msg); }
	void set_screen(const string& _screen) { screen = _screen; }

	//-----display----------//
	void clear() { msg.clear(); }
	void print_exceptions() const;
};

