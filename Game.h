#pragma once
#include "Pacman.h"
#include "Ghosts.h"
#include "Fruit.h"
#include "save.h"
#include "load.h"

class Game {
private:
    static const int MAX_POINTS = 100, SPEED = 150, PAUSE_X = 1, PAUSE_Y = 26; 
    Pacman pacman;
    Ghosts ghosts[Board::MAX_SIZES::MAX_GHOSTS];
    Fruit fruit;
    Board board;
    Load load;
    Save save;

    Ghost_mode ghosts_level_mode= Ghost_mode::Novice;
    vector<string> file_names;

    bool pause_flag = false;
    bool color_mode = true;
    bool loop_flag = false;
    bool first_run_done = false;
    bool fruit_is_dead = false;
    unsigned char current_key;
    bool save_mode = true;
    bool load_mode = false;

    


    class Menu {
    private:
        int user_choice = 0;
        char ghosts_level_choice;

    public:
        enum user_options { Start_Game = 1, Change_Color_Mode , Show_Ruls = 8, Exit_Game = 9 };
        enum ghosts_level_options { BEST = 'a', GOOD = 'b', NOVICE = 'c' };
        void handle_menu();
        void handle_ghosts_level(Game& run);
        void menu_display();
        void print_ruls() const;
        
        
        friend class Game; 
    };

    Menu menu;

    //--Data Members Fucns: --//
    void set_pacman(Pacman& pacman) { this->pacman = pacman; }
    Position& get_pacman_position(){ return pacman.get_position(); }
    void set_color_mode(bool color_mode_switch) { this->color_mode = color_mode_switch; }
   
    //--Game Logic Fucns: --//
    void game();
    void handle_pacman_move();
    void handle_ghost_move();
    void handle_fruit_move();
    void handle_score(Position& next_pos);
    void handle_collision();
    Position& handle_teleport(Position& pacman_pos);
    void print_move(const Position pos, Entity::Shape shape);
    void init_ghosts();
    bool is_my_teleporting(const Position& next_pos) {
        return (board.get_cell(next_pos) == (unsigned char)Board::TELEPORT);
    }
    void pause();
    void handle_key_input(const unsigned char current_key);
    void display_score_souls() const;

    void win();
    void lose();

    void load_new_board_to_play(const string& file_name);

    bool find_files();
    void load_game_from_files();

    void update_values_from_file();


public:
    Game();
    void run_menu() { menu.handle_menu(); }
    void run_load(); 
    void run_silent() { } // TODO silent = true
    void save_steps();
};

