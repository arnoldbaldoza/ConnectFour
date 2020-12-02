/*
  MyConnectFour, multiple solvers developed under C++

  MyConnectFour is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  MyConnectFour is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include "RandomPlay_Solver.h"
#include "MinimaxPlay_Solver.h"
#include "MinimaxABPlay_Solver.h"

// Global Variables used in tournament play.  Future work is to move this into a tournament class.
bool bShowWinner = true;
bool bShowMoveByMove = true;
bool bShowMoveHistory = false;
bool bShowGameNumber = true;

/// <summary>
/// PlayTwoSolvers() allows two solvers (both derived from Solver_ConnectFour class) to play each other.  
/// Fundamentally, each solver is presented with a board and is asked for its best move.  Solvers alternate with each move until the game is won or is drawn.
/// Solvers do not think while it is the other solvers turn to move.  Future work is to allow solvers to think during the other player's move.
/// Both solvers are initialized prior to this function call.
/// </summary>
/// <param name="p1">First Solver (to play as RED)</param>
/// <param name="p2">Second Solver (to play as YELLOW)</param>
/// <returns></returns>
int PlayTwoSolvers( Solver_ConnectFour *p1, Solver_ConnectFour *p2) {
    int winner;
    Move m;
    typePlayer playerToMove = RED;  // RED moves first; in this case p1 is RED, P2 is YELLOW

    Board vboard; // the tournament board
    vboard.InitBoard(playerToMove);

    MoveHistory mh; // the move history
    mh.ResetHistory();

    // Loop until there is a winner
    for (; ; ) {
        
        // 1. If there are no valid moves on the board, the game is a draw
        if (vboard.IsNoMove()) {
            winner = 0;
            break;
        }

        // 2. Select a Valid Move and Play it
        if (playerToMove == RED) {
            m = p1->SolveBoard(vboard, mh.NumberOfMoves());
        }
        else {
            m = p2->SolveBoard(vboard, mh.NumberOfMoves());
        }

        if (bShowMoveByMove) {
            std::cout << m << " ";
        }

        vboard.MakeMove(m,playerToMove);
        mh.AddMove(m);


        // 3. Check if the moving player won the game
        if (vboard.IsWin(playerToMove)) {
            winner = (playerToMove == RED) ? 1 : -1;
            break;
        }

        // 4. Toggle player for the next move
        playerToMove = (typePlayer)!playerToMove;
    }

    if (bShowWinner) {
        switch (winner) {
        case 1:
            std::cout << " RED WINS! \n";
            break;
        case -1:
            std::cout << " YELLOW WINS! \n";
            break;
        default:
            std::cout << " DRAW! \n";
            break;
        }
    }
    
    if (bShowMoveHistory)
        mh.PrintMoveHistory();

    return winner;
}

/// <summary>
/// MatchPlay () allows two solvers (both derived from Solver_ConnectFour class) to play each other for a specified number of games. 
/// </summary>
/// <param name="p1">First Solver (to play as RED)</param>
/// <param name="p2">Second Solver (to play as YELLOW)</param>
/// <param name="numberOfGames">Number of Games to be Played</param>
void MatchPlay(Solver_ConnectFour* p1, Solver_ConnectFour* p2, unsigned int numberOfGames = 1) {
    unsigned long int NumGames = 0, RedWins = 0, YellowWins = 0, Draw = 0;
    
    for (unsigned int i = 0; i < numberOfGames; i++) {
        if (bShowGameNumber)
            std::cout << "[ " << i << " ] ";
        int winner = PlayTwoSolvers(p1, p2);
        NumGames++;
        switch (winner) {
        case 1:
            RedWins++;
            break;
        case -1:
            YellowWins++;
            break;
        case 0:
            Draw++;
            break;
        default:
            break;
        }
    }

    std::cout << std::endl;
    std::cout << "Number of Games: " << NumGames << std::endl;
    std::cout << "Number of Red Wins: " << RedWins << std::endl;
    std::cout << "Number of Yellow Wins: " << YellowWins << std::endl;
    std::cout << "Number of Draws: " << Draw << std::endl;
}

int main()
{
    /* Random Play */
    /*
    RandomPlay_Solver rp_Solver;
    rp_Solver.SelfPlayMatch(3);
    */

    /* Minimax Play */
    /*
    MinimaxPlay_Solver mmp_Solver;
    mmp_Solver.SelfPlayMatch(1, 10); // 60 games with a max depth of 8
    */

    /* Minimax with Alpha-Beta Pruning Play */
    /*
    MinimaxABPlay_Solver mmABp_Solver;
    mmABp_Solver.SelfPlayMatch(1, 14);
    */

    /* Playing Two Solvers Against Each Other */
    unsigned int nGames = 1000;
    RandomPlay_Solver rp_Solver;
    MinimaxPlay_Solver mm_Solver(8, false);
    MinimaxABPlay_Solver mmABp_Solver1(12, true);   // Variety of play == TRUE
    MinimaxABPlay_Solver mmABp_Solver2 (4, false);  // Variety of play == FALSE

    Solver_ConnectFour* p1 = &mmABp_Solver1;
    Solver_ConnectFour* p2 = &mmABp_Solver2;

    MatchPlay(p1, p2, nGames);  

    p1 = &rp_Solver;
    p2 = &mm_Solver;

    MatchPlay(p1, p2, nGames);
    
    /* Forcing user input before ending the program */
    std::string strInput;
    std::cin >> strInput;
}