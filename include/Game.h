// ifndef and define statements ensure that the header file is only included
// once
#ifndef GAME_H
#define GAME_H

// include necessary libraries
#include <chrono>  // for timing
#include <cmath>   // for math functions

// include the header file for the MCTS needed algorithms
#include "Algo.h"

// define the Game class
class Game {
 public:
  // constructor takes in various parameters to set up the game
  Game(size_t row, size_t col, size_t xHead1, size_t yHead1, size_t xHead2,
       size_t yHead2, size_t _designDepth);

  // function to update the game state based on the players' head positions
  bool updateGame(size_t xHead1, size_t yHead1, size_t xHead2, size_t yHead2);

  // function to calculate the command to be executed based on the previous
  // position and the current position
  int calcCMD(size_t x_pre, size_t y_pre, size_t _x, size_t _y);

  // function to perform Monte Carlo simulation to evaluate the best move for
  // the player
  void monteCarlo(
      std::chrono::time_point<std::chrono::system_clock> time) const;

  // getter functions to retrieve the nodes representing the players and the
  // current game map
  Node* get_node1() { return node1; }
  Node* get_node2() { return node2; }
  Map get_gameMap() { return gameMap; }

 private:
  // member variable to store the game map
  Map gameMap;

  // member variables to store the nodes representing the players
  Node* node1;
  Node* node2;

  // member variable to store the design depth parameter
  size_t designedDepth;
};

// end of the header file
#endif
