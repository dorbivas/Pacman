#include "Game.h"
int main(int argc, char** argv) {
	cursor_visibility(false);
	Game game;
	string str;

	if (argc == 1)
		game.run_menu();

	else if (argc == 2)
	{
		str = argv[1];
		if (str.compare("-load")==0)
			game.run_load();
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
	else if (argc == 3)
	{
		str = argv[1];
		if (str.compare("-load") == 0)
		{
			str = argv[2];
			if (str.compare("-silent") == 0)
				game.run_silent();
			else
				cout << "ERROR";//TODO EXCEPTIONS (not silent)
		}
		else
			cout << "error";//TODO EXCEPTIONS (notload)

	}
	else
	{
		game.run_menu();//for testing without cmd
		//throw(dor)-todo
		cout << "ERROR" << endl;
	}
	return 0; 
}