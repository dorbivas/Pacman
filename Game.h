#pragma once
#include "Pacman.h"
#include "Ghosts.h"
#include "Entity.h"
#include <filesystem>
#include <istream>
#include <fstream>
class Game :Entity{

private:
    static const int MAX_POINTS = 30  , NUM_OF_GHOSTS = 4 , SPEED = 150,PAUSE_X=11,PAUSE_Y=24; //todo good sol ?
    /*teleports order is sync with the board from left to right */
    enum teleports {
        TP_NORTH1_TOP_X = 21,
        TP_NORTH1_TOP_Y = 1,
        TP_NORTH2_TOP_X = 53,
        TP_NORTH2_TOP_Y = 1,

        TP_NORTH1_BOT_X = 21,
        TP_NORTH1_BOT_Y = 22,
        TP_NORTH2_BOT_X = 53,
        TP_NORTH2_BOT_Y = 22,

        TP_EAST_BOT_X = 79,
        TP_EAST_BOT_Y = 21,
        TP_WEST_TOP_X = 1,
        TP_WEST_TOP_Y = 6
    };

    class Menu {
    private:
        int user_choice = 0;

    public:
        enum user_options { Start_Game = 1, Change_Color_Mode , Show_Ruls = 8, Exit_Game = 9 };
        void handle_menu();
        void menu_display();
        void print_ruls() const;
        friend class Game; //todo ?
    };

    Pacman pacman;
    Ghosts ghosts[NUM_OF_GHOSTS];
    Board board;
    Menu menu;

    bool pause_flag = false;
    bool color_mode = true;
    bool loop_flag = false;

    //--Data Members Fucns: --//
    void set_pacman(Pacman& pacman) { this->pacman = pacman; }
    Position& get_pacman_position(){ return pacman.get_position(); }
    void set_color_mode(bool color_mode_switch) { this->color_mode = color_mode_switch; }
   
    //--Game Logic Fucns: --//
    void game();
    void check_pacman_move(const Position& move_vector);
    void handle_ghost_move();
    void handle_move(Position& next_pos);
    void handle_score(Position& pacman_pos);
    Position& my_teleport(Position& next_pos);
    void handle_collision();

    bool is_collided_ghost(const Position& pacman_pos);

    bool is_my_teleporting(const Position& next_pos);
    void handle_teleport(Position& pacman_pos);
    void reset_game();
    void pause();
    Position& handle_key_input(const unsigned char current_key);
    char**  create_board();
    //--Display Fucns: --//
    void print_ruls() const;
   // void print_move(const Position pos, const unsigned char c) const;
    //void display_score_souls() const;

    void win();
    void lose();

public:
    Game();

    void run_menu() { menu.handle_menu(); } //TODO ?
};
