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
#include <bitset>
#include <ctime>
#include "Board.h"

//
// Constructors and Initializers
//

/// <summary>
/// Board() is the constructor that initializes the board.  By default, typePlayer p is RED.
/// </summary>
/// <param name="p">Player to move in the default board configuration</param>
Board::Board(typePlayer p) {
	InitBoard(p);
}

/// <summary>
/// Board::InitBoard() initializes the board (all positions empty) and the height[] to contain the first empty square in a column
/// </summary>
/// <param name="player">Player to move in the default board configuration</param>
void Board::InitBoard(typePlayer player) {
	// player to move in this position is specified by player; by default, b_PlayerToMove = RED
	b_PlayerToMove = player; 

	b[0] = (BitBoard) 0ULL; // initialize bitboard with all 0's
	b[1] = (BitBoard) 0ULL; // initialize bitboard with all 0's
	/* Future Work: Transposition Board -- mirror image of the moves */
	//transpose_b[0] = (BitBoard)0ULL; // initialize bitboard with all 0's
	//transpose_b[1] = (BitBoard)0ULL; // initialize bitboard with all 0's

	int h = 0;

	// height contains the first empty square in a column
	// initialize to height[i] to the first empty square in column i (i.e., 0, 7, 14, 21, 28, 35, 42)
	for (int i = 1; i < (WIDTH + 1); i++) {
		height[i] = (h * WIDTH);

		/* Future Work: Transposition Board -- mirror image of the moves */
		//Move t_i = TransposeMove((Move)i);
		//t_height[(WIDTH+1) - i] = (h * WIDTH);
		//t_height[i] = (h * WIDTH);

		h++;
	}
}

//
// Member-Access functions
//

/// <summary>
/// GetBoard() returns the board associated with the specified player
/// </summary>
/// <param name="p">Specified player</param>
/// <returns>Board associated with the specified player (not a pointer)</returns>
BitBoard Board::GetBoard(typePlayer p) {
	return b[p];
}

/// <summary>
/// Board::GetPlayerToMove() returns the value of b_PlayerToMove
/// </summary>
/// <param name=""></param>
/// <returns>Value of b_PlayerToMove</returns>
typePlayer Board::GetPlayerToMove(void) {
	return b_PlayerToMove;
}

/// <summary>
/// Board::SetPlayerToMove() sets b_PlayerToMove to the specified player
/// </summary>
/// <param name="p">Player to which to set b_PlayerToMove</param>
void Board::SetPlayerToMove(typePlayer p) {
	b_PlayerToMove = p;
}

/// <summary>
/// TogglePlayerToMove() toggles b_PlayerToMove between RED and YELLOW
/// </summary>
/// <param name=""></param>
void Board::TogglePlayerToMove(void) {
	b_PlayerToMove = (typePlayer) !b_PlayerToMove;
}

//
// Move Related Functions
//

/// <summary>
/// Board::IsNoMove() determines if a Valid Move exists and returns the appropriate bool
/// </summary>
/// <param name=""></param>
/// <returns>true / false if there are no valid moves / there is at least one valid move</returns>
bool Board::IsNoMove(void) {
	for (int v : MoveSequence) {
		if (IsValidMove(v)) {
			return false; 
		}
	}
	return true;
}

/// <summary>
/// Board::IsValidMove() determines if a specified Move is valid.  A move is valid if it is not being placed in the "overflow" position of a column (i.e., TOP)
/// </summary>
/// <param name="m">Move to determine if valid or not</param>
/// <returns>true if move is valid / false if move is not valid</returns>
bool Board::IsValidMove(Move m) {
	return ((TOP & (ONE << height[m])) == 0);
}

/// <summary>
/// Board::NumberOfPossibleMoves returns the current number of valid moves
/// </summary>
/// <param name=""></param>
/// <returns>Number of Valid Moves in the current board configuration</returns>
unsigned int Board::NumberOfPossibleMoves(void) {
	unsigned int r = 0;
	for (auto const& v : MoveSequence) {
		if (IsValidMove(v)) {
			r++;
		}
	}
	return r;
}

/// <summary>
/// MakeMove() performs a specified move, by adding a player's piece to the next available position in the column.
/// </summary>
/// <param name="m">Move to perform (i.e., column number in which to "drop" the piece)</param>
void Board::MakeMove(Move m) {
	typePlayer p = GetPlayerToMove();

	// update the board
	b[p] = b[p] ^ (ONE << height[m]);

	/* Future Work: Transposition Board -- mirror image of the moves */
	// Make Move on transposition board as well
	//Move t_m = TransposeMove(m);
	//transpose_b[p] = transpose_b[p] ^ (ONE << t_height[t_m]);

	// update the height
	height[m]++;

	/* Future Work: Transposition Board -- mirror image of the moves */
	//t_height[t_m]++;

	// update board to reflect the next player to move
	TogglePlayerToMove();
}

