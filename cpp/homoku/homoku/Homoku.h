#pragma once
#include "Sequence.h"
#include "PriorityQueue.h"
#include <utility>
#include <omp.h>


/**
 * Const values for Gomoku.
 */
static const int MAX_DEPTH = 5;
static const int MAX_DEPTH_MCTS = 9;

/**
 * A gameBoard storing a Gomoku Board.
 */
using MatrixInt = ArraySequence<ArraySequence<int>>;
using GameBoard = MatrixInt;
using Move = Item<std::pair<int, int>>;

/**
 * A class storing a Gomoku position.
 * Function are relative to the current player to play.
 * Position containing aligment are not supported by this class.
 */
class Position {
public:
    
    static const int WIDTH = 19;  // Width of the board
    static const int HEIGHT = 19; // Height of the board
    int centerX = ((int)floor(Position::WIDTH / 2.0));
    int centerY = ((int)floor(Position::HEIGHT / 2.0));
    int highX = centerX;
    int lowX = centerX;
    int highY = centerY;
    int lowY = centerY;
    //int radius = 0;

    int currentPlayer = 1;
    int nMoves = 0;
    GameBoard gameBoard = GameBoard(Position::HEIGHT, ArraySequence<int>(Position::WIDTH, 0));

    /**
     * Indicates whether a cell is empty.
     * @return true if the cell is empty, false if not.
     */
    bool canMove(int x, int y) const {
        try
        {
            return gameBoard[x][y] == 0;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    /**
     * Makes a move.
     * This function should be used only when player can move.
     */
    void move(int x, int y) {
        //std::cout << x << " " << y << std::endl;
        this->gameBoard[x][y] = currentPlayer;
        //int rDistance = std::max(std::abs(x - centerX), std::abs(y - centerY));
        //if (rDistance > this->radius) this->radius = rDistance;
        if (x > this->highX) this->highX = x;
        else if (x < this->lowX) this->lowX = x;
        if (y > this->highY) this->highY = y;
        else if (y < this->lowY) this->lowY = y;
        currentPlayer = -currentPlayer;
        nMoves++;
    }

    /**
     * Evals a move
     * @return eval of the move
     */
    int evalMove(int x, int y) const {

        // check 5 in a row in every direction
        
        /*
        //horizontal
        //right
        int horizontal = 0;
        int i1 = 0;
        while (gameBoard[x][y + i1] == currentPlayer or i1 == 0) {
            i1++;
            horizontal++;
            if (i1 <= 5 and y + i1 < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i1 == 5) return 10000;
        //left
        int i2 = 0;
        while (gameBoard[x][y - i2] == currentPlayer or i2 == 0) {
            i2++;
            horizontal++;
            if (i2 <= 5 and y - i2 >= 0) {
                continue;
            }
            else break;
        }
        if (i2 == 5) return 10000;
        if (horizontal == 6) return 10000;

        //vertical
        //down
        int vertical = 0;
        int i3 = 0;
        while (gameBoard[x + i3][y] == currentPlayer or i3 == 0) {
            i3++;
            vertical++;
            if (i3 <= 5 and x + i3 < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i3 == 5) return 10000;
        //up
        int i4 = 0;
        while (gameBoard[x - i4][y] == currentPlayer or i4 == 0) {
            i4++;
            vertical++;
            if (i4 <= 5 and x - i4 >= 0) {
                continue;
            }
            else break;
        }
        if (i4 == 5) return 10000;
        if (vertical == 6) return 10000;

        //diagonal1 NE-SW
        int diagonal1 = 0;
        int i5 = 0;
        while (gameBoard[x + i5][y + i5] == currentPlayer or i5 == 0) {
            i5++;
            diagonal1++;
            if (i5 <= 5 and x + i5 < HEIGHT and y + i5 < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i5 == 5) return 10000;
        int i6 = 0;
        while (gameBoard[x - i6][y - i6] == currentPlayer or i6 == 0) {
            i6++;
            diagonal1++;
            if (i6 <= 5 and x - i6 >= 0 and y - i6 >= 0) {
                continue;
            }
            else break;
        }
        if (i6 == 5) return 10000;
        if (diagonal1 == 6) return 10000;

        //diagonal2 NW-SE
        int diagonal2 = 0;
        int i7 = 0;
        while (gameBoard[x - i7][y + i7] == currentPlayer or i7 == 0) {
            i7++;
            diagonal2++;
            if (i7 <= 5 and x - i7 >= 0 and y + i7 < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i7 == 5) return 10000;
        int i8 = 0;
        while (gameBoard[x + i8][y - i8] == currentPlayer or i8 == 0) {
            i8++;
            diagonal2++;
            if (i8 <= 5 and x + i8 < HEIGHT and y - i8 >= 0) {
                continue;
            }
            else break;
        }
        if (i8 == 5) return 10000;
        if (diagonal2 == 6) return 10000;
        

        //return std::max({ horizontal, vertical, diagonal1, diagonal2 });
        return std::pow(3, horizontal - 2) + std::pow(3, vertical - 2) + std::pow(3, diagonal1 - 2) + std::pow(3, diagonal2 - 2);
        */
        

        ///*
        int open = 0;
        ArraySequence<int> is = ArraySequence<int>(8, 0);
        ArraySequence<int> js = ArraySequence<int>(8, 0);
        //horizontal
        //right
        //count same symbol
        //int horizontal = 0;
        while (gameBoard[x][y + is[0]] == currentPlayer or is[0] == 0) {
            is[0]++;
            //horizontal++;
            if (is[0] <= 5 and y + is[0] < HEIGHT) {
                continue;
            }
            else break;
        }
        int horizontal = is[0] - 1;
        //count zeros
        js[0] = 0;
        if (is[0] <= 5 and y + is[0] < HEIGHT) {
            while (gameBoard[x][y + is[0]] == 0) {
                is[0]++;
                js[0]++;
                if (is[0] <= 5 and y + is[0] < HEIGHT) {
                    continue;
                }
                else break;
            }
        }
        //left
        while (gameBoard[x][y - is[1]] == currentPlayer or is[1] == 0) {
            is[1]++;
            //horizontal++;
            if (is[1] <= 5 and y - is[1] >= 0) {
                continue;
            }
            else break;
        }
        horizontal += is[1] - 1;
        //count zeros
        js[1] = 0;
        if (is[1] <= 5 and y - is[1] >= 0) {
            while (gameBoard[x][y - is[1]] == 0) {
                is[1]++;
                js[1]++;
                if (is[1] <= 5 and y - is[1] >= 0) {
                    continue;
                }
                else break;
            }
        }
        if (horizontal == 4) return 10000;
        else if (horizontal + js[0] + js[1] < 4) {
            // means can't get 5 from it
            horizontal = 0;
        }
        else if (horizontal + js[0] + js[1] == 4) {
            // means closed
        }
        else {
            if (horizontal >= 3) open++;
            //horizontal++;
        }

        //vertical
        //down
        //int vertical = 0;
        while (gameBoard[x + is[2]][y] == currentPlayer or is[2] == 0) {
            is[2]++;
            //vertical++;
            if (is[2] <= 5 and x + is[2] < HEIGHT) {
                continue;
            }
            else break;
        }
        int vertical = is[2] - 1;
        js[2] = 0;
        if (is[2] <= 5 and x + is[2] < HEIGHT) {
            while (gameBoard[x + is[2]][y] == 0) {
                is[2]++;
                js[2]++;
                if (is[2] <= 5 and x + is[2] < HEIGHT) {
                    continue;
                }
                else break;
            }
        }
        //up
        while (gameBoard[x - is[3]][y] == currentPlayer or is[3] == 0) {
            is[3]++;
            //vertical++;
            if (is[3] <= 5 and x - is[3] >= 0) {
                continue;
            }
            else break;
        }
        vertical += is[3] - 1;
        js[3] = 0;
        if (is[3] <= 5 and x - is[3] >= 0) {
            while (gameBoard[x - is[3]][y] == 0) {
                is[3]++;
                js[3]++;
                if (is[3] <= 5 and x - is[3] >= 0) {
                    continue;
                }
                else break;
            }
        }
        if (vertical == 4) return 10000;
        else if (vertical + js[2] + js[3] < 4) {
            // means can't get 5 from it
            vertical = 0;
        }
        else if (vertical + js[2] + js[3] == 4) {
            // means closed
        }
        else {
            if (vertical >= 3) open++;
            //vertical++;
        }

        //diagonal1 NE-SW
        //int diagonal1 = 0;
        while (gameBoard[x + is[4]][y + is[4]] == currentPlayer or is[4] == 0) {
            is[4]++;
            //diagonal1++;
            if (is[4] <= 5 and x + is[4] < HEIGHT and y + is[4] < HEIGHT) {
                continue;
            }
            else break;
        }
        int diagonal1 = is[4] - 1;
        js[4] = 0;
        if (is[4] <= 5 and x + is[4] < HEIGHT and y + is[4] < HEIGHT) {
            while (gameBoard[x + is[4]][y + is[4]] == 0) {
                is[4]++;
                js[4]++;
                if (is[4] <= 5 and x + is[4] < HEIGHT and y + is[4] < HEIGHT) {
                    continue;
                }
                else break;
            }
        }
        while (gameBoard[x - is[5]][y - is[5]] == currentPlayer or is[5] == 0) {
            is[5]++;
            //diagonal1++;
            if (is[5] <= 5 and x - is[5] >= 0 and y - is[5] >= 0) {
                continue;
            }
            else break;
        }
        diagonal1 += is[5] - 1;
        js[5] = 0;
        if (is[5] <= 5 and x - is[5] >= 0 and y - is[5] >= 0) {
            while (gameBoard[x - is[5]][y - is[5]] == 0) {
                is[5]++;
                js[5]++;
                if (is[5] <= 5 and x - is[5] >= 0 and y - is[5] >= 0) {
                    continue;
                }
                else break;
            }
        }
        if (diagonal1 == 4) return 10000;
        else if (diagonal1 + js[4] + js[5] < 4) {
            // means can't get 5 from it
            diagonal1 = 0;
        }
        else if (diagonal1 + js[4] + js[5] == 4) {
            // means closed
        }
        else {
            if (diagonal1 >= 3) open++;
            //diagonal1++;
        }

        //diagonal2 NW-SE
        //int diagonal2 = 0;
        while (gameBoard[x - is[6]][y + is[6]] == currentPlayer or is[6] == 0) {
            is[6]++;
            //diagonal2++;
            if (is[6] <= 5 and x - is[6] >= 0 and y + is[6] < HEIGHT) {
                continue;
            }
            else break;
        }
        int diagonal2 = is[6] - 1;
        js[6] = 0;
        if (is[6] <= 5 and x - is[6] >= 0 and y + is[6] < HEIGHT) {
            while (gameBoard[x - is[6]][y + is[6]] == 0) {
                is[6]++;
                js[6]++;
                if (is[6] <= 5 and x - is[6] >= 0 and y + is[6] < HEIGHT) {
                    continue;
                }
                else break;
            }
        }
        while (gameBoard[x + is[7]][y - is[7]] == currentPlayer or is[7] == 0) {
            is[7]++;
            //diagonal2++;
            if (is[7] <= 5 and x + is[7] < HEIGHT and y - is[7] >= 0) {
                continue;
            }
            else break;
        }
        diagonal2 += is[7] - 1;
        js[7] = 0;
        if (is[7] <= 5 and x + is[7] < HEIGHT and y - is[7] >= 0) {
            while (gameBoard[x + is[7]][y - is[7]] == 0) {
                is[7]++;
                js[7]++;
                if (is[7] <= 5 and x + is[7] < HEIGHT and y - is[7] >= 0) {
                    continue;
                }
                else break;
            }
        }
        if (diagonal2 == 4) return 10000;
        else if (diagonal2 + js[6] + js[7] < 4) {
            // means can't get 5 from it
            diagonal2 = 0;
        }
        else if (diagonal2 + js[6] + js[7] == 4) {
            // means closed
        }
        else {
            if (diagonal2 >= 3) open++;
            //diagonal2++;
        }
        //*/
        /*
        ArraySequence<int> is = ArraySequence<int>(8, 0);
        ArraySequence<int> js = ArraySequence<int>(8, 0);
        
        //horizontal
        //right
        //count same symbol
        //int horizontal = 0;
        while (gameBoard[x][y + is[0]] == currentPlayer or is[0] == 0) {
            is[0]++;
            //horizontal++;
            if (is[0] <= 5 and y + is[0] < HEIGHT) {
                continue;
            }
            else break;
        }
        //if (is[0] == 5) return 10000;
        //count zeros
        js[0] = is[0];
        while (gameBoard[x][y + js[0]] == 0) {
            js[0]++;
            if (js[0] <= 5 and y + js[0] < HEIGHT) {
                continue;
            }
            else break;
        }
        //left
        while (gameBoard[x][y - is[1]] == currentPlayer or is[1] == 0) {
            is[1]++;
            //horizontal++;
            if (is[1] <= 5 and y - is[1] >= 0) {
                continue;
            }
            else break;
        }
        //count zeros
        js[1] = is[1];
        while (gameBoard[x][y - js[1]] == 0) {
            js[1]++;
            if (js[1] <= 5 and y - js[1] >= 0) {
                continue;
            }
            else break;
        }
        //if (is[1] == 5) return 10000;
        int horizontal = is[0] + is[1] - 2;
        if (horizontal == 4) return 10000;
        else if (horizontal + js[0] + js[1] < 4) {
            // means can't get 5 from it
            horizontal = 0;
        }
        else if (horizontal + js[0] + js[1] == 4) {
            // means closed
        }
        else {
            // means open
        }

        //vertical
        //down
        //int vertical = 0;
        while (gameBoard[x + is[2]][y] == currentPlayer or is[2] == 0) {
            is[2]++;
            //vertical++;
            if (is[2] <= 5 and x + is[2] < HEIGHT) {
                continue;
            }
            else break;
        }
        js[2] = is[2];
        while (gameBoard[x + js[2]][y] == 0) {
            js[2]++;
            if (js[2] <= 5 and x + js[2] < HEIGHT) {
                continue;
            }
            else break;
        }
        //if (is[2] == 5) return 10000;
        //up
        while (gameBoard[x - is[3]][y] == currentPlayer or is[3] == 0) {
            is[3]++;
            //vertical++;
            if (is[3] <= 5 and x - is[3] >= 0) {
                continue;
            }
            else break;
        }
        js[3] = is[3];
        while (gameBoard[x - js[3]][y] == 0) {
            js[3]++;
            if (js[3] <= 5 and x - js[3] >= 0) {
                continue;
            }
            else break;
        }
        //if (is[3] == 5) return 10000;
        int vertical = is[2] + is[3] - 2;
        if (vertical == 4) return 10000;
        else if (vertical + js[2] + js[3] < 4) {
            // means can't get 5 from it
            vertical = 0;
        }
        else if (vertical + js[2] + js[3] == 4) {
            // means closed
        }
        else {
            // means open
        }

        //diagonal1 NE-SW
        //int diagonal1 = 0;
        while (gameBoard[x + is[4]][y + is[4]] == currentPlayer or is[4] == 0) {
            is[4]++;
            //diagonal1++;
            if (is[4] <= 5 and x + is[4] < HEIGHT and y + is[4] < HEIGHT) {
                continue;
            }
            else break;
        }
        js[4] = is[4];
        while (gameBoard[x + js[4]][y + js[4]] == 0) {
            js[4]++;
            if (js[4] <= 5 and x + js[4] < HEIGHT and y + js[4] < HEIGHT) {
                continue;
            }
            else break;
        }
        //if (is[4] == 5) return 10000;
        while (gameBoard[x - is[5]][y - is[5]] == currentPlayer or is[5] == 0) {
            is[5]++;
            //diagonal1++;
            if (is[5] <= 5 and x - is[5] >= 0 and y - is[5] >= 0) {
                continue;
            }
            else break;
        }
        js[5] = is[5];
        while (gameBoard[x - js[5]][y - js[5]] == 0) {
            js[5]++;
            if (js[5] <= 5 and x - js[5] >= 0 and y - js[5] >= 0) {
                continue;
            }
            else break;
        }
        //if (is[5] == 5) return 10000;
        int diagonal1 = is[4] + is[5] - 2;
        if (diagonal1 == 4) return 10000;
        else if (diagonal1 + js[4] + js[5] < 4) {
            // means can't get 5 from it
            diagonal1 = 0;
        }
        else if (diagonal1 + js[4] + js[5] == 4) {
            // means closed
        }
        else {
            // means open
        }

        //diagonal2 NW-SE
        //int diagonal2 = 0;
        while (gameBoard[x - is[6]][y + is[6]] == currentPlayer or is[6] == 0) {
            is[6]++;
            //diagonal2++;
            if (is[6] <= 5 and x - is[6] >= 0 and y + is[6] < HEIGHT) {
                continue;
            }
            else break;
        }
        js[6] = is[6];
        while (gameBoard[x - js[6]][y + js[6]] == 0) {
            js[6]++;
            if (js[6] <= 5 and x - js[6] >= 0 and y + js[6] < HEIGHT) {
                continue;
            }
            else break;
        }
        //if (is[6] == 5) return 10000;
        while (gameBoard[x + is[7]][y - is[7]] == currentPlayer or is[7] == 0) {
            is[7]++;
            //diagonal2++;
            if (is[7] <= 5 and x + is[7] < HEIGHT and y - is[7] >= 0) {
                continue;
            }
            else break;
        }
        js[7] = is[7];
        while (gameBoard[x + js[7]][y - js[7]] == 0) {
            js[7]++;
            if (js[7] <= 5 and x + js[7] < HEIGHT and y - js[7] >= 0) {
                continue;
            }
            else break;
        }
        //if (is[7] == 5) return 10000;
        int diagonal2 = is[6] + is[7] - 2;
        if (diagonal2 == 4) return 10000;
        else if (diagonal2 + js[6] + js[7] < 4) {
            // means can't get 5 from it
            diagonal2 = 0;
        }
        else if (diagonal2 + js[6] + js[7] == 4) {
            // means closed
        }
        else {
            // means open
        }
        */
        if (open >= 2) open = 100;
        return std::pow(3, horizontal) + std::pow(3, vertical) + std::pow(3, diagonal1) + std::pow(3, diagonal2) + open;
    }

    /**
     * Indicates whether the current player wins by playing this move.
     * This function should never be called if player can't move there.
     * @return true if current player makes an alignment by playing this move.
     */
    bool isWinningMove(int x, int y) const {

        //horizontal
        //right
        int horizontal = 0;
        int i1 = 0;
        while (gameBoard[x][y + i1] == currentPlayer or i1 == 0) {
            i1++;
            horizontal++;
            if (i1 <= 5 and y + i1 < HEIGHT) {
                continue;
            }
            else break;
        }
        //left
        int i2 = 0;
        while (gameBoard[x][y - i2] == currentPlayer or i2 == 0) {
            i2++;
            horizontal++;
            if (i2 <= 5 and y - i2 >= 0) {
                continue;
            }
            else break;
        }
        if (horizontal == 6) return true;
        //vertical
        //down
        int vertical = 0;
        int i3 = 0;
        while (gameBoard[x + i3][y] == currentPlayer or i3 == 0) {
            i3++;
            vertical++;
            if (i3 <= 5 and x + i3 < HEIGHT) {
                continue;
            }
            else break;
        }
        //up
        int i4 = 0;
        while (gameBoard[x - i4][y] == currentPlayer or i4 == 0) {
            i4++;
            vertical++;
            if (i4 <= 5 and x - i4 >= 0) {
                continue;
            }
            else break;
        }
        if (vertical == 6) return true;
        //diagonal1 NE-SW
        int diagonal1 = 0;
        int i5 = 0;
        while (gameBoard[x + i5][y + i5] == currentPlayer or i5 == 0) {
            i5++;
            diagonal1++;
            if (i5 <= 5 and x + i5 < HEIGHT and y + i5 < HEIGHT) {
                continue;
            }
            else break;
        }
        int i6 = 0;
        while (gameBoard[x - i6][y - i6] == currentPlayer or i6 == 0) {
            i6++;
            diagonal1++;
            if (i6 <= 5 and x - i6 >= 0 and y - i6 >= 0) {
                continue;
            }
            else break;
        }
        if (diagonal1 == 6) return true;
        //diagonal2 NW-SE
        int diagonal2 = 0;
        int i7 = 0;
        while (gameBoard[x - i7][y + i7] == currentPlayer or i7 == 0) {
            i7++;
            diagonal2++;
            if (i7 <= 5 and x - i7 >= 0 and y + i7 < HEIGHT) {
                continue;
            }
            else break;
        }
        int i8 = 0;
        while (gameBoard[x + i8][y - i8] == currentPlayer or i8 == 0) {
            i8++;
            diagonal2++;
            if (i8 <= 5 and x + i8 < HEIGHT and y - i8 >= 0) {
                continue;
            }
            else break;
        }
        if (diagonal2 == 6) return true;

        return false;

        /*
        // check 5 in a row in every direction
        ArraySequence<int> is = ArraySequence<int>(8, 0);
        //horizontal
        //right
        int horizontal = 0;
        //count same symbol
        while (gameBoard[x][y + is[0]] == currentPlayer or is[0] == 0) {
            is[0]++;
            horizontal++;
            if (is[0] <= 5 and y + is[0] < HEIGHT) {
                continue;
            }
            else break;
        }
        //int horizontal = is[0] - 1;
        //left
        while (gameBoard[x][y - is[1]] == currentPlayer or is[1] == 0) {
            is[1]++;
            horizontal++;
            if (is[1] <= 5 and y - is[1] >= 0) {
                continue;
            }
            else break;
        }
        horizontal -= 2;
        if (horizontal == 4) return true;

        //vertical
        //down
        int vertical = 0;
        while (gameBoard[x + is[2]][y] == currentPlayer or is[2] == 0) {
            is[2]++;
            vertical++;
            if (is[2] <= 5 and x + is[2] < HEIGHT) {
                continue;
            }
            else break;
        }
        //int vertical = is[2] - 1;
        //up
        while (gameBoard[x - is[3]][y] == currentPlayer or is[3] == 0) {
            is[3]++;
            vertical++;
            if (is[3] <= 5 and x - is[3] >= 0) {
                continue;
            }
            else break;
        }
        vertical -= 2;
        if (vertical == 4) return true;

        //diagonal1 NE-SW
        int diagonal1 = 0;
        while (gameBoard[x - is[4]][y + is[4]] == currentPlayer or is[4] == 0) {
            is[4]++;
            diagonal1++;
            if (is[4] <= 5 and x + is[4] < HEIGHT and y + is[4] < HEIGHT) {
                continue;
            }
            else break;
        }
        //int diagonal1 = is[4] - 1;
        while (gameBoard[x - is[5]][y + is[5]] == currentPlayer or is[5] == 0) {
            is[5]++;
            diagonal1++;
            if (is[5] <= 5 and x - is[5] >= 0 and y - is[5] >= 0) {
                continue;
            }
            else break;
        }
        diagonal1 -= 2;
        if (diagonal1 == 4) return true;

        //diagonal2 NW-SE
        int diagonal2 = 0;
        while (gameBoard[x - is[6]][y + is[6]] == currentPlayer or is[6] == 0) {
            is[6]++;
            diagonal2++;
            if (is[6] <= 5 and x - is[6] >= 0 and y + is[6] < HEIGHT) {
                continue;
            }
            else break;
        }
        //int diagonal2 = is[6] - 1;
        while (gameBoard[x + is[7]][y - is[7]] == currentPlayer or is[7] == 0) {
            is[7]++;
            diagonal2++;
            if (is[7] <= 5 and x + is[7] < HEIGHT and y - is[7] >= 0) {
                continue;
            }
            else break;
        }
        diagonal2 -= 2;
        if (diagonal2 == 4) return true;
        
        return false;
        */
    }
};

/*
 * Recursively solve a Gomoku position using Negamax (opt Minimax) algorithm.
 */
Move negamax(const Position position, int depth = 0, int alpha = 0, int beta = 100) {

    if (position.nMoves == Position::WIDTH * Position::HEIGHT) // check for draw game
    {
        Move move;
        move.item = std::pair<int, int>(-1, -1);
        move.priority = 0;
    }

    int max = 81 - depth;	// upper bound of our score as we cannot win immediately
    if (beta > max) {
        beta = max;                     // there is no need to keep beta above our max possible score.
    }
    if (alpha >= beta) {
        Move move;
        move.item = std::pair<int, int>(-1, -1);
        move.priority = -100000;
        return move;
    }  // prune the exploration if the [alpha;beta] window is empty.

    PriorityQueue<std::pair<int, int>> heuristicScoreQueue = PriorityQueue<std::pair<int, int>>();
    #pragma omp parallel for shared(position, heuristicScoreQueue)
    for (int x = position.lowX - 1; x <= position.highX + 1; x++) {
        for (int y = position.lowY - 1; y <= position.highY + 1; y++) {
            if (position.canMove(x, y)) {
                std::pair<int, int> move = std::pair<int, int>(x, y);
                int eval = position.evalMove(x, y);
                #pragma omp critical
                {
                    heuristicScoreQueue.Insert(move, eval);
                }
            }
        }
    }
    // check win
    Move firstMove = heuristicScoreQueue.GetHighestPriorityItem();
    if (depth == MAX_DEPTH or position.nMoves < 5 or firstMove.priority > 1000) {
        firstMove.priority = firstMove.priority - depth;
        return firstMove;
    }
    else {
        /*
        if (depth == 0) {
            std::cout << "--------------------------------------------------" << std::endl;
        }
        */

        PriorityQueue<std::pair<int, int>> scoreQueue = PriorityQueue<std::pair<int, int>>();

        // optimization on depth of view
        // check future of the best move
        int start = 1;
        Position newPosition = position;
        newPosition.move(firstMove.item.first, firstMove.item.second);
        int opEval = negamax(newPosition, depth + 1).priority;
        int Eval = firstMove.priority - opEval;
        if (Eval > -1000) {
            //if (depth == 0) depth = MAX_DEPTH - 3;
            //start = 0;
            if (depth == 0) return firstMove;
            else { scoreQueue.Insert(firstMove.item, Eval); }
        }

        //#pragma omp parallel for shared(position, heuristicScoreQueue, scoreQueue, bestMove)
        for (int i = start; i < heuristicScoreQueue.GetLength(); i++) {
            Item<std::pair<int, int>> item = heuristicScoreQueue.GetItem(i);
            //check win
            /*
            if (item.priority > 1000) {
                item.priority = item.priority - depth;
                return item;
            }
            */
            // check future
            Position newPosition = position;
            newPosition.move(item.item.first, item.item.second);
            int opEval = negamax(newPosition, depth + 1).priority;
            if (opEval > 1000) {
                //scoreQueue.Insert(item.item, -1000000);
                continue;
            } else {
                int Eval = item.priority - opEval;
                if (Eval > alpha) {
                    alpha = Eval;
                }
                if (Eval >= beta) {
                    item.priority = Eval;
                    return item;
                }
                scoreQueue.Insert(item.item, Eval);
                break;
            }
        }
        if (scoreQueue.GetLength() == 0) {
            // make lose sign
            Move move;
            move.item = std::pair<int, int>(-2, -2);
            move.priority = -1000000;
            return move;
        }
        else
        {
            // get best move
            Item<std::pair<int, int>> bestitem = scoreQueue.GetHighestPriorityItem();
            return bestitem;
        }
    }

    /*
    ArraySequence<int> bestMove;
    if (scoreArray.GetLength() == 0) {
        bestMove = ArraySequence<int>(3, -10000);
    }
    else { bestMove = findMaxScore(scoreArray); }

    if (depth == 0) {
        for (int i = 0; i < scoreArray.GetLength(); i++)
                std::cout << &scoreArray[i] << std::endl;
        std::cout << "best: " << &bestMove << '\t' << position.radius << std::endl;
    }
    return bestMove;
    */
    
}

Move MCTS(const Position position, int depth) {

    if (position.nMoves == Position::WIDTH * Position::HEIGHT) // check for draw game
    {
        Move move;
        move.item = std::pair<int, int>(-1, -1);
        move.priority = 0;
    }

    if (depth == 0) {
        PriorityQueue<std::pair<int, int>> scoreQueue = PriorityQueue<std::pair<int, int>>();
        #pragma omp parallel for shared(position, scoreQueue)
        for (int x = position.lowX - 1; x <= position.highX + 1; x++) {
            for (int y = position.lowY - 1; y <= position.highY + 1; y++) {
                if (position.canMove(x, y)) {
                    std::pair<int, int> move = std::pair<int, int>(x, y);
                    Position newPosition = position;
                    newPosition.move(x, y);
                    int eval = position.evalMove(x, y) - MCTS(newPosition, depth + 1).priority;
                    #pragma omp critical
                    {
                        scoreQueue.Insert(move, eval);
                    }
                }
            }
        }
        ///*
        for (int i = 0; i < scoreQueue.GetLength(); i++)
            std::cout << scoreQueue[i].item.first << " " << scoreQueue[i].item.second << " " << scoreQueue[i].priority << std::endl;
        //*/
        Item<std::pair<int, int>> item = scoreQueue.GetHighestPriorityItem();
        return item;
    }
    else {
        PriorityQueue<std::pair<int, int>> heuristicScoreQueue = PriorityQueue<std::pair<int, int>>();
        #pragma omp parallel for shared(position, heuristicScoreQueue)
        for (int x = position.lowX - 1; x <= position.highX + 1; x++) {
            for (int y = position.lowY - 1; y <= position.highY + 1; y++) {
                if (position.canMove(x, y)) {
                    std::pair<int, int> move = std::pair<int, int>(x, y);
                    int eval = position.evalMove(x, y);
                    #pragma omp critical
                    {
                        heuristicScoreQueue.Insert(move, eval);
                    }
                }
            }
        }
        ///*
        for (int i = 0; i < heuristicScoreQueue.GetLength(); i++)
            std::cout << position.currentPlayer << " d" << depth << " " << heuristicScoreQueue[i].item.first << " " << heuristicScoreQueue[i].item.second << " " << heuristicScoreQueue[i].priority << std::endl;
        //*/
        Item<std::pair<int, int>> item = heuristicScoreQueue.GetHighestPriorityItem();
        //check win
        if (item.priority > 1000 or depth == MAX_DEPTH_MCTS or position.nMoves < 5) {
            item.priority = item.priority - depth;
            return item;
        }
        // check future
        Position newPosition = position;
        newPosition.move(item.item.first, item.item.second);
        int opEval = MCTS(newPosition, depth + 1).priority;
        item.priority = item.priority - opEval;
        return item;
    }
}