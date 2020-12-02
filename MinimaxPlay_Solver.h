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
#pragma once
#include "Solver_ConnectFour.h"

/// <summary>
/// MinimaxPlay_Solver is derived from Solver_ConnectFour and selects its moves using the minimax algorithm.
/// Reference: https://en.wikipedia.org/wiki/Minimax
/// </summary>
class MinimaxPlay_Solver :
	public Solver_ConnectFour
{
private:
	unsigned long long int iTotalNumberOfMoves;
	unsigned long long int numberOfNodes;
	bool bVarietyOfPlay;
	bool bShowMoveByMove;
	bool bShowWinner;
	int s_max_depth;

	Move GetBestMove(typePlayer playerToMove, unsigned int max_depth, bool isMaximizingPlayer, MoveHistory* mh);
	Move GetBestMoveMinimax(typePlayer playerToMove, unsigned int max_depth, bool isMaximizingColor, unsigned int MoveNumber);
	int Minimax(int depth, typePlayer playerToMove, bool isMaximizingPlayer, unsigned int MoveNumber);

public:
	MinimaxPlay_Solver (int md = 8, bool bVariety = false);

	Move SolveBoard(const Board& b, unsigned int MoveNumber);
	Move SolveBoard(const Board& b, unsigned int max_depth, unsigned int MoveNumber);
	
	int SelfPlay(typePlayer playerToMove, unsigned int max_depth);
	void SelfPlayMatch(unsigned int nRuns, unsigned int max_depth);
};

