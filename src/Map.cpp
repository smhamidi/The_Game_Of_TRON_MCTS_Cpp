#include "Map.h"

// Constructor that takes row, column, and head positions for both players
Map::Map(size_t row, size_t col, size_t xHead1, size_t yHead1, size_t xHead2,
         size_t yHead2)
    : head1{xHead1, yHead1}, head2{xHead2, yHead2}, mapState{-1} {
  // DEBUG
  // Check if heads are within map boundaries
  if (!(xHead1 > 0 && xHead1 < col - 1 && yHead1 > 0 && yHead1 < row - 1 &&
        xHead2 > 0 && xHead2 < col - 1 && yHead2 > 0 && yHead2 < row - 1)) {
    throw std::logic_error("map.cpp: constructor: heads are out of map!");
  }
  // END

  // Create a vector of vectors to represent the board, initially all set to
  // true
  std::vector<std::vector<bool>> tmpBoard(row, std::vector<bool>(col, true));
  board = std::move(tmpBoard);

  // Create the walls around the edge of the board
  for (size_t rowIdx = 0; rowIdx < row; ++rowIdx) {
    for (size_t colIdx = 0; colIdx < col; ++colIdx) {
      if (rowIdx == 0 || rowIdx == row - 1 || colIdx == 0 ||
          colIdx == col - 1) {
        board[rowIdx][colIdx] = false;
      }
    }
  }
  // Finished creating walls

  // Put the heads of both players on the map
  board[yHead1][xHead1] = false;
  board[yHead2][xHead2] = false;
}

// Constructor that takes a single dimension and head positions for both players
Map::Map(size_t dim, size_t xHead1, size_t yHead1, size_t xHead2, size_t yHead2)
    : Map(dim, dim, xHead1, yHead1, xHead2, yHead2) {}

// Copy constructor
Map::Map(const Map& _map) {
  board = _map.get_board();
  head1 = _map.get_head1();
  head2 = _map.get_head2();
  mapState = _map.get_mapState();
}

/*
the following function get the commands and update the heads and board.
it will return the state of the game
1: player one has won
2: player two has won
0: DRAW
-1: everything Normal
*/
int Map::updateMap(int player1CMD, int player2CMD) {
  // DEBUG
  if (((player1CMD > 3) || (player1CMD < 0)) ||
      ((player2CMD > 3) || (player2CMD < 0))) {
    throw std::logic_error("map.cpp: updateMap: Incorrect command");
  }
  // END
  updateHead1(head1[0] + (player1CMD - 2) % 2, head1[1] - (player1CMD - 1) % 2);
  updateHead2(head2[0] + (player2CMD - 2) % 2, head2[1] - (player2CMD - 1) % 2);

  if (head1 == head2) {
    mapState = 0;
    return 0;  // DRAW
  }

  else if (!updateCoordinate(head1)) {
    mapState = 2;
    return 2;  // Player 2 won

  } else if (!updateCoordinate(head2)) {
    mapState = 1;
    return 1;  // Player 1 won
  }
  return -1;  // Nothing has happened
}

// it will update the coordinate on the map and will return either false if
// we hit an obstacle, or true if everything is OK!
bool Map::updateCoordinate(size_t _x, size_t _y) {
  // DEBUG
  if (mapState != -1) {
    throw std::logic_error(
        "map.cpp: updateCoordinate: game has FINISHED already!");
  }
  // END
  if (board[_y][_x] == false) {
    return false;
  }
  board[_y][_x] = false;
  return true;
}
bool Map::updateCoordinate(std::vector<size_t> head) {
  return Map::updateCoordinate(head[0], head[1]);
}

bool Map::testCommand(int cmd, size_t playerNum) {
  // DEBUG
  if (((cmd > 3) || (cmd < 0))) {
    throw std::logic_error("map.cpp: testCommand: Incorrect command");
  }
  if (playerNum != 1 && playerNum != 2) {
    throw std::logic_error("map.cpp: testCommand: player do not exist");
  }
  if (mapState != -1) {
    throw std::logic_error("map.cpp: testCommand: game has FINISHED already!");
  }
  // END
  return playerNum == 1
             ? board[head1[1] - ((cmd - 1) % 2)][head1[0] + ((cmd - 2) % 2)]
             : board[head2[1] - ((cmd - 1) % 2)][head2[0] + ((cmd - 2) % 2)];
}

void Map::updateHead1(size_t xHead1, size_t yHead1) {
  // DEBUG
  if (std::abs(static_cast<int>(xHead1 - head1[0])) +
          std::abs(static_cast<int>(yHead1 - head1[1])) !=
      1) {
    throw std::logic_error("map.cpp: updateHead1: Incorrect placement");
  }
  if (mapState != -1) {
    throw std::logic_error("map.cpp: updateHead1: game has FINISHED already!");
  }
  // END

  head1[0] = xHead1;
  head1[1] = yHead1;
}

void Map::updateHead2(size_t xHead2, size_t yHead2) {
  // DEBUG
  if (std::abs(static_cast<int>(xHead2 - head2[0])) +
          std::abs(static_cast<int>(yHead2 - head2[1])) !=
      1) {
    throw std::logic_error("map.cpp: updateHead2: Incorrect placement");
  }
  if (mapState != -1) {
    throw std::logic_error("map.cpp: updateHead2: game has FINISHED already!");
  }

  // END
  head2[0] = xHead2;
  head2[1] = yHead2;
}

void Map::dispMap() const {
  for (size_t rows{0}; rows < board.size(); rows++) {
    for (size_t cols{0}; cols < board[rows].size(); cols++) {
      std::cout << ((((head1[0] == cols) && (head1[1] == rows)) ||
                     ((head2[0] == cols) && (head2[1] == rows)))
                        ? "#"
                        : (board[rows][cols] ? "-" : "*"));
    }
    std::cout << std::endl;
  }
}