#pragma once
#pragma once
#include "Board.h"

#pragma once
#include "Entity.h"

class Save {

public:
    void init() {
        string file_name = "pacman_03.txt";
        string file_name=
        myfile.open(file_name);
    }
    void Write_to_file(const char buffer) {
        myfile << buffer;
    }

    void Write_to_file(const char* buffer) {
        myfile << buffer;
    }

    void Write_to_file(const int buffer) {
        myfile << buffer;
    }


    void finish() {
        myfile.close();
    }



private:

    std::ofstream myfile;
};