// Code referenced here, made changes to try and not make it the same: https://pencilprogrammer.com/cpp-programs/tic-tac-toe-game/
#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Player.h"
#include <windows.h>
#pragma once

using namespace std;

typedef struct {
    int* row;
}WinList;

class Game
{
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, computerPlayer;
    int emptyCount;
    WinList winList[8];

    void displayBoard()
    {
        cout << endl;
        cout << "                    |   |   " << endl;
        cout << "                  " << board[0] << " | " << board[1] << " | " << board[2] << endl;
        cout << "                    |   |   " << endl;
        cout << "                 -----------" << endl;
        cout << "                    |   |   " << endl;
        cout << "                  " << board[3] << " | " << board[4] << " | " << board[5] << endl;
        cout << "                    |   |   " << endl;
        cout << "                 -----------" << endl;
        cout << "                    |   |   " << endl;
        cout << "                  " << board[6] << " | " << board[7] << " | " << board[8] << endl;
        cout << "                    |   |   " << endl;
        cout << endl;
    }

    void computerInput()
    {
        int pos;
        pos = rand() % 10;
        if (emptyIndex[pos] == 1)
        {
            if (emptyCount < 0)
            {
                return;
            }
            computerInput();
        }
        else
        {
            cout << "\tComputer chose: " << pos + 1 << endl;
            emptyIndex[pos] = 1;
            emptyCount -= 1;
            board[pos] = 'O';
        }
    }

    void playerInput(Player& player)
    {
        int pos;
        cout << endl;
        cout << "\t" << player.getName() << "'s Turn" << endl;
        cout << "\tEnter position >>";
        cin >> pos;
        pos -= 1;
        if (emptyIndex[pos] == 1)
        {
            cout << "-----That won't work. Please try again-----" << endl;
            playerInput(player);
        }
        else
        {
            emptyIndex[pos] = 1;
            emptyCount -= 1;
            player.getName().compare("Player 1") == 0 ? board[pos] = 'X' : board[pos] = 'O';
        }
    }

    void checkWin(Player& p1, Player& p2)
    {
        int i, j, k;
        bool flag = false;
        char first_symbol;
        for (i = 0;i < 8;i++)
        {
            first_symbol = board[winList[i].row[0]];
            if ((first_symbol != 'X') && (first_symbol != 'O'))
            {
                flag = false;
                continue;
            }
            flag = true;
            for (j = 0;j < 3;j++) {
                if (first_symbol != board[winList[i].row[j]]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                gameOn = 0;
                if (first_symbol == 'X') {
                    cout << "\t-----------------------" << endl;
                    cout << "\t     Player 1 wins!" << endl;
                    cout << "\t-----------------------" << endl;
                    p1.won();
                }
                else {
                    p2.won();
                    if (computerPlayer) {
                        cout << "\t-----------------------" << endl;
                        cout << "\tThe Computer wins!" << endl;
                        cout << "\t-----------------------" << endl;
                    }
                    else {
                        cout << "\t-----------------------" << endl;
                        cout << "\t     Player 2 wins!" << endl;
                        cout << "\t-----------------------" << endl;

                    }
                }
                displayScore(p1, p2);
                break;
            }
        }
    }

    void play(Player& p1, Player& p2)
    {
        char rematch = '\0';
        int hand = 0;
        gameOn = 1;
        displayBoard();
        while ((emptyCount > 0) && (gameOn != 0))
        {
            if (computerPlayer)
            {
                hand == 1 ? computerInput() : playerInput(p2);
            }
            else
            {
                hand == 1 ? playerInput(p1) : playerInput(p2);
            }
            hand = !hand;
            displayBoard();
            checkWin(p1, p2);
        }
        if (emptyCount <= 0)
        {
            cout << "\t-----------------------" << endl;
            cout << "\t It's a tie!" << endl;
            cout << "\t-----------------------" << endl;
        }
        cout << endl;
        cout << "\tRematch? (Y)es or (N)o: ";
        cin >> rematch;
        if ((rematch == 'Y') || (rematch == 'y'))
        {
            init();
            play(p1, p2);
        }
    }

    void displayScore(Player& p1, Player& p2)
    {
        cout << endl;
        cout << "\t      SCORE";
        cout << endl;
        if (computerPlayer)
        {
            cout << "\t Player 1: " << p1.getScore() << " \t Computer: " << p2.getScore() << endl;
        }
        else
        {
            cout << "\t Player 1: " << p1.getScore() << " \t Player 2: " << p2.getScore() << endl;
        }
    }

    public:
        Game() : emptyCount{ 0 }, gameOn{ 1 }, computerPlayer{ 0 }
        {
            init();
            winList[0].row = new int[3]{ 0,1,2 };
            winList[1].row = new int[3]{ 3,4,5 };
            winList[2].row = new int[3]{ 6,7,8 };
            winList[3].row = new int[3]{ 0,3,6 };
            winList[4].row = new int[3]{ 1,4,7 };
            winList[5].row = new int[3]{ 2,5,8 };
            winList[6].row = new int[3]{ 0,4,8 };
            winList[7].row = new int[3]{ 2,4,6 };
        }

        void init() 
        {
            gameOn = 1;

            emptyCount = 0;
            srand(time(0));
            for (size_t i = 0; i < 10; i++) {
                emptyIndex[i] = 0;
                board[i] = (i + 1) + '0';
                emptyCount++;
            }
            emptyCount--;
        }

        void onePlayerGame()
        {
            Player p("Player 1");
            Player c("Computer");
            cout << endl;
            cout << "      ---------------------------------" << endl;
            cout << "\t Player 1: X \t Computer: O" << endl;
            cout << "      ---------------------------------" << endl;
            cout << endl;
            cout << "      ---------- GAME START! ----------";
            computerPlayer = 1;
            play(c, p);
        }

        void twoPlayerGame()
        {
            Player p("Player 1");
            Player c("Player 2");
            cout << endl;
            cout << "      ---------------------------------" << endl;
            cout << "\t Player 1: X \t Player 2: O" << endl;
            cout << "      ---------------------------------" << endl;
            cout << endl;
            cout << "      ---------- GAME START! ----------";
            computerPlayer = 0;
            play(c, p);
        }
};

