#include <iostream>
#include <chrono>
#include <random>
#include <math.h>
#include "Homoku.h"
#include <omp.h>

int main()
{
    ///*
    // make Game Map
    //GameBoard gameMatrix = GameBoard(Position::HEIGHT, ArraySequence<int>(Position::WIDTH, 0));

    //make Position
    Position position = Position();
    /*
    //make Search Pattern
    MatrixInt searchPattern = MatrixInt(Position::HEIGHT * Position::HEIGHT, ArraySequence<int>(3, -100000));
    int x = 0; // current position; x
    int y = 0; // current position; y
    int d = 0; // current direction; 0=RIGHT, 1=DOWN, 2=LEFT, 3=UP
    int s = 1; // chain size
    int c = 0;
    // starting point
    x = ((int)floor(Position::WIDTH / 2.0));
    y = ((int)floor(Position::HEIGHT / 2.0));
    for (int k = 1; k <= (Position::HEIGHT - 1); k++)
    {
        for (int j = 0; j < (k < (Position::HEIGHT - 1) ? 2 : 3); j++)
        {
            for (int i = 0; i < s; i++)
            {
                //std::cout << "{" << x << ", " << y << "}" << ", ";
                searchPattern[c][0] = x;
                searchPattern[c][1] = y;
                c++;
                switch (d)
                {
                case 0: y = y + 1; break;
                case 1: x = x + 1; break;
                case 2: y = y - 1; break;
                case 3: x = x - 1; break;
                }
            }
            d = (d + 1) % 4;
        }
        s++;
    }
    //std::cout << gameMatrix[0][Position::HEIGHT - 1] << " ";
    searchPattern[searchPattern.GetLength() - 1][0] = 0;
    searchPattern[searchPattern.GetLength() - 1][1] = Position::HEIGHT - 1;
    searchPattern[searchPattern.GetLength() - 1][2] = -100000;
    */
    int x, y;

    ///*
    
    int movesCounter = 0;
    while (true) {
        for (int i = 0; i < Position::HEIGHT; i++) {
            std::cout << &position.gameBoard[i] << std::endl;
        }
        std::cin >> x >> y;
        if (position.canMove(x, y)) {
            position.move(x, y);
        }
        else continue;
        if (movesCounter == 0) {
            x = ((int)floor(Position::HEIGHT / 2.0));
            y = ((int)floor(Position::HEIGHT / 2.0));
            if (position.canMove(x, y)) {
                position.move(x, y);
            }
            else {
                x--;
                position.move(x, y);
            }
        }
        else {
            ArraySequence<int> AImove = negamax(position, /*searchPattern,*/ 0, 0, 100);
            x = AImove[0];
            y = AImove[1];
            position.move(x, y);
        }
        movesCounter++;
    }
    //*/

    /*
    
    int movesCounter = 0;
    while (true)
    {
        std::cin >> x >> y;
        
        if (position.canMove(x, y)) {
            position.move(x, y);
        }
        else continue;
        if (movesCounter == 0) {
            x = ((int)floor(Position::HEIGHT / 2.0));
            y = ((int)floor(Position::HEIGHT / 2.0));
            if (position.canMove(x, y)) {
                position.move(x, y);
            }
            else {
                x--;
                position.move(x, y);
            }
        }
        else {
            ArraySequence<int> AImove = negamax(position, searchPattern, 0, 0, 100);
            x = AImove[0];
            y = AImove[1];
            position.move(AImove[0], AImove[1]);
        }
        movesCounter++;

        std::cout << x << ' ' << y << std::endl;
    }
    */
}