/// <summary>
/// Board::MakeMove() performs a specified move, by adding a player's piece to the next available position in the column.
/// </summary>
/// <param name="m">Move to perform (i.e., column number in which to "drop" the piece)</param>
/// <param name="p">Player making the move</param>
void Board::MakeMove(Move m, typePlayer p) {
	// update the board
	b[p] = b[p] ^ (ONE << height[m]);

	/* Future Work: Transposition Board -- mirror image of the moves */
	// Make Move on transposition board as well
	//Move t_m = TransposeMove(m);
	//transpose_b[p] = transpose_b[p] ^ (ONE << t_height[t_m]);

	// update the height
	height[m]++;

	/* Future Work: Transposition Board -- mirror image of the moves */
	//t_height[t_m]++;

	// update board to reflect the next player to move
	TogglePlayerToMove();
}

/// <summary>
/// Board::TakeBackMove() reverses a move (take back) by removing a player's piece from the top position in a column
/// This function may be need to be modified as I cannot arbitrarily remove a specified player's piece; I have to remove the top-most piece in a column.
/// Where do I use this function?  It appears incorrect as I need to remove from !p instead of from p (take back is for the other play, not the current player to move)
/// </summary>
/// <param name="m">Move to take back (i.e., column number in which to remove the piece</param>
/*
void Board::TakeBackMove(Move m) {
	typePlayer p = GetPlayerToMove();
	// update the height;
	height[m]--;

	// update the board
	b[p] = b[p] ^ (ONE << height[m]);

	// Future Work: Transposition Board -- mirror image of the moves
	//Move t_m = TransposeMove(m);
	//t_height[t_m]--;
	//transpose_b[p] = transpose_b[p] ^ (ONE << t_height[t_m]);

	// update board to reflect the next player to move
	TogglePlayerToMove();
}
*/

/// <summary>
/// Board::TakeBackMove() reverses a move (take back) by removing a player's piece from the top position in a column
/// This function may be need to be modified as I cannot arbitrarily remove a specified player's piece; I have to remove the top-most piece in a column.
/// It just so happens that I always take back the move I just made, so this function works.
/// TODO: For correctness, I would need to verify that player p has the top-most piece in the column before removing the top-most piece.
/// </summary>
/// <param name="m">Move to take back (i.e., column number in which to remove the piece</param>
/// <param name="p">Player's piece to remove</param>
void Board::TakeBackMove(Move m, typePlayer p) {
	// update the height;
	height[m]--;

	// update the board
	b[p] = b[p] ^ (ONE << height[m]);

	/* Future Work: Transposition Board -- mirror image of the moves */
	//Move t_m = TransposeMove(m);
	//t_height[t_m]--;
	//transpose_b[p] = transpose_b[p] ^ (ONE << t_height[t_m]);

	// update board to reflect the next player to move
	TogglePlayerToMove();
}

/// <summary>
/// Board::FindKillerMove() determines if the current player can win with the next move
/// </summary>
/// <param name="p">Player for which to find the Killer Move</param>
/// <returns>Returns the Killer Move, if found; returns 0, if a Killer Move does not exist</returns>
Move Board::FindKillerMove(typePlayer p) {
	for (auto const& v : MoveSequence) {
		if (IsValidMove(v)) {
			MakeMove(v, p);
			if (IsWin(p)) {
				TakeBackMove(v, p);
				return v;
			}
			TakeBackMove(v, p);
		}
	}
	return (Move)0;
}

/// <summary>
/// TransposeMove() is a helper function for the transposition boards (FUTURE WORK)
/// </summary>
/// <param name="m">Move to be transposed</param>
/// <returns></returns>
Move TransposeMove(Move m) {
	Move t_m;
	switch (m) {
	case 1:
		t_m = 7;
		break;
	case 2:
		t_m = 6;
		break;
	case 3:
		t_m = 5;
		break;
	case 4:
		t_m = 4;
		break;
	case 5:
		t_m = 3;
		break;
	case 6:
		t_m = 2;
		break;
	case 7:
		t_m = 1;
		break;
	}
	return t_m;
}

//
// Board-related functions
//

