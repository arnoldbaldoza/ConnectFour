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
#include <chrono>
#include "Solver_ConnectFour.h"
#include "MinimaxPlay_Solver.h"

#define MAX_BESTVAL (WIDTH * (HEIGHT + 1))
// #define MIN_SCORE (-(WIDTH * HEIGHT) / 2 + 3)
#define DRAW 0
#define WIN 10000
#define LOSS -10000
#define MAX_DEPTH 8

//
// Constructor and Initializers
//

/// <summary>
/// MinimaxPlay_Solver::MinimaxPlay_Solver() initializes the board configuration, the move history associated with the board, and the maximum depth of the search
/// </summary>
/// <param name="md">Maximum depth to be searched (default is 8)</param>
MinimaxPlay_Solver::MinimaxPlay_Solver(int md, bool bVariety) : Solver_ConnectFour() {
    s_board.InitBoard();
    s_mh.ResetHistory();
    s_max_depth = md;
    bVarietyOfPlay = bVariety;
    iTotalNumberOfMoves = 0;
    numberOfNodes = 0;
    bShowMoveByMove = true;
    bShowWinner = true;
    SetPlayerName("Minimax Connect Four Player");
}


//
// Methods to find "best" move
//

/// <summary>
/// MinimaxPlay_Solver::GetBestMove() simply passes along the necessary parameters to GetBestMoveMinimax() to find the best move for the player.
/// </summary>
/// <param name="playerToMove">Player to move</param>
/// <param name="max_depth">Maximum Depth to search</param>
/// <param name="isMaximizingPlayer">Are we Maximizing or Minimizing the board evaluation for the moving player?</param>
/// <param name="mh">Move History (needed for current number of moves)</param>
/// <returns>Best Move</returns>
Move MinimaxPlay_Solver::GetBestMove(typePlayer playerToMove, unsigned int max_depth, bool isMaximizingPlayer, MoveHistory *mh) {
    return GetBestMoveMinimax(playerToMove, max_depth, isMaximizingPlayer, mh->NumberOfMoves());
}

/// <summary>
/// MinimaxPlay_Solver::GetBestMoveMinimax() uses the minimax algorithm to find the best move for the player.
/// </summary>
/// <param name="playerToMove">Player to Move</param>
/// <param name="max_depth">Maximum Depth to search</param>
/// <param name="isMaximizingColor">Are we Maximizing or Minimizing the board evaluation for the moving player?</param>
/// <param name="MoveNumber">Current Move Number (used in board evaluation function)</param>
/// <returns>Best Move</returns>
Move MinimaxPlay_Solver::GetBestMoveMinimax(typePlayer playerToMove, unsigned int max_depth, bool isMaximizingColor, unsigned int MoveNumber) {
    
    Move bestMove = 0;
    double bestVal = -MAX_BESTVAL; 
    Board b;
    int color;

    typePlayer p = playerToMove;

    color = isMaximizingColor ? 1 : -1;

    /* 
    if (isMaximizingColor) {
        color = 1;
    }
    else {
        color = -1;
    }
    */

    // If the player can win on the next move, return that winning move
    b.CopyBoard(s_board);
    bestMove = b.FindKillerMove(p);
    if (bestMove != 0) {
        bestVal = color * ((MAX_BESTVAL - MoveNumber) / 2);
    }
    else {
        // If Killer Move does not exist, find the best move

        // For each valid move, find the move with the "best" value (max for maximizing player, min for minimizing player)
        for (auto const& v : s_board.MoveSequence) {
            if (s_board.IsValidMove(v)) {
                // If the possible move is valid, 
                numberOfNodes++;    // capture statistics of number of Nodes visited
                
                // ... Make the  Move...
                s_board.MakeMove(v, p);

                // ... Find the opponent's response, returning the appropriate valuation ...
                double moveVal = Minimax(max_depth, (typePlayer)(!playerToMove), !isMaximizingColor, MoveNumber + 1);

                // ... add some noise to the moveVal if it is equal to bestVal ...
                if ((moveVal == bestVal) && (bVarietyOfPlay)) {
                    moveVal += (-1 + 2 * ((float)rand()) / (float)RAND_MAX);
                }

                // ... Keep the best Move ...
                if (isMaximizingColor) {
                    if (moveVal > bestVal) {  // NOT greater than or Equal to force at least one move
                        bestMove = v;
                        bestVal = moveVal;
                    }
                }
                else // Minimizing Player
                    if (moveVal < bestVal) {
                        bestMove = v;
                        bestVal = moveVal;
                    }

                // ... Take back the move and loop to the next valid move ...
                s_board.TakeBackMove(v, (typePlayer)(p));
            }
        }
    }
    // Return the bestMove
    return bestMove;
}

