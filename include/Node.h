#ifndef NODE_H  // Header guard: prevent multiple inclusions of this file in the
                // same translation unit
#define NODE_H

#include <array>
#include <cmath>
#include <iostream>
#include <iostream>  // Include the standard library header for input/output streams
#include <limits>
#include <stack>
#include <vector>

class Node {  // Define the Node class
 public:
  // Declare the default constructor for creating a node as a root
  Node();

  // Declare a memeber function that returns all the node in the graph.
  std::vector<Node*> getAllNodes();

  // Delcare the destructor of the class
  // ~Node();

  // Declare a member function that creates 3 child nodes with acceptable
  // directions for leaf nodes
  bool expansion();

  // Declare a member function that calculates the value for each node using
  // Monte Carlo simulation
  double calcValue() const;

  // Declare a member function that increments the number of times this node
  // wins
  void increaseW() { wCnt++; }

  // Declare a member function that increments the number of times this node is
  // visited
  void increaseP() { pCnt++; }

  // Declare a member function that marks this node as visited
  void updateVisited() { visited = true; }

  // Declare a member function that increments the depth of this node
  void increaseDepth() { depth++; }

  // Declare a member function that assigns child nodes to this node
  void assignChilds();

  // Declare a member function that sets the isLeaf flag to indicate whether
  // this node is a leaf node or not
  void set_isLeaf(bool _isLeaf) { isLeaf = _isLeaf; }

  // Declare a member function that sets the parent node of this node
  void set_parent(Node* _parent) { parent = _parent; }

  // Declare a member function that returns a reference to the array of child
  // nodes
  std::array<Node*, 3>& get_childs() { return childs; }

  // Declare a member function that returns a reference to the parent node
  Node*& get_parent() { return parent; }

  // Declare a member function that returns the depth of this node
  size_t get_depth() const { return depth; }

  // Declare a member function that returns true if this node has been visited
  bool get_visited() const { return visited; }

  // Declare a member function that returns the number of times this node has
  // won
  size_t get_wCnt() const { return wCnt; }

  // Declare a member function that returns the number of times this node has
  // been visited
  size_t get_pCnt() const { return pCnt; }

  // Declare a member function that returns the global direction of this node
  int get_globalDir() const { return globalDir; }

  // Declare a member function that returns true if this node is a leaf node
  bool get_isLeaf() const { return isLeaf; }

  // Declare a member function that returns true if this node is not a leaf node
  bool is_parent() const { return !isLeaf; }

 private:
  // Declare a constructor that creates a node with a parent and a direction
  Node(Node* _parent, int _globalDir);

  size_t wCnt;  // The number of times this node has won
  size_t pCnt;  // The number of times this node has been visited

  bool isLeaf;   // Flag to indicate whether this node is a leaf node or not
  bool visited;  // Flag to indicate whether this node has been visited or not

  std::array<Node*, 3> childs;  // The array of child nodes
  Node* parent;                 // Pointer to the parent node

  size_t depth;   // The depth of this node
  int globalDir;  // The global direction of this node
};

#endif  // End of the header guard.