/// <summary>
/// Board::IsWin() determines if a position is won for a specified player.
/// Reference: https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
/// To check if there are four in a row horizontally, we need for example to look at positions 11, 18, 25 and 32 whether they are all set to one.
/// Likewise, we might check positions 21, 28, 35 and 42. The underlying positional pattern is that the positions looked at differ by a constant number of 7.
/// 
/// Take the leftmost position(here 11 and 21, respectively), add 7 and 7 and 7 again, you get the four positions to look at.
/// Vertically, the difference is 1, take position 15 and 16 as an example.Diagonally it's either a difference of 8 (take 16 and 24 as an example) or a difference 
/// of 6 (take 30 and 36).
/// 
/// So, the "magic" difference numbers on the bitboard are 1, 6, 7 and 8.
/// 
/// Let's take a bitboard and shift a copy of it by 6 to the right, another copy by twice as much, and a final copy by thrice as much to the right.
/// Then let's "overlay" all copies with the AND-operator. The effect is that all of the vertically distributed positions of the bitboard making up four in a row 
/// (vertically) are now queried: Is each one of you a one ? If so, we identified four bits in a row.
/// 
/// The point is that bit shiftingand combining bits make it a parallel computation for all positions on the board!
/// You don't look at an individual position, you look at all the positions on the board at once and check for their neighbors being another three bits set as well.
/// </summary>
/// <param name="p">Player to determine if won or not</param>
/// <returns>true if p won the game; false if p did not win the game</returns>
bool Board::IsWin(typePlayer p) {
	int directions[] = { 1, 7, 6, 8 };
	for (int direction : directions)
		if ((b[p] & (b[p] >> direction) & b[p] >> (2 * direction) & b[p] >> (3 * direction)) != 0)
			return true;
	return false;
}

/// <summary>
/// Board::CopyBoard() performs a deep copy of this data structure
/// </summary>
/// <param name="src">Board to copy</param>
void Board::CopyBoard(Board src) {
	// copy boards
	b[0] = src.b[0];
	b[1] = src.b[1];

	for (int i = 1; i < (WIDTH + 1); i++) {
		height[i] = src.height[i];
	}

	// Future Work: Transposition Board -- mirror image of the moves
	// Copy the data structures related to transposition boards

	b_PlayerToMove = src.b_PlayerToMove;
}

/// <summary>
/// Board::PrintBoard () displays the player p's board in two ways: using bitset and in the traditional board configuration (columns and rows).  Used for debugging purposes
/// </summary>
/// <param name="p">Player's board to be displayed</param>
void Board::PrintBoard(typePlayer p) {
	BitBoard copyBoard = b[p];
	unsigned int pos = 0;
	unsigned int col = 0;

	// print using bitset to confirm that PrintBoard is correct

	switch (p) {
	case RED:
		std::cout << "RED";
		break;
	case YELLOW:
		std::cout << "YELLOW";
		break;
	}
	
	std::cout << "'s BOARD: ";
	std::bitset<64> x (copyBoard);
	std::cout << x;
	std::cout << "\n";

	// print sideways
	while (pos < SIZE) {
		if (col == (HEIGHT)) {
			std::cout << "\n";
			col = 0;
			pos++;
		}
		if (pos == SIZE)
			break;
		
		if ((copyBoard & (ONE << pos)) != 0L) {
			std::cout << "1";
		}
		else {
			std::cout << "0";
		}
		pos++;
		col++;
	}
	std::cout << "\n";
	std::cout << "HEIGHTS ";
	for (int i = 1; i <= WIDTH; i++) {
		std::cout << height[i] << " ";
	}
	std::cout << "\n";
}

/// <summary>
/// Board::PrintTransposeBoard() displays the mirror image of player p's board.  Used for debugging purposes.
/// FUTURE WORK
/// </summary>
/// <param name="p"></param>
void Board::PrintTransposeBoard(typePlayer p) {
	//BitBoard copyBoard = transpose_b[p];
	BitBoard copyBoard = b[p];
	unsigned int pos = 0;
	unsigned int col = 0;

	// print using bitset to confirm that PrintBoard is correct

	switch (p) {
	case RED:
		std::cout << "RED";
		break;
	case YELLOW:
		std::cout << "YELLOW";
		break;
	}
	//std::cout << "\n";

	std::cout << "'s BOARD: ";
	std::bitset<64> x(copyBoard);
	std::cout << x;
	std::cout << "\n";

	// print sideways
	while (pos < SIZE) {
		if (col == (HEIGHT)) {
			std::cout << "\n";
			col = 0;
			pos++;
		}
		if (pos == SIZE)
			break;

		if ((copyBoard & (ONE << pos)) != 0L) {
			std::cout << "1";
		}
		else {
			std::cout << "0";
		}
		pos++;
		col++;
	}
	std::cout << "\n";
	std::cout << "HEIGHTS ";
	for (int i = 1; i <= WIDTH; i++) {
		//std::cout << t_height[i] << " ";
	}
	std::cout << "\n";
	//PrintPossibleMoves();
}

