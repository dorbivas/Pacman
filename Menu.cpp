#include "Menu.h"


void Menu()
{
	int userChoice = 0;
	cout<<"\n\tWelcome to Snake. (press any key to continue)\n";
	do
	{
		cout<<"Please choose LVL or 0 to escape \n\n";
		cout<<"0 ==> Exit \n\n";
		cout<<"1 ==> Basic	\n\n";
		cout<<"2 ==> Advenced \n\n";
		cout<<"3 ==> Master \n\n";

        cin >> userChoice;
        if (userChoice == 0)
            exit(0);
        else
        {
            //this->player.get_position().set_xy(33, 33);
            pos.set_xy(33, 33);
        }

	} while (userChoice != 1);
	system("cls");
	Game();
}
