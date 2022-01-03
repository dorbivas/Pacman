#include "Game.h"
int main(int argc, char** argv) {
	cursor_visibility(false);
	Game game;
	string str;
	try
	{

		if (argc == 1) 
			game.run_menu();

		//str = argv[0];
		//if (argc == 1) 	{
		//	if (str.compare("Pacman.exe") == 0) {
		//		game.run_menu();
		//		//game.run_load(); // cd C:\Users\USER\source\repos\Pacman Pacman.exe -load 
		//	}
		//	else
		//	{
		//		throw " unvalid .exe name ";
		//	}
		//}
		
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
			{
				throw " unvalid game mode params ";
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
					throw " unvalid load mode params ";
			}
			else
			{
				throw " unvalid game mode params ";
			}

		}
		else
		{
			//game.run_menu();//for testing without cmd 
			
			throw "ya ";
		}
	}
	catch (const char* error_msg)
	{
		system("cls");
		cout << "ERROR1: " << error_msg << endl;
		system("PAUSE");
		system("cls");
		return 0;
	}
	
	return 0; 
}