// FUTURE WORK: NegaMax
/*
int Board::negamax(int depth, typePlayer playerToMove, int color, MoveHistory* mh) {
	
	typePlayer p = playerToMove;

	// First evaluate from the p's perspective

	// check if current player wins in this position (before I check if depth = 0 or no more moves)
	if (IsWin((typePlayer)(p))) {
		// Current player wins
		//return color * MAX_BESTVAL;
		//return color * MAX_BESTVAL;
		return color * ((MAX_BESTVAL - mh->NumberOfMoves()) / 2);
		//return (color * (WIN - mh.NumberOfMoves()));
	}

	// if terminal node or depth = 0, return DRAW
	if ((depth == 0) || (IsNoMove())) {
		return DRAW;
	}

	Board b;
	Move bestMove = 0;
	int bestScore;

	// Now check what the opponent (!p) can do

	// what can the opponent do now?
	p = (typePlayer)!p;
	color = -color;
	
	// is there a killer move for the opponent?
	b.CopyBoard(*this);
	bestMove = b.FindKillerMove(p);
	if (bestMove != 0) {
		// std::cout << "Killer Move Found: " << bestMove << std::endl;
		bestScore = (MAX_BESTVAL - (mh->NumberOfMoves())) / 2;
		//bestScore = MAX_BESTVAL;
		return color * ((MAX_BESTVAL - mh->NumberOfMoves()) / 2);
		//return bestScore;
	}
	
		//bestScore = -999;
	bestScore = -MAX_BESTVAL; // negative infinity
	//bestScore = -(int)((MAX_BESTVAL - mh.NumberOfMoves()) / 2); //  -std::numeric_limits<float>::min();; 

	// For the opponent
	// Try a move and get the score for the resulting position
	for (int v : MoveSequence) {
		if (IsValidMove(v)) {
			// process the move if it's valid
			numberOfNodes++;
			b.CopyBoard(*this); 
			b.MakeMove(v, p, mh);

			// call for next player, p and color
			bestScore = std::max(bestScore, -b.negamax(depth - 1, (typePlayer)(p), color), mh);

			b.TakeBackMove(v, p, mh);
			
		}
	}
	return bestScore;
}
Move Board::GetBestMoveNegaMax(typePlayer playerToMove, int color) {
	// Get the best move for the player p
	// Give a Board (this), get the base move for the curent player p
	Move bestMove = 0;
	//double bestVal = -(double)((WIDTH * (HEIGHT + 1) - mh.NumberOfMoves())) / 2; //  -std::numeric_limits<float>::min();
	double bestVal = -999;
	Board b;
	 
	typePlayer p = playerToMove;


	// Is there a Killer Move?  Can current player win with the next move?
	b.CopyBoard(*this);
	bestMove = b.FindKillerMove(p);
	if (bestMove != 0) {
#ifdef VERBOSE
		std::cout << "Killer Move Found: " << bestMove << std::endl;
#endif
		// return the best Move, not best Val
		return color * bestMove;
	}
	
	// If a killer move does not exist, make a move, and then make initial call to negamax
	for (auto const& v : MoveSequence) {
		if (IsValidMove(v)) {
			numberOfNodes++;
			b.CopyBoard(*this);
			b.MakeMove(v, p);

			// Find the opponent's response and return appropriate valuation (minimize)
			// float moveVal = b.Minimax(0, false);
			// Initial call for Player's A root node is: negamax (rootNode, depth, 1)
			// Initial call for Player's B root node is: negamax (rootNode, depth, -1)
			// at this point, p == RED has color ==1; and p == YELLOW has color == -1
			double moveVal = 0;
			moveVal = b.negamax(MAX_DEPTH, (typePlayer)(p), color); 

			std::cout << " Best Value = " << bestVal << " Move = " << v << " Value = " << moveVal << "\n";
			//std::cout << " Move = " << v << " Value = " << moveVal << "\n";

			if (moveVal > bestVal) {  // NOT greater than or Equal to force at least one move
				bestMove = v;
				bestVal = moveVal;
			}

			b.TakeBackMove(v, (typePlayer)(p));
		}
	}
	// return the best Move,  not bestVal
	return bestMove;
}
*/

