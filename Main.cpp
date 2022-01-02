#include "Game.h"
int main(int argc, char** argv) {
	cursor_visibility(false);
	Game game;

	if (argc == 1)
		game.run_menu();

	else if (argc == 2)
	{
		string str = argv[1];
		if (str.compare("-load")==0)
			game.run_load();
		else if (str.compare("-silent")==0)
			game.run_silent();
		else if (str.compare("-save")==0)
		{
			game.set_save_mode(true);
			game.run_menu();
		}
		else
		{
			//throw(dor)-todo
			cout << "ERROR" << endl;
		}
	}
	else
		game.run_menu();//for testing without cmd
		//throw(dor)-todo
		cout << "ERROR" << endl;

	return 0; 
}