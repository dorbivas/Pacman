#include "Position.h"
class Ghosts
{

private:
    Position pos;

public:
    //constructors
    Ghosts();
    ~Ghosts();

    Position get_position();
    void set_position(Position pos);
    void set_position(int x, int y);
};
