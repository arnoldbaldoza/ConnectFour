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
//#include <stdlib.h>
#include <ctime>
#include <chrono>
#include "Solver_ConnectFour.h"
#include "RandomPlay_Solver.h"

unsigned long long int iTotalNumberOfMoves;

//
// Constructors and Initializers
//

/// <summary>
/// RandomPlay_Solver() initializes the randomizer, the board configuration, and the move history associated with the board
/// </summary>
/// <param name=""></param>
RandomPlay_Solver::RandomPlay_Solver(void) : Solver_ConnectFour () {
    srand((unsigned int)time(NULL)); // initialize randomizer
    s_board.InitBoard();
    s_mh.ResetHistory();
    iTotalNumberOfMoves = 0;
    bShowMoveByMove = false;
    bShowWinner = false;
    SetPlayerName("Random Connect Four Player");
}

//
// Methods to find "Best" Move
//


/// <summary>
/// RandomPlay_Solver::GetBestMove() returns the "best move" for the player.  For RandomPlay_Solver, the best move is a random move.
/// For randomize play, this function does not require any parameters.
/// </summary>
/// <returns>Best Move</returns>
Move RandomPlay_Solver::GetBestMove(void) {
    std::vector<Move> ValidMoves;
    Move bestMove = 0;

    // Find all Valid Moves 
    for (auto const& v : s_board.MoveSequence) {
        if (s_board.IsValidMove(v)) {
            ValidMoves.push_back(v);
        }
    }

    // return a random move
    if (ValidMoves.size() != 0) {
        return ValidMoves.at(rand() % ValidMoves.size());
    }
    else {
        return (Move)0;
    }
}

//
// Tournament Methods
//

/// <summary>
/// RandomPlay_Solver::SolverBoard is used for "tournament" play.  The solver takes the specified board and returns the "best" move.
/// Other parameters of this function need to be uniform for other solvers and are thus subject to change.  Currently, MoveNumber is passed 
/// as the other solvers need MoveNumber to evaluate the board.
/// </summary>
/// <param name="b">Board configuration to be "solved"</param>
/// <param name="MoveNumber">Current MoveNumber (used in the evaluation function of other solvers)</param>
/// <returns></returns>
Move RandomPlay_Solver::SolveBoard(const Board & b, unsigned int MoveNumber) {
    s_board.CopyBoard(b); // copy the board into the solver
    return GetBestMove(); // return the best move
}

//
// Self-Play Methods
//

/// <summary>
/// RandomPlay_Solver::RandomPlay() simulates a game between two players who both randomly select moves.  Used for debuggging purposes.
/// </summary>
/// <param name="playerToMove">Player to make the first move</param>
/// <returns>1, if RED wins; -1, if YELLOW wins; 0, if drawn game</returns>
int RandomPlay_Solver::SelfPlay(typePlayer playerToMove) {
    int color;  // for minimizing and maximizing the board evaluation
    int winner; // winner of the game
    Move m;     // move to be played

    // Initialize the board
    s_board.InitBoard(playerToMove);
    s_mh.ResetHistory();
    
    if (playerToMove == RED) {
        color = 1;
    }
    else {
        color = -1;
    }

    // Loop until there is a winner
    for (; ; ) {

        // 1. If there are no valid moves on the board, the game is a draw
        if (s_board.IsNoMove()) {
            if (bShowWinner) {
                std::cout << " DRAW!\n";
            }    
            winner = 0;
            break;
        }

        // 2. Select a Valid Move and Play it
        m = GetBestMove();

        if (bShowMoveByMove) {
            std::cout << m << " ";
        }

        s_board.MakeMove(m, playerToMove);
        s_mh.AddMove(m);

        // 3. Check if the moving player won the game
        if (s_board.IsWin(playerToMove)) {          
            if (playerToMove == RED) {
                if (bShowWinner) {
                    std::cout << " RED WINS!\n";
                }
                winner = 1;
            }
            else {
                if (bShowWinner) {
                    std::cout << " YELLOW WINS!\n";
                }
                winner = -1;
            }
            break;
        }

        // 4. Toggle player for the next move
        playerToMove = (typePlayer)!playerToMove;
        color = -color;
    }

    // Print out the Move History for the game
    s_mh.PrintMoveHistory();

    // Update statistics
    iTotalNumberOfMoves += s_mh.NumberOfMoves();

    // return the result of the game
    return winner;
}

/// <summary>
/// RandomPlay_Solver::RandomMatch() plays a number of games between two players who both randomly select moves.  Used for debugging purposes.
/// </summary>
/// <param name="nRuns">Number of Games to be played</param>
void RandomPlay_Solver::SelfPlayMatch(unsigned int nRuns) {
    std::cout << "Playing " << nRuns << " Random Matches\n";

    int winner; // result of each game

    // statistics to capture
    unsigned int redW = 0, yellowW = 0, iTotalGames = 0;
    iTotalNumberOfMoves = 0;

    // don't be verbose -- allows for accurate timing of the games
    bShowMoveByMove = false;
    bShowWinner = false;

    // Start the clock
    auto c_start_ms = std::chrono::steady_clock().now();

    // Play game nRuns times...
    for (unsigned int i = 0; i < nRuns; i++) {
        // Play the Game
        winner = SelfPlay(RED);

        // Update statistics
        iTotalGames++;
        switch (winner) {
        case -1:
            yellowW++;
            break;
        case 1:
            redW++;
            break;
        default:
            break;
        }

        if (bShowMoveByMove || bShowWinner) {
            std::cout << std::endl;
        }

        // Don't show Move History -- allows for accurate timing statistics
        //s_mh.PrintMoveHistory();
    }

    // Stop the clock and calculate duration
    auto c_end_ms = std::chrono::steady_clock().now();
    std::chrono::milliseconds duration_ms = (std::chrono::duration_cast<std::chrono::milliseconds>)(c_end_ms - c_start_ms);

    // Display statistics
    std::cout << " Total Number Of Games : " << iTotalGames << "\n";
    std::cout << " Total Number Of Moves : " << iTotalNumberOfMoves << "\n";
    std::cout << " Total Duration (msec): " << duration_ms.count() << "msec\n";
    std::cout << "Moves Per msec: " << (double)(iTotalNumberOfMoves / (double)(duration_ms.count())) << "\n";

    double redP, yellowP, drawP;
    redP = (double)redW / iTotalGames * 100.0;
    yellowP = (double)yellowW / iTotalGames * 100.0;
    drawP = (double)((iTotalGames - (yellowW + redW)) / (double)iTotalGames) * 100.0;

    std::cout << " Total Number Of Red Wins : " << redW << " [" << redP << "]\n";
    std::cout << " Total Number Of Yellow Wins : " << yellowW << " [" << yellowP << "]\n";
    std::cout << " Total Number Of Draws : " << iTotalGames - (yellowW + redW) << " [" << drawP << "]\n";

}