#include "Game.h"
int main(int argc, char** argv) {
	cursor_visibility(false);
	Game game;
	string str, error_main = " unvalid args ";

	try
	{
		if (argc == 1)
		{
			game.run_menu();
		}

		else if (argc == 2)
		{
			str = argv[1];
			if (str.compare("-load") == 0)
				game.run_load();
			else if (str.compare("-save") == 0)
			{
				game.set_save_mode(true);
				game.run_menu();
			}
			else
				throw error_main;
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
					throw error_main;
			}
			else if (str.compare("-save") == 0)
			{
				str = argv[2];
				if (str.compare("-silent") == 0)
				{
					game.set_save_mode(true);
					game.run_menu();
				}
				else
					throw error_main;
			}
			else
				throw error_main;
		}
		else
			throw " Main unexpected behavior ";
		
	}
	catch (const char* error_msg)
	{
		system("cls");
		cout << "ERROR: " << error_msg << endl;
		system("PAUSE");
		system("cls");
		return 0;
	}
	catch (const string error_msg)
	{
		system("cls");
		cout << "ERROR: " << error_msg << endl;
		system("PAUSE");
		system("cls");
		return 0;
	}
	
	return 0; 
}