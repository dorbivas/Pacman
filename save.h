#pragma once
#pragma once
#include "Board.h"

#pragma once
#include "Entity.h"

class Save {

public:
    void init() {
        myfile.open("steps.txt");
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