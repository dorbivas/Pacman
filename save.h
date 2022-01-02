#pragma once
#include "Entity.h"

class Save {

public:

    void set_board_name(string _board_name){
        board_name = _board_name;
    }
    void init_save_file() {
        string file_name = board_name.substr(0, board_name.find('.'));
        file_name += ".result";
        steps_file.open(file_name);
        if (!steps_file) {
            //throw; TODO
        }
    }
    void write_to_file(const char buffer) {
        steps_file << buffer;
    }

    void write_to_file(const char* buffer) {
        steps_file << buffer;
    }

    void write_to_file(const int buffer) {
        steps_file << buffer;
    }

    void finish_saving() {
        steps_file.close();
    }

private:
    ofstream steps_file;
    string board_name;
};