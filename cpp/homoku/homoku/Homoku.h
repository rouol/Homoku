#pragma once
#include "Sequence.h"
#include "PriorityQueue.h"
#include <utility>
#include <omp.h>

/**
 * Const values for Gomoku.
 */
static const int MAX_DEPTH = 4;

/**
 * A gameBoard storing a Gomoku Board.
 */
using MatrixInt = ArraySequence<ArraySequence<int>>;
using GameBoard = MatrixInt;

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
    int radius = 0;

    int currentPlayer = 1;
    int nMoves = 0;
    GameBoard gameBoard = GameBoard(Position::HEIGHT, ArraySequence<int>(Position::WIDTH, 0));

    /**
     * Indicates whether a cell is empty.
     * @return true if the cell is empty, false if not.
     */
    bool canMove(int x, int y) const {
        return gameBoard[x][y] == 0;
    }

    /**
     * Makes a move.
     * This function should be used only when player can move.
     */
    void move(int x, int y) {
        //std::cout << x << " " << y << std::endl;
        this->gameBoard[x][y] = currentPlayer;
        int rDistance = std::max(std::abs(x - centerX), std::abs(y - centerY));
        if (rDistance > this->radius) this->radius = rDistance;
        currentPlayer = -currentPlayer;
        nMoves++;
    }

    /**
     * Evals a this Position
     * @return eval of the Position
     */
    int evalPosition() const {

        // array with 2, 3, 4 combos
        ArraySequence<int> combos = ArraySequence<int>(3);

        //look for

    }

    /**
     * Evals a move
     * @return eval of the move
     */
    int evalMove(int x, int y) const {

        // check 5 in a row in every direction
        /*
        int horizontal1 = 0;
        int horizontal2 = 0;
        int vertical1 = 0;
        int vertical2 = 0;
        int diagonal11 = 0;
        int diagonal12 = 0;
        int diagonal21 = 0;
        int diagonal22 = 0;
        int current = currentPlayer;
        #pragma omp parallel sections //shared(horizontal, vertical, diagonal1, diagonal2)
        {
            //horizontal
            #pragma omp section
            {
                //right
                int i1 = 0;
                while (gameBoard[x][y + i1] == current or i1 == 0) {
                    i1++;
                    horizontal1++;
                    if (i1 <= 5 and y + i1 < HEIGHT) {
                        continue;
                    }
                    else break;
                }
                if (i1 == 5) return 10000 - nMoves - 1;
            }
            #pragma omp section
            {
                //left
                int i2 = 0;
                while (gameBoard[x][y - i2] == current or i2 == 0) {
                    i2++;
                    horizontal2++;
                    if (i2 <= 5 and y - i2 >= 0) {
                        continue;
                    }
                    else break;
                }
                if (i2 == 5) return 10000 - nMoves - 1;
            }
            //vertical
            #pragma omp section
            {
                //down
                int i3 = 0;
                while (gameBoard[x + i3][y] == current or i3 == 0) {
                    i3++;
                    vertical1++;
                    if (i3 <= 5 and x + i3 < HEIGHT) {
                        continue;
                    }
                    else break;
                }
                if (i3 == 5) return 10000 - nMoves - 1;
            }
            #pragma omp section
            {
                //up
                int i4 = 0;
                while (gameBoard[x - i4][y] == current or i4 == 0) {
                    i4++;
                    vertical2++;
                    if (i4 <= 5 and x - i4 >= 0) {
                        continue;
                    }
                    else break;
                }
                if (i4 == 5) return 10000 - nMoves - 1;
            }
            //diagonal1 NE-SW
            #pragma omp section
            {
                int i5 = 0;
                while (gameBoard[x + i5][y + i5] == current or i5 == 0) {
                    i5++;
                    diagonal11++;
                    if (i5 <= 5 and x + i5 < HEIGHT and y + i5 < HEIGHT) {
                        continue;
                    }
                    else break;
                }
                if (i5 == 5) return 10000 - nMoves - 1;
            }
            #pragma omp section
            {
                int i6 = 0;
                while (gameBoard.Get(x - i6).Get(y - i6) == current or i6 == 0) {
                    i6++;
                    diagonal12++;
                    if (i6 <= 5 and x - i6 >= 0 and y - i6 >= 0) {
                        continue;
                    }
                    else break;
                }
                if (i6 == 5) return 10000 - nMoves - 1;
            }
            //diagonal2 NW-SE
            #pragma omp section
            {
                int i7 = 0;
                while (gameBoard[x - i7][y + i7] == current or i7 == 0) {
                    i7++;
                    diagonal21++;
                    if (i7 <= 5 and x - i7 >= 0 and y + i7 < HEIGHT) {
                        continue;
                    }
                    else break;
                }
                if (i7 == 5) return 10000 - nMoves - 1;
            }
            #pragma omp section
            {
                int i8 = 0;
                while (gameBoard[x + i8][y - i8] == current or i8 == 0) {
                    i8++;
                    diagonal22++;
                    if (i8 <= 5 and x + i8 < HEIGHT and y - i8 >= 0) {
                        continue;
                    }
                    else break;
                }
                if (i8 == 5) return 10000 - nMoves - 1;
            }
        }// omp sections
        */
        
        ///*
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
        if (i1 == 5) return 10000 - 1;
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
        if (i2 == 5) return 10000 - 1;

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
        if (i3 == 5) return 10000 - 1;
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
        if (i4 == 5) return 10000 - 1;

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
        if (i5 == 5) return 10000 - 1;
        int i6 = 0;
        while (gameBoard[x - i6][y - i6] == currentPlayer or i6 == 0) {
            i6++;
            diagonal1++;
            if (i6 <= 5 and x - i6 >= 0 and y - i6 >= 0) {
                continue;
            }
            else break;
        }
        if (i6 == 5) return 10000 - 1;

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
        if (i7 == 5) return 10000 - 1;
        int i8 = 0;
        while (gameBoard[x + i8][y - i8] == currentPlayer or i8 == 0) {
            i8++;
            diagonal2++;
            if (i8 <= 5 and x + i8 < HEIGHT and y - i8 >= 0) {
                continue;
            }
            else break;
        }
        if (i8 == 5) return 10000 - 1;
        //*/

        //return std::max({ horizontal - 1, vertical - 1, diagonal1 - 1, diagonal2 - 1 });
        return std::pow(3, horizontal - 2) + std::pow(3, vertical - 2) + std::pow(3, diagonal1 - 2) + std::pow(3, diagonal2 - 2) - 1;
    }

    /**
     * Indicates whether the current player wins by playing this move.
     * This function should never be called if player can't move there.
     * @return true if current player makes an alignment by playing this move.
     */
    bool isWinningMove(int x, int y) const {

        // check 5 in a row in every direction
        int i;

        //horizontal
        //right
        i = 0;
        while (gameBoard[x][y + i] == currentPlayer or i == 0){
            i += 1;
            if (i <= 5 and y + i < HEIGHT) {
                continue;
            } else break;
        }
        if (i == 5) return true;
        //left
        i = 0;
        while (gameBoard[x][y - i] == currentPlayer or i == 0) {
            i += 1;
            if (i <= 5 and y - i >= 0) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;
    
        //vertical
        //down
        i = 0;
        while (gameBoard[x + i][y] == currentPlayer or i == 0) {
            i += 1;
            if (i <= 5 and x + i < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;
        //up
        i = 0;
        while (gameBoard[x - i][y] == currentPlayer or i == 0) { 
            i += 1;
            if (i <= 5 and x - i >= 0) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;
    
        //diagonal1 NE-SW
        i = 0;
        while (gameBoard[x + i][y + i] == currentPlayer or i == 0) { 
            i += 1;
            if (i <= 5 and x + i < HEIGHT and y + i < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;
        i = 0;
        while (gameBoard[x - i][y - i] == currentPlayer or i == 0) {
            i += 1;
            if (i <= 5 and x - i >= 0 and y - i >= 0) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;
        
        //diagonal2 NW-SE
        i = 0;
        while (gameBoard[x - i][y + i] == currentPlayer or i == 0) {
            i += 1;
            if (i <= 5 and x - i >= 0 and y + i < HEIGHT) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;
        i = 0;
        while (gameBoard[x + i][y - i] == currentPlayer or i == 0) {
            i += 1;
            if (i <= 5 and x + i < HEIGHT and y - i >= 0) {
                continue;
            }
            else break;
        }
        if (i == 5) return true;

        return false;
    }

    /**
     * @return score of the position.
     */
    int score() const;
};


/*
 * Finds max score element
 * @return max element
 */
/*
ArraySequence<int> findMaxScore(MatrixInt scoreArray) {
    ArraySequence<int> posDataMax = scoreArray[0];
    if (scoreArray.GetLength() > 1) {
        ArraySequence<int> posData;
        for (int i = 1; i < scoreArray.GetLength(); i++) {
            posData = scoreArray[i];
            if (posData[2] > posDataMax[2])
                posDataMax = posData;
        }
    }
    return posDataMax;
}
*/

/*
 * Recursively solve a Gomoku position using Negamax (opt Minimax) algorithm.
 * @return the score of a position:
 *  - 0 for a draw game
 *  - positive score if you can win whatever your opponent is playing. Your score is
 *    the number of moves before the end you can win (the faster you win, the higher your score)
 *  - negative score if your opponent can force you to lose. Your score is the oposite of
 *    the number of moves before the end you will lose (the faster you lose, the lower your score).
 */
///*
ArraySequence<int> negamax(const Position position, /* MatrixInt searchPattern,*/ int depth, int alpha, int beta) {

    if (position.nMoves == Position::WIDTH * Position::HEIGHT) // check for draw game
        return ArraySequence<int>(3, 0);

    //if (depth == MAX_DEPTH) // depth check
        //return position.score(); 
        //return ArraySequence<int>(3, 0);

    int max = 90 - depth - 1;	// upper bound of our score as we cannot win immediately
    if (beta > max) {
        beta = max;                     // there is no need to keep beta above our max possible score.
        if (alpha >= beta) return alpha;  // prune the exploration if the [alpha;beta] window is empty.
    }

    /*
    MatrixInt scoreArray = MatrixInt();
    //MatrixInt scoreArray = MatrixInt(searchPattern.GetLength(), ArraySequence<int>(3, -100000));
    //MatrixInt scoreArray = searchPattern;
    //#pragma omp parallel for shared(position, scoreArray, alpha, beta)
    for (int i = 0; i < searchPattern.GetLength(); i++) {
        //int x = scoreArray[i][0];
        //int y = scoreArray[i][1];
        int x = searchPattern[i][0];
        int y = searchPattern[i][1];
        if (position.radius + 2 > std::max(std::abs(x - position.centerX), std::abs(y - position.centerY))) {
            if (position.canMove(x, y)) {
                ArraySequence<int> posData = ArraySequence<int>(3);
                posData[0] = x;
                posData[1] = y;
                int myEval = position.evalMove(x, y) - depth;    
                if (depth == 0) {
                    std::cout << x << " " << y << std::endl;
                    if (x == 10 and y == 8) {
                        std::cout << myEval << std::endl;
                    }
                }
                if (myEval > 1000) {
                    posData[2] = myEval;
                    std::cout << "win of " << position.currentPlayer << " at depth " << depth << " : " << &posData << std::endl;
                    return posData;
                }
                else if (depth == MAX_DEPTH or position.nMoves < 5) {
                    //scoreArray[i][2] = myEval;
                    posData[2] = myEval;
                    if (myEval > alpha) { alpha = myEval; }
                    if (myEval >= beta) {
                        //scoreArray.Append(posData);
                        //scoreArray[i] = posData;
                        return posData;
                        //break;
                    }
                }
                else {
                    Position newPosition = position;
                    newPosition.move(x, y);
                    int opEval = negamax(newPosition, searchPattern, depth + 1, alpha - 1, beta - 1)[2];
                    int Eval = myEval - opEval;
                    posData[2] = Eval;
                    if (Eval < -1000) {
                        //std::cout << "lose " << position.currentPlayer << " : " << &posData << std::endl;
                        //return posData;
                        continue;
                    }
                    //scoreArray[i][2] = Eval;
                    if (Eval > alpha) { alpha = Eval; }
                    if (Eval >= beta) {
                        //scoreArray.Append(posData);
                        //scoreArray[i] = posData;
                        return posData;
                        //break;
                    }
                }
                scoreArray.Append(posData);
            }
        }
    }
    */

    PriorityQueue<std::pair<int, int>> scoreQueue = PriorityQueue<std::pair<int, int>>();
    for (int x = 0; x < Position::HEIGHT; x++) {
        for (int y = 0; y < Position::WIDTH; y++) {
            if (position.radius + 3 > std::max(std::abs(x - position.centerX), std::abs(y - position.centerY))) {
                if (position.canMove(x, y)) {
                    std::pair<int, int> move = std::pair<int, int>(x, y);
                    int eval = position.evalMove(x, y) - depth;
                    scoreQueue.Insert(move, eval);
                }
            }
        }
    }
    ///*
    if (depth == 0) {
        for (int i = 0; i < scoreQueue.GetLength(); i++)
            std::cout << scoreQueue[i].item.first << " " << scoreQueue[i].item.second << " " << scoreQueue[i].priority << std::endl;
    }
    //*/
    ArraySequence<int> bestMove = ArraySequence<int>(3, -100000);
    if (depth == MAX_DEPTH or position.nMoves < 5) {
        Item<std::pair<int, int>> item = scoreQueue.GetHighestPriorityItem();
        bestMove[0] = item.item.first;
        bestMove[1] = item.item.second;
        bestMove[2] = item.priority;
    }
    else {
        if (depth == 0) {
            std::cout << "--------------------------------------------------" << std::endl;
        }
        for (int i = 0; i < scoreQueue.GetLength(); i++) {
            Item<std::pair<int, int>> item = scoreQueue.GetHighestPriorityItem();
            if (depth == 0) {
                std::cout << item.item.first << " " << item.item.second << " " << item.priority << " ";
            }
            if (depth == 1) {
                std::cout << "d1--------------------------------------------------" << std::endl;
                std::cout << item.item.first << " " << item.item.second << " " << item.priority << " ";
            }
            //check win
            if (item.priority > 1000) {
                bestMove[0] = item.item.first;
                bestMove[1] = item.item.second;
                bestMove[2] = item.priority;
                if (depth == 0) {
                std::cout << std::endl;
                }
                break;
            }
            // check future
            Position newPosition = position;
            newPosition.move(item.item.first, item.item.second);
            int opEval = negamax(newPosition, depth + 1, alpha - 1, beta - 1)[2];
            int Eval = item.priority - opEval;
            if (depth == 0) {
                std::cout << Eval << std::endl;
            }
            if (Eval < -1000) {
                scoreQueue.Delete();
                continue;
            }
            else {
                bestMove[0] = item.item.first;
                bestMove[1] = item.item.second;
                bestMove[2] = item.priority;
                break;
            }
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
    */
    return bestMove;
}
//*/