// FUTURE WORK: Using a hash table
/*
int Board::AlphaBetaWithHash(int depth, int alpha, int beta, typePlayer playerToMove, bool isMaximizingPlayer) {
	assert(alpha < beta);
	typePlayer p = playerToMove;
	int color;

	

	if (isMaximizingPlayer) {
		//p = RED;
		color = 1;
	}
	else {
		//p = YELLOW;
		color = -1;
	}

	// Handle Terminal Nodes

	if (IsWin((typePlayer)(p))) {
		// previous player wins
		return color * ((MAX_BESTVAL - mh.NumberOfMoves()) / 2);
		//return color * (WIN - mh.NumberOfMoves());
	}

	// if terminal node or depth = 0, return DRAW
	if ((depth == 0) || (IsNoMove())) {
		return DRAW;
	}

	Board b;
	int bestVal = 0;
	int moveVal = 0;


	// Look Up in the Hash Table
	// upperbound of our score as we cannot win immediately
	bestVal = ((WIDTH * (HEIGHT - 1)) - mh.NumberOfMoves()) / 2;
	if (int val = ht.get(this->b[0], this->b[1]))
		bestVal = val + MIN_SCORE - 1;
	if (beta > bestVal) {
		beta = bestVal;	// no need to keep beta above our max score
		if (alpha >= beta) return beta; // [alpha, beta] window is empty
	}

	if (isMaximizingPlayer) {
		//bestVal = -MAX_BESTVAL;

		for (int v : MoveSequence) {
			if (IsValidMove(v)) {
				// process the move if it's valid
				//int moveVal = 0.0;
				numberOfNodes++;
				b.CopyBoard(*this);
				b.MakeMove(v, p);

				bestVal = std::max(bestVal, b.AlphaBeta(depth - 1, alpha, beta, (typePlayer)(!playerToMove), false));

				b.TakeBackMove(v, p);
				alpha = std::max(alpha, bestVal);
				if (alpha >= beta)
					break;
				if (bestVal > alpha) // reduce the [alpha, beta] window -- only  need to search a position that is better than the best so far
					alpha = bestVal;
			}
		}
		ht.put(b.b[0], b.b[1], bestVal);
		return bestVal;
	}
	else { // Minimizing Player
		//bestVal = MAX_BESTVAL;

		for (int v : MoveSequence) {
			if (IsValidMove(v)) {
				// process the move if it's valid
				//double moveVal = 0;
				numberOfNodes++;
				b.CopyBoard(*this);
				b.MakeMove(v, p);

				bestVal = std::min(bestVal, b.AlphaBeta(depth - 1, alpha, beta, (typePlayer)(!playerToMove), true));

				b.TakeBackMove(v, p);
				beta = std::min(beta, bestVal);
				if (beta <= alpha)
					break;
				if (bestVal > alpha) // reduce the [alpha, beta] window -- only  need to search a position that is better than the best so far
					alpha = bestVal;
			}
		}
		ht.put(b.b[0], b.b[1], bestVal);
		return bestVal;
	}
}
Move Board::GetBestMoveAlphaBetaWithHash(typePlayer playerToMove, bool isMaximizingPlayer) {
	// Get the best move for the player p
		// Give a Board (this), get the base move for the curent player p
	Move bestMove = 0;
	//typeMoveList mlist;

	double bestVal = -MAX_BESTVAL; //  -std::numeric_limits<float>::min();
	int alpha = -MAX_BESTVAL;
	int beta = MAX_BESTVAL; // upperbound

		//std::cout << "Best Val = " << bestVal << std::endl;

	//mlist = GetPossibleMoves();
	Board b;

	typePlayer p = playerToMove;

	// Is there a Killer Move?  Can current player win with the next move?
	b.CopyBoard(*this);
	bestMove = b.FindKillerMove(p);

	if (bestMove != 0) {
#ifdef VERBOSE
		std::cout << "Killer Move Found: " << bestMove << std::endl;
#endif
		bestVal = WIN;
	}
	else {
		for (auto const& v : MoveSequence) {
			if (IsValidMove(v)) {
				numberOfNodes++;
				//bestMove = v;
				b.CopyBoard(*this);
				b.MakeMove(v, p);

				// Find the opponent's response and return appropriate valuation (minimize)
				// float moveVal = b.Minimax(0, false);

				double moveVal = b.AlphaBetaWithHash(MAX_DEPTH, alpha, beta, (typePlayer)(!playerToMove), false);

				//std::cout << " Best Value = " << bestVal << " Move = " << v << " Value = " << moveVal << "\n";
				//std::cout << " Move = " << v << " Value = " << moveVal << "\n";

				if (isMaximizingPlayer) {
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
				b.TakeBackMove(v, (typePlayer)(p));
			}

		}
	}
	return bestMove;
}
*/