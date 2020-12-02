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
/// MinimaxABPlay_Solver is derived from Solver_ConnectFour and selects its moves using the minimax algorithm with alpha-beta pruning.
/// Reference: https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
/// </summary>
class MinimaxABPlay_Solver :
	public Solver_ConnectFour
{
private:
	//std::string s_PlayerName = "Minimax Alpha-Beta Player";
	unsigned long long int iTotalNumberOfMoves;
	unsigned long long int numberOfNodes;
	bool bVarietyOfPlay = false;
	bool bShowMoveByMove = true;
	bool bShowWinner = true;
	int s_max_depth = 12;

	
	Move GetBestMove(typePlayer playerToMove, unsigned int max_depth, bool isMaximizingPlayer, MoveHistory* mh);
	Move GetBestMoveMinimaxAB(typePlayer playerToMove, unsigned int max_depth, bool isMaximizingPlayer, unsigned int MoveNumber);
	int AlphaBeta(int depth, int alpha, int beta, typePlayer playerToMove, bool isMaximizingPlayer, unsigned int MoveNumber);
	

public:
	//std::string GetPlayerName(void);
	//void SetPlayerName(std::string s);
	MinimaxABPlay_Solver(int max_depth = 12, bool bVariety = false);
	Move SolveBoard(const Board& b, unsigned int max_depth, unsigned int MoveNumber);
	Move SolveBoard(const Board& b, unsigned int MoveNumber);
	int SelfPlay(typePlayer playerToMove, unsigned int max_depth);
	void SelfPlayMatch(unsigned int nRuns, unsigned int max_depth);
};

