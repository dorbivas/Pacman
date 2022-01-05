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
    string screen;
    vector<string> error_msgs;

public:
    //-----member funcs----------//
    Exceptions() {};
    Exceptions(const string& _msg, const string& _screen) :
        screen(_screen) {
        error_msgs.push_back(_msg);
    }

    //-----getters----------//
    const vector<string>& get_all_msgs() const { return error_msgs; }
    const string& get_msg(int i) const { return error_msgs[i]; }
    size_t get_msg_len() const { return error_msgs.size(); }

    //-----setters----------//
    void set_msg(const string& _msg) { error_msgs.push_back(_msg); }
    void set_screen(const string& _screen) { screen = _screen; }

    //-----display----------//
    void clear() { error_msgs.clear(); }
    void print_exceptions() const;
};

