// This file is released without license and may be used freely
// Author: Alec Thilenius - alec@thilenius.com

#include "binary_tree.h"

#include <sstream>
#include <vector>
#include <iostream>

#include "printer.h"
#include "suite.h"

namespace thilenius {
namespace external {
namespace csci2270 {
namespace assignments {
namespace binary_tree {
namespace {

BinaryTreeNode* BuildSimpleBinaryTree() {
  // If you see a memory leak coming from here, it means your code was supposed
  // to delete the node, and didn't. You set the pointer to the node to nullptr,
  // but never called "delete" on it.
  return new BinaryTreeNode{
      4, new BinaryTreeNode{2, new BinaryTreeNode{1, nullptr, nullptr},
                            new BinaryTreeNode{3, nullptr, nullptr}},
      new BinaryTreeNode{6, new BinaryTreeNode{5, nullptr, nullptr},
                         new BinaryTreeNode{7, nullptr, nullptr}}};
}

void FreeNodes(BinaryTreeNode* node) {
  if (!node) {
    return;
  }
  FreeNodes(node->left_child);
  FreeNodes(node->right_child);
  delete node;
}

bool IsValidTree(BinaryTreeNode* node, int& size) {
  if (!node) {
    return true;
  }
  size--;
  if (size < 0) {
    return false;
  }
  if (node->left_child && node->left_child->data >= node->data) {
    return false;
  }
  if (node->right_child && node->right_child->data <= node->data) {
    return false;
  }
  return IsValidTree(node->left_child, size) &&
         IsValidTree(node->right_child, size);
}

SUITE(BinaryTreeTestSuite) {
  TEST("Set Head to nullptr", 5, 5) {
    BinaryTree binary_tree;
    binary_tree.head = (BinaryTreeNode*)-1;
    binary_tree = BinaryTree();
    EXPECT_TRUE(binary_tree.head == nullptr,
                "Head should be initialized to nullptr",
                "You didn't set head to nullptr in the constructor");
  }

  TEST("Size", 10, 10) {
    BinaryTree binary_tree;
    binary_tree.head = BuildSimpleBinaryTree();
    int size_given = binary_tree.Size();
    EXPECT_TRUE(size_given == 7,
                "Size should return 7 for: " + binary_tree.ToString(),
                "You didn't count the number of items correct. Got: " +
                    std::to_string(size_given));
    FreeNodes(binary_tree.head);
    binary_tree.head = new BinaryTreeNode{42, nullptr, nullptr};
    size_given = binary_tree.Size();
    EXPECT_TRUE(size_given == 1,
                "Size should return 1 for: " + binary_tree.ToString(),
                "You didn't count the number of items correct. Got: " +
                    std::to_string(size_given));
    FreeNodes(binary_tree.head);
    binary_tree.head = nullptr;
    size_given = binary_tree.Size();
    EXPECT_TRUE(size_given == 0, "Size should return 0 for an empty tree: " +
                                     binary_tree.ToString(),
                "You didn't count the number of items correct. Got: " +
                    std::to_string(size_given));
  }

  TEST("Contains", 10, 10) {
    BinaryTree binary_tree;
    binary_tree.head = BuildSimpleBinaryTree();
    EXPECT_TRUE(binary_tree.Contains(1),
                "Contains(1) should return true for: " + binary_tree.ToString(),
                "It returned false :'( Sad times");
    EXPECT_TRUE(binary_tree.Contains(6),
                "Contains(6) should return true for: " + binary_tree.ToString(),
                "It returned false. Not good");
    EXPECT_TRUE(binary_tree.Contains(4),
                "Contains(4) should return true for: " + binary_tree.ToString(),
                "It returned false :'( Oh the sorrow!");
    EXPECT_TRUE(
        !binary_tree.Contains(0),
        "Contains(0) should return false for: " + binary_tree.ToString(),
        "It returned true. OH THE HUMANITY!");
    FreeNodes(binary_tree.head);
    binary_tree.head = nullptr;
    EXPECT_TRUE(!binary_tree.Contains(69),
                "Contains(69) should return false for an empty tree: " +
                    binary_tree.ToString(),
                "Don't forget to check your nullptr head!");
  }

  TEST("Insert", 35, 35) {
    BinaryTree binary_tree;
    binary_tree.head = nullptr;
    // Insert 4
    int size = 1;
    std::string items = binary_tree.ToString();
    EXPECT_TRUE(binary_tree.Insert(4),
                "Insert(4) should return true for: " + items,
                "It returned false.");
    EXPECT_TRUE(binary_tree.head && IsValidTree(binary_tree.head, size),
                "Should be a valid tree of size 1 after inserting '4'",
                "You built an invalid tree. Why would you do that to me?");
    // Insert 2
    size = 2;
    items = binary_tree.ToString();
    EXPECT_TRUE(binary_tree.Insert(2),
                "Insert(2) should return true for: " + items,
                "It returned false, grasshopper");
    EXPECT_TRUE(
        binary_tree.head && IsValidTree(binary_tree.head, size),
        "Should be a valid tree of size 2 after inserting '2'",
        "You built an invalid tree. Your code needs to get it's life together");
    // Insert 3
    size = 3;
    items = binary_tree.ToString();
    EXPECT_TRUE(binary_tree.Insert(3),
                "Insert(3) should return true for: " + items,
                "It returned false. Like a boss!");
    EXPECT_TRUE(binary_tree.head && IsValidTree(binary_tree.head, size),
                "Should be a valid tree of size 3 after inserting '3'",
                "You built an invalid tree. More coffee maybe?");
    FreeNodes(binary_tree.head);
    binary_tree.head = BuildSimpleBinaryTree();
    // Insert 3 again
    items = binary_tree.ToString();
    EXPECT_TRUE(!binary_tree.Insert(1),
                "Insert(1) should return false for: " + items,
                "It returned true. Unlike a boss");
    FreeNodes(binary_tree.head);
  }

  TEST("Remove", 40, 40) {
    ACTIVE_TEST_CASE.leak_check = true;
    BinaryTree binary_tree;
    // Remove leaf, 1
    binary_tree.head = BuildSimpleBinaryTree();
    std::string items = binary_tree.ToString();
    int size = 6;
    EXPECT_TRUE(binary_tree.Remove(1),
                "Remove(1) should return true for: " + items,
                "It gave me false! I hate when that happens.");
    EXPECT_TRUE(binary_tree.head && IsValidTree(binary_tree.head, size),
                "Should be a valid tree of size 6 after removing '1'",
                "You built an invalid tree. Life's hard.");
    FreeNodes(binary_tree.head);
    // Remove leaf, 1 and 3
    binary_tree.head = BuildSimpleBinaryTree();
    items = binary_tree.ToString();
    size = 5;
    EXPECT_TRUE(binary_tree.Remove(1) && binary_tree.Remove(3),
                "Remove(1) and Remove(3) should return true for: " + items,
                "-sigh- False it be then");
    EXPECT_TRUE(
        binary_tree.head && IsValidTree(binary_tree.head, size),
        "Should be a valid tree of size 5 after removing '1' and '3'",
        "You built an invalid tree. Or maybe it's a bug in the compiler! :p");
    FreeNodes(binary_tree.head);
    // Remove parent, 2
    binary_tree.head = BuildSimpleBinaryTree();
    items = binary_tree.ToString();
    size = 6;
    EXPECT_TRUE(binary_tree.Remove(2),
                "Remove(2) should return true for: " + items,
                "False! Waaaa...");
    EXPECT_TRUE(binary_tree.head && IsValidTree(binary_tree.head, size),
                "Should be a valid tree of size 6 after removing '2'",
                "The '2' node is a parent node, it will be tricky to remove!");
    FreeNodes(binary_tree.head);
    // Remove root node, 4
    binary_tree.head = BuildSimpleBinaryTree();
    items = binary_tree.ToString();
    size = 6;
    EXPECT_TRUE(binary_tree.Remove(4),
                "Remove(4) should return true for: " + items, ":,(");
    EXPECT_TRUE(
        binary_tree.head && IsValidTree(binary_tree.head, size),
        "Should be a valid tree of size 6 after removing '4'",
        "The '4' node is the root node, it will also be tricky to remove!");
    FreeNodes(binary_tree.head);
    // Remove parent, 420
    binary_tree.head = BuildSimpleBinaryTree();
    items = binary_tree.ToString();
    EXPECT_TRUE(!binary_tree.Remove(420),
                "Remove(420) should return false for: " + items,
                "Noooope. Maybe a little too much 420 today...?");
    FreeNodes(binary_tree.head);
  }

  TEST("Clear - Extra Credit [5]", 5, 0) {
    ACTIVE_TEST_CASE.leak_check = true;
    BinaryTree binary_tree;
    binary_tree.head = BuildSimpleBinaryTree();
    binary_tree.Clear();
    EXPECT_TRUE(binary_tree.head == nullptr,
                "Head should be nullptr after Clear()",
                "It's not nullptr, let's just say.");
    FreeNodes(binary_tree.head);
  }
}

}  // namespace
}  // namespace binary_tree
}  // namespace assignments
}  // namespace csci2270
}  // namespace external
}  // namespace thilenius

int main(int argc, char* argv[]) {
  ::thilenius::external::vanguard::Suite suite(
      "Binary Search Tree", ::thilenius::external::csci2270::assignments::
                                binary_tree::BinaryTreeTestSuite);
  suite.RunAllTestCasesProtected();
  ::thilenius::external::vanguard::Printer printer;
  printer.WriteStdCout(suite, &std::cout);
  printer.WriteSuiteResults(suite, &std::cout);
  printer.WriteSuiteReportCard(suite, &std::cout);
}