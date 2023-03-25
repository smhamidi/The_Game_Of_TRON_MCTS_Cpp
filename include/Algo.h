#ifndef ALGO_H
#define ALGO_H
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#include "Map.h"
#include "Node.h"

inline Node*& selectionToMove(Node* const& _parent) {
  double maxVi{-1.0};
  Node*& maxChild{_parent->get_childs()[0]};

  for (auto& child : _parent->get_childs()) {
    double vi = static_cast<double>(child->get_wCnt()) / child->get_pCnt();
    if (child->get_pCnt() == 0) {
      vi = std::numeric_limits<double>::infinity();
    }
    if (vi > maxVi) {
      maxVi = vi;
      maxChild = child;
    }
  }

  return maxChild;
}

inline Node*& selection(Node* const& _parent) {
  // DEBUG
  if (!_parent->is_parent()) {
    throw std::logic_error(
        "Algo.h: selection: this NODE has no child to select.");
  }
  if (_parent->get_childs().size() != 3) {
    throw std::logic_error("Algo.h: selection: The number of childs is not 3");
  }
  // END

  double maxVal = _parent->get_childs()[0]->calcValue();
  Node*& maxChild = _parent->get_childs()[0];
  for (auto& child : _parent->get_childs()) {
    double val = child->calcValue();
    if (val > maxVal) {
      maxVal = val;
      maxChild = child;
    }
  }
  return maxChild;
}

inline bool backP(Node*& leaf, bool& result) {
  while (leaf) {
    leaf->increaseP();
    if (result) {
      leaf->increaseW();
    }
    leaf = leaf->get_parent();
  }
  return true;
}

inline bool playOut(Map& virtualMap) {
  std::vector<int> possibleCmd{0, 1, 2, 3};
  auto rd = std::random_device{};
  auto rng = std::default_random_engine{rd()};
  int gameState{-1};
  int command1{0};
  int command2{0};
  while (true) {
    std::shuffle(std::begin(possibleCmd), std::end(possibleCmd), rng);
    // possible choice of player one
    for (const auto& i : possibleCmd) {
      if (virtualMap.testCommand(i, 1)) {
        command1 = i;
        break;
      }
    }

    std::shuffle(std::begin(possibleCmd), std::end(possibleCmd), rng);
    // possible choice of player two
    for (const auto& i : possibleCmd) {
      if (virtualMap.testCommand(i, 2)) {
        command2 = i;
        break;
      }
    }

    gameState = virtualMap.updateMap(command1, command2);

    if (gameState != -1) {
      // game is over
      return (gameState == 1);
    }
  }
}

#endif