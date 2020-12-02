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
#include "MoveHistory.h"

/// <summary>
/// MoveHistory::AddMove() adds a move to the back of the vector.
/// </summary>
/// <param name="m">Move to add to the move history</param>
void MoveHistory::AddMove(Move m) {
	Moves.push_back(m);
}

/// <summary>
/// MoveHistory::RemoveMove() removes the last move that was added (LIFO)
/// </summary>
/// <param name=""></param>
void MoveHistory::RemoveMove(void) {
	Moves.pop_back();
}

/// <summary>
/// MoveHistory::ResetHistory() clears the move history (i.e., clears the vector)
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void MoveHistory::ResetHistory(void) {
	Moves.clear();
}

/// <summary>
/// MoveHistory::NumberOfMoves() returns the number of moves in the move history
/// </summary>
/// <param name=""></param>
/// <returns>Moves.size()</returns>
unsigned int MoveHistory::NumberOfMoves(void) {
	return Moves.size();
}

/// <summary>
/// MoveHistory::PrintMoveHistory() displays the move history (i.e., all moves added to move history)
/// </summary>
/// <param name=""></param>
void MoveHistory::PrintMoveHistory(void) {
	
	std::cout << std::endl << "MOVE HISTORY: ";
	for (t_MoveHistory::iterator m_it = Moves.begin(); m_it != Moves.end(); m_it++) {
		std::cout << *m_it << " ";
	}
	std::cout << std::endl;
}