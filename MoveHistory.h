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
#include<vector>

typedef unsigned int Move;
typedef std::vector <Move> t_MoveHistory;

/// <summary>
/// MoveHistory allows one to track the moves played in a game.  This implementation uses a vector to store the moves and assumes players alternate moves.
/// </summary>
class MoveHistory
{
private:
	t_MoveHistory Moves;

public:
	void AddMove(Move m);
	void RemoveMove(void);
	void ResetHistory(void);
	unsigned int NumberOfMoves(void);
	void PrintMoveHistory(void);
};

