#pragma once
#include "Entity.h"

class Save {

public:

    void set_board_name(string _board_name){
        board_name = _board_name;
    }
    void set_current_key(unsigned char _current_key) { current_key = _current_key; }

    void set_ghosts_directions(int _ghosts_directions) {//TODO
        ghosts_directions.push_back(_ghosts_directions);
    }

    void clear_direction_stuck() {
        ghosts_directions.clear();
    }

    void set_fruit_direction(int _fruit_direction) {
        fruit_direction = _fruit_direction;
    }

    void set_fruit_shape(int _fruit_shape) {
        fruit_shape = _fruit_shape;
    }

    void set_fruit_pos(Position _fruit_pos) {
        fruit_pos = _fruit_pos;
    }

    void set_is_fruit_dead(bool _is_dead) {
        is_fruit_dead = _is_dead;
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

    void save_steps();

private:
    ofstream steps_file;
    string board_name;
    unsigned char current_key;
    vector<int> ghosts_directions;//TODO
    int fruit_direction;
    int fruit_shape;
    Position fruit_pos;
    bool is_fruit_dead = false;
};