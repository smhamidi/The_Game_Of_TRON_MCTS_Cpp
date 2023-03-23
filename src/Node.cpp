#include "Node.h"

#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

Node::Node()
    : wCnt{0},
      pCnt{0},
      depth{0},
      parent{nullptr},
      childs({nullptr, nullptr, nullptr}),
      isLeaf{true},
      visited{false},
      globalDir{2} {}

Node::Node(Node* _parent, int _globalDir)
    : wCnt{0},
      pCnt{0},
      depth{0},
      parent{_parent},
      childs({nullptr, nullptr, nullptr}),
      isLeaf{true},
      visited{false},
      globalDir{_globalDir} {}

Node::~Node() {  // Destructor for Node class

  // Create a stack to keep track of nodes that need to be deleted, and push
  // the current node onto the stack.
  std::vector<Node*> nodeStack;
  nodeStack.push_back(this);

  // Continue processing nodes until the stack is empty.
  while (!nodeStack.empty()) {
    // Pop the top node from the stack and assign it to a variable.
    Node* current = nodeStack.back();
    nodeStack.pop_back();

    // Iterate over the current node's child nodes and push them onto the stack
    // for later deletion.
    for (Node*& child : current->childs) {
      if (child) {
        nodeStack.push_back(child);
      }
    }

    // Delete the current node.
    delete current;
  }
}

void Node::assignChilds() {
  // DEBUG
  if ((this->childs[0] != nullptr) || (this->childs[1] != nullptr) ||
      (this->childs[2] != nullptr)) {
    throw std::logic_error(
        "Node.cpp: assginChilds: assigning to Non leaf Node");
  }
  // END

  this->childs[0] = new Node(this, globalDir + 1 == 4 ? 0 : globalDir + 1);
  this->childs[1] = new Node(this, globalDir);
  this->childs[2] = new Node(this, globalDir - 1 == -1 ? 3 : globalDir - 1);
}

bool Node::expansion() {
  this->depth++;  // Increment the depth of the current node.

  // Create a stack to keep track of nodes that need to be expanded, and push
  // the current node onto the stack.
  std::vector<Node*> nodeStack;
  nodeStack.push_back(this);

  // Continue processing nodes until the stack is empty.
  while (!nodeStack.empty()) {
    // Pop the top node from the stack and assign it to a variable.
    Node* current = nodeStack.back();
    nodeStack.pop_back();

    // Check if the current node is a leaf node and the root node.
    if (current->isLeaf && !current->parent) {
      // If so, expand the node by generating its child nodes.
      current->isLeaf = false;
      current->assignChilds();
    } else {
      // If the current node is not a leaf node or the root node, iterate over
      // its child nodes.
      for (auto& i : current->childs) {
        if (i->get_isLeaf()) {
          // If the child node is a leaf node with a parent, expand it by
          // generating its child nodes.
          i->increaseDepth();
          i->set_isLeaf(false);
          i->assignChilds();
        } else {
          // If the child node is not a leaf node, push it onto the stack for
          // later expansion.
          nodeStack.push_back(i);
        }
      }
    }
  }

  // Return true to indicate successful expansion.
  return true;
}

double Node::calcValue() const {
  // DEBUG
  if (this->parent == nullptr) {
    throw std::logic_error(
        "Node.cpp: calcValue: there is no parent to look for");
  }
  if (pCnt == 0 || parent->get_pCnt() == 0) {
    throw std::logic_error("Node.cpp: calcValue: playCount is 0");
  }
  // END
  double EXPLORE_RATE = 10;
  return (((static_cast<double>(wCnt) / static_cast<double>(pCnt)) +
           EXPLORE_RATE * std::sqrt((std::log(parent->get_pCnt()) /
                                     static_cast<double>(pCnt)))));
}