#include <iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>
#include "Game.h"
#include "Player.h"
#include <windows.h>

using namespace std;

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int ch;

    while (1) {
        cout << "      ---------- Welcome to Tic-Tac-Toe! ----------" << endl;
        cout << "\t          1. 1 Player game" << endl;
        cout << "\t          2. 2 Player game" << endl;
        cout << "\t          3. Exit the game" << endl;
        cout << "      ---------------------------------------------" << endl;
        cout << endl;
        cout << "\t Select an option >> ";
        cin >> ch;
        switch (ch) {
        case 1:
        {
            Game* game = new Game;
            game->init();
            game->onePlayerGame();
        }
              break;
        case 2:
        {
            Game* game = new Game;
            game->init();
            game->twoPlayerGame();
        }
              break;
        case 3:
            return 0;
        default:
            cout << "Invalid option. Please try again.";
        }
    }
    return 0;
}