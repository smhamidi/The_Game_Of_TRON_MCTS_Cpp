#include "Game.h"

#include <chrono>
#include <cmath>

Game::Game(size_t row, size_t col, size_t xHead1, size_t yHead1, size_t xHead2,
           size_t yHead2, size_t _deaignedDepth)
    : gameMap{row, col, xHead1, yHead1, xHead2, yHead2},
      node1{new Node{}},
      node2{new Node{}},
      designedDepth{_deaignedDepth} {
  while (node1->get_depth() < designedDepth) {
    node1->expansion();
    node2->expansion();
  }
}

bool Game::updateGame(size_t xHead1, size_t yHead1, size_t xHead2,
                      size_t yHead2) {
  bool smthWRONG{(gameMap.updateCoordinate(xHead1, yHead1)) &&
                 (gameMap.updateCoordinate(xHead2, yHead2))};
  if (!smthWRONG) {
    gameMap.dispMap();
    return smthWRONG;
  }

  int player1CMD =
      calcCMD(gameMap.get_head1()[0], gameMap.get_head1()[1], xHead1, yHead1);
  int player2CMD =
      calcCMD(gameMap.get_head2()[0], gameMap.get_head2()[1], xHead2, yHead2);

  for (const auto& i : node1->get_childs()) {
    if (player1CMD == i->get_globalDir()) {
      node1 = i;
      node1->set_parent(nullptr);
      break;
    }
  }

  for (const auto& i : node2->get_childs()) {
    if (player2CMD == i->get_globalDir()) {
      node2 = i;
      node2->set_parent(nullptr);
      break;
    }
  }

  while (node1->get_depth() < designedDepth) {
    node1->expansion();
    node2->expansion();
  }

  gameMap.updateHead1(xHead1, yHead1);
  gameMap.updateHead2(xHead2, yHead2);

  return smthWRONG;
}

int Game::calcCMD(size_t x_pre, size_t y_pre, size_t _x, size_t _y) {
  int deltaY = _y - y_pre;
  int deltaX = _x - x_pre;

  if ((deltaX == 0 && deltaY == 0) || (abs(deltaX) == 1 && abs(deltaY) == 1) ||
      (abs(deltaX) > 1) || (abs(deltaY) > 1)) {
    std::logic_error("Game.cpp : calcCMD: it is not possible");
  }

  if (deltaX == 0) {
    if (deltaY == 1) {
      return 0;  // Down
    } else {
      return 2;  // Up
    }
  } else {
    if (deltaX == 1) {
      return 3;  // Right
    } else {
      return 1;  // Left
    }
  }
}

void Game::monteCarlo(
    std::chrono::time_point<std::chrono::system_clock> time) const {
  while (node1->get_depth() < designedDepth) {
    node1->expansion();
  }
  while (node2->get_depth() < designedDepth) {
    node2->expansion();
  }

  size_t counter{0};
  while ((static_cast<double>((static_cast<std::chrono::duration<double>>(
                                   std::chrono::system_clock::now() - time)
                                   .count()) *
                              1000)) < 995) {
    Node* leafNode1{node1};
    Node* leafNode2{node2};
    int gameState{-1};
    Map virtualMap{gameMap};
    while (!leafNode1->get_isLeaf()) {
      leafNode1 = selection(leafNode1);
      leafNode2 = selection(leafNode2);
      gameState = virtualMap.updateMap(leafNode1->get_globalDir(),
                                       leafNode2->get_globalDir());
      if (gameState == -1) {
        continue;
      } else if (gameState == 1) {
        backP(leafNode1, true);
        backP(leafNode2, false);
        break;
      } else if (gameState == 2 || gameState == 0) {
        backP(leafNode1, false);
        backP(leafNode2, true);
        break;
      }
    }
    // DEBUG
    if (leafNode1->get_isLeaf() != leafNode2->get_isLeaf()) {
      std::logic_error(
          "Game.cpp: playGame: opponent node has not reached leaf");
    }
    // END
    if (gameState == -1) {
      bool won1{playOut(virtualMap)};
      if (won1) {
        backP(leafNode1, true);
        backP(leafNode2, false);
      } else {
        backP(leafNode1, false);
        backP(leafNode2, true);
      }
    }
    counter++;
  }
  std::cout << "### Number of Iterations: " << counter << std::endl;
}