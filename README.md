# ConnectFour
Connect Four (also known as Four Up, Plot Four, Find Four, Four in a Row, Four in a Line, Drop Four, and Gravitrips in the Soviet Union) is a two-player connection board game, in which the players choose a color and then take turns dropping colored discs into a seven-column, six-row vertically suspended grid. The pieces fall straight down, occupying the lowest available space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs. 
This repository implements several Solvers, each solver using a different algorithm to determine its best move:
  RandomPlay_Solver: selects its move randomly
  MinimaxPlay_Solver: selects its move using the Minimax algorithm
  MinimaxPlayAB_Solver: selects its move using the Minimax algorithm with Alpha-Beta pruning
MyConnectFour.cpp contains the main() function and shows how the solvers can be called.  MatchPlay() allows two solvers to compete against each other.