/// <summary>
/// MinimaxPlay_Solver::Minimax() is the implementation of the Minimax algorithm
/// </summary>
/// <param name="depth">Depth to search</param>
/// <param name="playerToMove">Player To Move</param>
/// <param name="isMaximizingPlayer">Are we Maximizing or Minimizing the board evaluation for the moving player?</param>
/// <param name="MoveNumber">Used in the board evaluation</param>
/// <returns>Value of the current position</returns>
int MinimaxPlay_Solver::Minimax(int depth, typePlayer playerToMove, bool isMaximizingPlayer, unsigned int MoveNumber)
{
    typePlayer p = playerToMove;
    int color;

    color = isMaximizingPlayer ? 1 : -1;
    /*
    if (isMaximizingPlayer) {
        color = 1;
    }
    else {
        color = -1;
    }
    */

    // Handle Terminal Nodes: does player p win?
    if (s_board.IsWin((typePlayer)(p))) {
        return color * ((MAX_BESTVAL - MoveNumber) / 2);
    }

    // if terminal node (i.e., no move to make) or depth = 0, return DRAW
    if ((depth == 0) || (s_board.IsNoMove())) {
        return DRAW;
    }

    int bestVal = 0;

    if (isMaximizingPlayer) {
        bestVal = -MAX_BESTVAL;

        // For each valid move, return the best value
        for (int v : s_board.MoveSequence) {
            if (s_board.IsValidMove(v)) {
                // process the move if it's valid
                numberOfNodes++;
                s_board.MakeMove(v, p);

                bestVal = std::max(bestVal, Minimax(depth - 1, (typePlayer)(!playerToMove), !(isMaximizingPlayer), MoveNumber+1));

                s_board.TakeBackMove(v, p);
            }
        }
        return bestVal;
    }
    else { // Minimizing Player
        bestVal = MAX_BESTVAL;

        // For each valid move, return the best value
        for (int v : s_board.MoveSequence) {
            if (s_board.IsValidMove(v)) {
                // process the move if it's valid
                numberOfNodes++;
                s_board.MakeMove(v, p);

                bestVal = std::min(bestVal, Minimax(depth - 1, (typePlayer)(!playerToMove), !isMaximizingPlayer, MoveNumber+1));

                s_board.TakeBackMove(v, p);
            }
        }
        return bestVal;
    }
}

//
// Tournament Methods
//

/// <summary>
/// MinimaxPlay_Solver::SolveBoard() is used for tournament play.   The solver takes the specified board and returns the "best" move.
/// Other parameters of this function need to be uniform for other solvers and are thus subject to change.  Currently, MoveNumber is passed 
/// as the other solvers need MoveNumber to evaluate the board.
/// </summary>
/// <param name="b">Board configuration to be "solved"</param>
/// <param name="MoveNumber">Current MoveNumber (used in the evaluation function of the solver)</param>
/// <returns></returns>
Move MinimaxPlay_Solver::SolveBoard(const Board& b, unsigned int MoveNumber) {
    s_board.CopyBoard(b);
    return GetBestMoveMinimax(s_board.GetPlayerToMove(), s_max_depth, true, MoveNumber);
}
Move MinimaxPlay_Solver::SolveBoard(const Board& b, unsigned int max_depth, unsigned int MoveNumber) {
    s_board.CopyBoard(b);
    return GetBestMoveMinimax(s_board.GetPlayerToMove(), max_depth, true, MoveNumber);
}

//
// Self-Play Methods
//

/// <summary>
/// MinimaxPlay_Solver::MinimaxPlay() simulates a game between two players, searching to a specified max_depth. Used for debuggging purposes.
/// </summary>
/// <param name="playerToMove">First player to move</param>
/// <param name="max_depth">Maximum depth to be searched</param>
/// <returns>1, if RED wins; -1, if YELLOW wins; 0, if drawn game</returns>
int MinimaxPlay_Solver::SelfPlay(typePlayer playerToMove, unsigned int max_depth) {
    int color;  // for minimizing and maximizing the board evaluation
    int winner; // winner of the game
    Move m;     // move to be played
    
    // Initialize the board
    s_board.InitBoard();
    s_mh.ResetHistory();
    
    // playerToMove = player who has the first move
    s_playerToMove = playerToMove;

    color = (playerToMove == RED) ? 1 : -1;
    
    /*
    if (playerToMove == RED) {
        color = 1;
    }
    else {
        color = -1;
    }
    */

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
        m = GetBestMove(playerToMove, max_depth, true, &s_mh);

        if (bShowMoveByMove) {
            std::cout << m << " ";
        }

        s_board.MakeMove(m, playerToMove);
        s_mh.AddMove(m);

        // 3. Check if the moving player won the game
        if (s_board.IsWin(playerToMove)) {
            //s_mh.PrintMoveHistory();
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

    // return the results of the game
    return winner;
}

/// <summary>
/// MinimaxPlay_Solver::MinimaxMatch() plays a number of games between two players, searching to a specified max_depth.  Used for debugging purposes.
/// </summary>
/// <param name="nRuns">Number of Games to be Played</param>
/// <param name="max_depth">Maximum depth to be searched</param>
void MinimaxPlay_Solver::SelfPlayMatch(unsigned int nRuns, unsigned int max_depth) {
    std::cout << "Playing " << nRuns << " Minimax Matches of depth = " << max_depth << "\n";

    int winner; // result of each game

    // statistics to capture
    unsigned int redW = 0, yellowW = 0, iTotalGames = 0;
    iTotalNumberOfMoves = 0;

    // don't be verbose -- allows for accurate timing of the games
    bShowMoveByMove = false;
    bShowWinner = false;

    // Start the clock
    auto c_start_ms = std::chrono::steady_clock().now();

    // Play the game rRuns times...
    for (unsigned int i = 0; i < nRuns; i++) {
        std::cout << i << " ";

        // Play the game
        winner = SelfPlay(RED, max_depth);

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