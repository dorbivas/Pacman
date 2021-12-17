#pragma once
class Position {

private:
    int x, y;

public:
    //--Constructor --//
    Position() { x = 0; y = 0; }
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
    //--Data Members Fucns: --//
    void set_xy(int _x, int _y) {x = _x; y = _y;}
    int get_x() const { return this->x; }
    int get_y() const { return this->y; }

    //--Game Logic Fucns: --//
    bool operator==(const Position& pos){return((pos.get_x()==x)&&(pos.get_y()==y));}
}; 

/*
   
    TODO dor
   
    ***done*** (no deduction) missing a dedicated Menu class for handling user input / output -
      menu option selection and printing instructions and messages (e.g. for Game::Menu, ::print_ruls)

    - (-1) use enum class rather than enum (enum Color, Direction); (-1) should use named constants / enum
      instead of literals (Game::Menu, ::pause)

    - Board enum
     ***done*** delete corsair
     *
     *
     * scan file func to find .screen
     * 
     * 
       - Speed
        slow ghost
        slow even more fruit




      TODO yarden
   

  ***done*** - (-2) objects (which are not locally created) should be returned by reference to avoid
    copy (Ghosts::get_position, Pacman::get_position); (-2) objects should be received by reference to avoid copy
   (Ghosts::set_position, Pacman::set_position)

    - (-1) logic to draw entities should be placed in entity classes and not in encompassing board
    / game class - or altogether separated from classes which handle game logic (Game::
 
        Kids
        -   shape color at entity kids init them on the constructor
        - virt funcs to kids
        - init() func which sets the initial parms every board Maybe dad do init for all




   - copy constractors delete? when we have dynemic alocations.

   


    TODO Gen
    - Finish fruit
        - fruit interaction() (with pacmen \ ghost) diffrent cases + score for pacmen 
        - place fruit() in a new unkowen board ,  (replace fruit inside current board)
        - move() from entity hertiage
        - fruit dissapere() after some time
        - only 1 or zero fruits on board = cool down in between reappears.

    - ghost LVLS
        **done** Novice = rand every 20 move
        * GOOD =  novic 5 + Smart 1-15~  BFS startegy
        * Smart
        * 
        * implement BFS in ghost class
        *       - ghost class update members need to have queue and visit matrix
        *       - pass the next pos + direction to the move func
        * implement Good in ghost class 
        *
        * to do mode enum
        * set mode

    - board File Support
       - locate file ".scree" almost done include fix
       -get num of lines function
       - get num of cells function
       
       - load the boards to matrix() - build board and fill with POINTS (?where is tp)
       - check if valid board.
       - generic tp  + support old board 
       - print score + souls in the "&" places 3 lines 20 chars max


   - game logics advence to next board
            rebuild the board live the same score
            init all parms from new board starting pos
       



    MENU - low priority
        - another mode with our custome made board.
        TODO level ghosts display


    BUGS:
    board unexpected behaver in some X Y check ?
*/