#include <iostream>
#include <chrono>
#include <random>
#include <math.h>
#include "Homoku.h"
#include <omp.h>
#include <cstdlib>

// for data sampling
#include <fstream>

int main()
{
    //make Position
    Position position = Position();
    int x, y;

    // get config
    int player; // human's player
    std::cin >> player;

    bool win = false;
    int winner = 0;

    int movesCounter = 0;
    if (player == -1) {
        x = position.centerX;
        y = position.centerY;
        position.move(x, y);
        std::cout << x << ' ' << y << std::endl;
        movesCounter++;
    }

    Move AImove;
    while (true)
    {
        std::cin >> x >> y;
        //AImove = negamax(position, 0, 0, 100);
        //AImove = MCTS(position, 0);
        //x = AImove.item.first;
        //y = AImove.item.second;

        if (position.canMove(x, y)) {
            if (position.isWinningMove(x, y)) {
                win = true;
                winner = player;
                std::cout << -1 << ' ' << -1 << " " << winner << std::endl;
                break;
            }
            else {
                //for (int i = 0; i < position.gameBoard.GetLength(); i++)
                //    MatrixsFile << &position.gameBoard[i];
                //MatrixsFile << std::endl;
                //MovesFile << x << ' ' << y << std::endl;
                position.move(x, y);
            }
        }
        if (movesCounter == 0) {
            x = position.centerX;
            y = position.centerY;
            if (position.canMove(x, y)) {
                position.move(x, y);
                std::cout << x << ' ' << y << std::endl;
            }
            else {
                x--;
                y++;
                position.move(x, y);
                std::cout << x << ' ' << y << std::endl;
            }
        }
        else {
            AImove = negamax(position);
            //AImove = MCTS(position, 0);
            x = AImove.item.first;
            y = AImove.item.second;
            if (x < 0) {
                win = true;
                winner = player;
                std::cout << x << ' ' << y << " " << winner << std::endl;
                break;
            } else if (position.isWinningMove(x, y)) {
                win = true;
                winner = -player;
                std::cout << x << ' ' << y << " " << winner << std::endl;
                break;
            }
            position.move(x, y);
            std::cout << x << ' ' << y << std::endl;
        }
        movesCounter++;
    }
}