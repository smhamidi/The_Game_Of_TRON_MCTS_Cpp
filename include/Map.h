#ifndef MAP_H
#define MAP_H

#include <cmath>
#include <iostream>
#include <vector>

class Map {
 public:
  // Constructor that takes number of rows and columns of the game board, as
  // well as initial positions of the two player heads.
  Map(size_t _row, size_t _col, size_t _xHead1, size_t _yHead1, size_t _xHead2,
      size_t _yHead2);

  // Constructor that takes dimension of the square game board and the initial
  // positions of the two player heads.
  Map(size_t _dim, size_t _xHead1, size_t _yHead1, size_t _xHead2,
      size_t _yHead2);

  // Copy constructor.
  Map(const Map&);

  // Displays the current state of the game board to the console.
  void dispMap() const;

  // Updates the game board according to the input commands of the two players.
  int updateMap(int _ourCommand, int _hisComand);

  // Updates the position of a single head on the game board.
  bool updateCoordinate(size_t _x, size_t _y);

  // Updates the position of both heads on the game board.
  bool updateCoordinate(std::vector<size_t> _head);

  // Checks whether a given command is valid for a given player number.
  bool testCommand(int _command, size_t _playerNumber);

  // Returns the current state of the game board.
  std::vector<std::vector<bool>> get_board() const { return board; }

  // Returns the position of the first player's head.
  std::vector<size_t> get_head1() const { return head1; }

  // Returns the position of the second player's head.
  std::vector<size_t> get_head2() const { return head2; }

  // Returns the state of the game board.
  int get_mapState() const { return mapState; }

  // Updates the position of the first player's head.
  void updateHead1(size_t, size_t);

  // Updates the position of the second player's head.
  void updateHead2(size_t, size_t);

 private:
  // The game board, represented as a 2D vector of bools.
  std::vector<std::vector<bool>> board;

  // The position of the first player's head.
  std::vector<size_t> head1;

  // The position of the second player's head.
  std::vector<size_t> head2;

  // The state of the game board.
  int mapState;
};

#endif
#ifndef MAP_H
