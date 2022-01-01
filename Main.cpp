#include "Game.h"
int main(/*int argc, char** argv*/) {
	cursor_visibility(false);
	Game game;	

	game.run_menu();
	return 0; 
}