// This file is released without license and may be used freely
// Author: Alec Thilenius - alec@thilenius.com

#ifndef EXTERNAL_CSCI2270_ASSIGNMENTS_03_BINARY_TREE_H_
#define EXTERNAL_CSCI2270_ASSIGNMENTS_03_BINARY_TREE_H_

#include <string>

#include "suite.h"

namespace thilenius {
namespace external {
namespace csci2270 {
namespace assignments {
namespace binary_tree {

struct BinaryTreeNode {
  int data;
  BinaryTreeNode* left_child;
  BinaryTreeNode* right_child;
};

class BinaryTree {
 public:
  BinaryTree();
  int Size();
  bool Contains(int value);
  bool Insert(int value);
  bool Remove(int value);
  void Clear();

  std::string ToString();

  BinaryTreeNode* head;
};


}  // namespace binary_tree
}  // namespace assignments
}  // namespace csci2270
}  // namespace external
}  // namespace thilenius

#endif  // EXTERNAL_CSCI2270_ASSIGNMENTS_03_BINARY_TREE_H_