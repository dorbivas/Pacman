#include "Game.h"


#define MAX_BORDER_X_SIDE 79
#define MAX_BORDER_Y_SIDE 24
#define BRICK 219
#define INSIDE_BRICK 178

void Game::board_init()
{
    char brick = BRICK;
    Position p1(0, 0);
    for (int i = 0; i < MAX_BORDER_X_SIDE; i++)
    {
        p1.set_xy(i, 0);
        cout << brick;
        p1.set_xy(i, MAX_BORDER_Y_SIDE - 1);
        cout << brick;
    }
    for (int i = 0; i < MAX_BORDER_Y_SIDE; i++)
    {
        p1.set_xy(0, i);
        cout << brick;
        p1.set_xy(MAX_BORDER_X_SIDE - 1, i);
        cout << brick;
    }
    board_inside();
}

void Game::board_inside()
{
    char brick = INSIDE_BRICK;
    Position p1(0, 0);
    for (int i = 10; i < 60; i++)
    {
        p1.set_xy(i, 10);
        cout << brick;
        p1.set_xy(i, 10 - 1);
        cout << brick;
    }
    for (int i = 10; i < 10; i++)
    {
        p1.set_xy(10, i);
        cout << brick;
        p1.set_xy(60 - 1, i);
        cout << brick;
    }
}

void Game::Menu()
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




/* void Game::game()
{
    while (currentKey != ESC //&& win condition)
        {
            int dirX, dirY;    //holding the directions
            Sleep(30); //1 second between moves
            if (_kbhit()) // if any key was hit , only if a key was hit we read what key code it was
                currentKey = getKey();

            switch (currentKey)
            {
            case RIGHT: {
                dirX = 1;
                dirY = 0;
                break;
            }
            case LEFT: {
                dirX = -1;
                dirY = 0;
                break;

            }
            case UP: {
                dirX = 0;
                dirY = -1;
                break;
            }
            case DOWN: {
                dirX = 0;
                dirY = 1;
                break;
            }
            Move(snake, dirX, dirY, food);
            //PrintMove(snake);
            //set_xy(150, 150);
        }
        set_xy(food->x, food->y);
        cout << " ";
        if (currentKey == ESC)
        {
            printf("\x1b[0m");
            system("cls");
            Menu();
        }
        if (snake->size == MAX_SNAKE_SIZE)
        {
            FreeAll(snake, food);
            WinPrinter();
        }
        } */