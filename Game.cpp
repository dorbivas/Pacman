#include "Game.h"

#define MAX_BORDER_X_SIDE 79
#define MAX_BORDER_Y_SIDE 24


void Game::board_init()
{
    Position p1(0, 0);
    for (int i = 0; i < MAX_BORDER_X_SIDE; i++)
    {
        p1.set_xy(i, 0);
        cout << "#";
        p1.set_xy(i, MAX_BORDER_Y_SIDE - 1);
        cout << "#";
    }
    for (int i = 0; i < MAX_BORDER_X_SIDE; i++)
    {
        p1.set_xy(0, i);
        cout << "#";
        p1.set_xy(MAX_BORDER_X_SIDE - 1, i);
        cout << "#";
    }
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