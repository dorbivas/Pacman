#include "Menu.h"
/*Menu::Menu()
{
} */
void Menu::init()
{
    int userChoice = 0;
    Position pos(1, 2);
    //this->player.set_position(pos);
    cout << "\n\tWelcome to Snake. (press any key to continue)\n";
    do
    {
        cout << "Please choose LVL or 0 to escape \n\n";
        cout << "0 ==> Exit \n\n";
        cout << "1 ==> Basic    \n\n";
        cout << "2 ==> Advenced \n\n";
        cout << "3 ==> Master \n\n";

        cin >> userChoice;
        if (userChoice == 0)
            exit(0);
        else
        {
            //this->player.get_position().set_xy(33, 33);
            pos.set_xy(33, 33);
        }

    } while (userChoice != 0);
    system("cls");
    //Game g;
    //g.board_init(); 
}