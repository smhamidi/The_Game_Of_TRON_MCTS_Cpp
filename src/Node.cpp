#include "Node.h"

Node::Node()
    : wCnt{0},
      pCnt{0},
      depth{0},
      parent{nullptr},
      childs({nullptr, nullptr, nullptr}),
      isLeaf{true},
      globalDir{2} {}

Node::Node(Node* _parent, int _globalDir)
    : wCnt{0},
      pCnt{0},
      depth{0},
      parent{_parent},
      childs({nullptr, nullptr, nullptr}),
      isLeaf{true},
      globalDir{_globalDir} {}

std::vector<Node*> Node::getAllNodes() {
  // Returning vector containing all nodes.
  std::vector<Node*> nodesToReturn;

  // Create a vector to keep track of nodes that need to be Added, and push
  // the current node onto the stack.
  std::vector<Node*> nodeStack;
  nodeStack.push_back(this);

  // Continue processing nodes until the stack is empty.
  while (!nodeStack.empty()) {
    // Pop the top node from the stack and assign it to a variable.
    Node* current = nodeStack.back();
    nodeStack.pop_back();

    // Iterate over the current node's child nodes and push them onto the stack
    // for later iterations.
    for (Node*& child : current->get_childs()) {
      if (child != nullptr) {
        nodeStack.push_back(child);
      }
    }

    // Add the current node.
    nodesToReturn.push_back(current);
  }
  return nodesToReturn;
}

void Node::assignChilds() {
  // DEBUG
  if ((this->childs[0] != nullptr) || (this->childs[1] != nullptr) ||
      (this->childs[2] != nullptr)) {
    throw std::logic_error(
        "Node.cpp: assginChilds: assigning to Non leaf Node");
  }
  if (this->get_depth() != 0) {
    throw std::logic_error("Node.cpp: assignChilds: depths is not 0");
  }
  // END

  this->childs[0] = new Node(this, globalDir + 1 == 4 ? 0 : globalDir + 1);
  this->childs[1] = new Node(this, globalDir);
  this->childs[2] = new Node(this, globalDir - 1 == -1 ? 3 : globalDir - 1);
}

bool Node::expansion() {
  // Loop through all nodes and select the ones with depths of 0 to assign
  // child
  std::vector<Node*> allNodes = this->getAllNodes();
  for (Node*& node : allNodes) {
    if (node->get_depth() == 0) {
      node->assignChilds();
      node->set_isLeaf(false);
      node->increaseDepth();
    } else {
      node->set_isLeaf(false);
      node->increaseDepth();
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
  // END

  if (pCnt == 0) {
    return std::numeric_limits<double>::infinity();
  }

  double EXPLORE_RATE = 10;
  return (((static_cast<double>(wCnt) / static_cast<double>(pCnt)) +
           EXPLORE_RATE * std::sqrt((std::log(parent->get_pCnt()) /
                                     static_cast<double>(pCnt)))));
}

// Node::~Node() {
//   // Destructor for Node class
//   auto nodes = this->getAllNodes();
//   for (Node*& node : nodes) {
//     if (node != nullptr) {
//       delete node;
//       node = nullptr;
//     }
//   }
// }
