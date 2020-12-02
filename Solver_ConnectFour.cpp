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
#include "Solver_ConnectFour.h"

Solver_ConnectFour::Solver_ConnectFour(void) {
	s_board.InitBoard();
	s_mh.ResetHistory();
	s_playerToMove = RED;
	SetPlayerName("Generic Connect Four Solver");
}

//
// Member-access methods
//

/// <summary>
/// Solver_ConnectFour::GetPlayerName() returns the name of the solver
/// </summary>
/// <param name=""></param>
/// <returns>s_PlayerName</returns>
std::string Solver_ConnectFour::GetPlayerName(void) {
	return s_PlayerName;
}

/// <summary>
/// Solver_ConnectFour::SetPlayerName() set the name of the solver to a specified string
/// </summary>
/// <param name="s">New name of the solver</param>
void Solver_ConnectFour::SetPlayerName(std::string s) {
	s_PlayerName = s;
}