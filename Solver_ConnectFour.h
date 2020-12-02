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
#include<iostream>
#include "Board.h"
#include "MoveHistory.h"

/// <summary>
/// Solver_ConnectFour is the base class for our Connect Four solvers
/// </summary>
class Solver_ConnectFour
{
protected:
	std::string s_PlayerName;
	Board s_board;
	MoveHistory s_mh;
	typePlayer s_playerToMove;
	typePlayer s_winner;

public:
	Solver_ConnectFour(void);

	std::string GetPlayerName(void);
	void SetPlayerName(std::string s); 

	virtual Move SolveBoard(const Board& b, unsigned int MoveNumber) = 0;	// To be defined in derived classes
};

