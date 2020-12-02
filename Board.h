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
#include <list>
#include<vector>

#define HEIGHT 6
#define WIDTH 7
#define SIZE (HEIGHT * (WIDTH+1))
#define ONE 1ULL
#define TOP ((0b0000001000000100000010000001000000100000010000001ULL) << HEIGHT)

typedef unsigned int Move;	// A move is the column in which the piece is to be dropped (possible valid moves are defined in MoveSequence[])
typedef std::list <Move> typeMoveList;

/* 

The bitboard b is arranged as:
5 12 19 26 33 40 47
4 11 18 25 32 39 46
3 10 17 24 31 38 45
2  9 15 23 30 37 44
1  8 15 22 29 38 43
0  7 14 21 28 35 42

As 48 bits are needed to represent the board, we use an unsigned long long int since it is represented using 64-bits.

*/

typedef unsigned long long BitBoard;

enum typePlayer { RED = 0, YELLOW = 1 };	// The two different players are designated as RED or YELLOW

class Board
{
private:
	BitBoard b[2]; // one board for each player
	typePlayer b_PlayerToMove; // playerToMove in this position
	unsigned short int height[WIDTH + 1]; // height is an array of the first available position in the column i; for convenience, height[0] is not used; and height[1] thru height [7] is used.

	/* Future Work: Transposition Board */ 
	// BitBoard transpose_b[2];
	//unsigned short int t_height[WIDTH + 1]; // transposition height
	
public:
	//static const int MIN_SCORE = -(WIDTH * HEIGHT) / 2 + 3;
	//static const int MAX_SCORE = -(WIDTH * HEIGHT + 1) / 2 - 3;

	Move MoveSequence[7] = { 4, 3, 5, 2, 6, 1, 7 }; // optimized Move Sequence, start from the middle of the board and move outward

	// Constructors and Initializers
	Board(typePlayer player = RED);
	void InitBoard(typePlayer player = RED);

	// Access functions to Private member 
	BitBoard GetBoard(typePlayer p); 
	typePlayer GetPlayerToMove(void);
	void SetPlayerToMove(typePlayer p);
	void TogglePlayerToMove(void);
	
	// Move-related functions
	bool IsNoMove(void);
	bool IsValidMove(Move m);
	unsigned int NumberOfPossibleMoves(void);
	void MakeMove(Move m);
	void MakeMove(Move m, typePlayer p);
	//void TakeBackMove(Move m);
	void TakeBackMove(Move m, typePlayer p);
	Move FindKillerMove(typePlayer p);

	// Board-related functions
	bool IsWin(typePlayer p);
	void CopyBoard(Board b);
	void PrintBoard(typePlayer p);
	void PrintTransposeBoard(typePlayer p);
	

	//Move GetRandomMove(typePlayer playerToMove, bool isMaximizingPlayer);
	
	/*
	int Minimax(int depth, typePlayer playerToMove, bool isMaximizingPlayer);
	Move GetBestMoveMinimax(typePlayer playerToMove, bool isMaximizingPlayer);

	int negamax(int depth, typePlayer playerToMove, int color);
	Move GetBestMoveNegaMax(typePlayer playerToMove, int color);
	
	int AlphaBeta(int depth, int  alpha, int beta, typePlayer playerToMove, bool isMaximizingPlayer);
	Move GetBestMoveAlphaBeta(typePlayer playerToMove, bool isMaximizingPlayer);
	BitBoard GetBoard(typePlayer p);

	int AlphaBetaWithHash(int depth, int alpha, int beta, typePlayer playerToMove, bool isMaximizingPlayer);
	Move GetBestMoveAlphaBetaWithHash(typePlayer playerToMove, bool isMaximizingPlayer);

	*/
};

