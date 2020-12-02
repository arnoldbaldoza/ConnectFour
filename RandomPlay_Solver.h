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
/// RandomPlay_Solver is derived from Solver_ConnectFour and randomly selects its moves.
/// </summary>
class RandomPlay_Solver : 
	public Solver_ConnectFour 
{
private:
	unsigned long long int iTotalNumberOfMoves;
	bool bShowMoveByMove = false;
	bool bShowWinner = false;

	Move GetBestMove(void);

public:
	RandomPlay_Solver(void);

	Move SolveBoard(const Board& b, unsigned int MoveNumber);

	int SelfPlay(typePlayer playerToMove);
	void SelfPlayMatch(unsigned int nRuns);

	
};

