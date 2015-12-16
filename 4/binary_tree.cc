// This file is released without license and may be used freely
// Author: Alec Thilenius - alec@thilenius.com

#include "binary_tree.h"

#include <iostream>

namespace thilenius {
namespace external {
namespace csci2270 {
namespace assignments {
namespace binary_tree {

//  ______     __     __   __     ______     ______     __  __
// /\  == \   /\ \   /\ "-.\ \   /\  __ \   /\  == \   /\ \_\ \
// \ \  __<   \ \ \  \ \ \-.  \  \ \  __ \  \ \  __<   \ \____ \
//  \ \_____\  \ \_\  \ \_\\"\_\  \ \_\ \_\  \ \_\ \_\  \/\_____\
//   \/_____/   \/_/   \/_/ \/_/   \/_/\/_/   \/_/ /_/   \/_____/
//                          ______   ______     ______     ______     ______
//                         /\__  _\ /\  == \   /\  ___\   /\  ___\   /\  ___\
//                         \/_/\ \/ \ \  __<   \ \  __\   \ \  __\   \ \___  \
//                            \ \_\  \ \_\ \_\  \ \_____\  \ \_____\  \/\_____\
//                             \/_/   \/_/ /_/   \/_____/   \/_____/   \/_____/

// Welcome to assignment three, Binary Trees! Let me tell you, this thing is a
// pain in the... ummm... head. This assignment is technically a
// "Binary Search Tree", meaning that it follows the rules:
//   - Each node has at most 2 children (Hence the binary part)
//   - The "left" child and grandchildren are ALWAYS less than the parent
//   - The "right" child and grandchildren are ALWAYS greater than the parent
// In this version of the binary tree, I do not allow duplicate values, to make
// life ever so less painful for you guys.
//
// Just like the LinkedList assignment, the only file you should edit is this
// one. Just like the LinkedList assignment, you'll need to look in the header
// file (binary_tree.h) to see how the class and the "BinaryTreeNode" is set up.
// It might also be helpful to look at the test file (binary_tree_test.cc) to
// see what it's looking for.
//
// Unlike the LinkedList assignment, this one is a %#$&, or at least more so
// than the LinkedList assignment. Also unlike the LinkedList assignment, you
// might want to use a good amount of recursion to solve it. For that, you will
// need helper functions (see below). You are free to use the helpers already
// there, not use them, make your own, put angry comments in them yelling at
// your computer, what ever your heart desires. The helpers are there to help,
// or not help, or be deleted or changed. I often leave my computer angry
// comments. It doesn't help, but nor does the copious amounts of coffee I
// insist on drinking.
//
// A really (REALLY) good place to start on this assignment is by reading Gabe's
// writeup from when he taught CSCI2270. Keep in mind his assignment allowed
// duplicates, ours does not.
// https://github.com/johnsogg/cs2270/blob/master/homeworks/hw-2-binary-search-trees/BinarySearchTrees.pdf
//
// There is also his lecture slides on binary search trees, also brilliant:
// https://github.com/johnsogg/cs2270/tree/master/lecture_slides

//==============================================================================
//==  HELPERS  =================================================================
//==============================================================================
// Take a look at the section "Methods" before looking over this
//
// This section (the un-named namespace, also called an anonymous namespace) is
// where you 'should' put helpers used by your code. This is a good place to put
// recursive functions that are then called by your member functions (why they
// are called helpers).
//
// I left in all the helper stubs of the ones I used in the solution. You don't
// have to use them, you can change them, or do what ever you like to them.
namespace {

// I used this helper to compute the size of a tree recursively, given the head
// node in the tree.
int SizeRecursive(const BinaryTreeNode* tree_node) {
  int rv = 0;
  if (tree_node) {
    rv = 1;
    if (tree_node->left_child) rv += SizeRecursive(tree_node->left_child);
    if (tree_node->right_child) rv += SizeRecursive(tree_node->right_child);
  }
  return rv;
}

// I used this helper to check if a tree contained the value "value" given the
// head node in the tree.
bool ContainsRecursive(const BinaryTreeNode* tree_node, int value) {
  
  if(tree_node) {
    if(tree_node->data == value) return true;
    if(tree_node->left_child) 
      if(ContainsRecursive(tree_node->left_child, value)) return true;
    if(tree_node->right_child) 
      if(ContainsRecursive(tree_node->right_child, value)) return true;
  }

  return false;
}

BinaryTreeNode * initNode(int value) {
  BinaryTreeNode * tmp = new BinaryTreeNode;
  tmp->data = value;
  tmp->left_child = nullptr;
  tmp->right_child = nullptr;
  return tmp;
}

// I used this helper to insert a value into a tree in any position except as
// the first item. I had a if (head == nullptr) case in my method for that case.
// This helper then would recursively find where the node needed to go, then
// inset it there. Keep in mind that because we aren't self-balancing these
// trees, you only inset into a 'leaf' node, that is, a node with no children.
// Because balancing a binary tree is a LOT of work, you can just leave it
// unbalanced, as long as it's a valid binary search tree.
bool InsertRecursive(BinaryTreeNode* tree_node, int value) {
  if(value < tree_node->data) {
    if(!tree_node->left_child) {
      BinaryTreeNode * tmp = initNode(value);
      tree_node->left_child = tmp;
      return true;
    }
    return InsertRecursive(tree_node->left_child, value);
  }
  else {
    if(!tree_node->right_child) {
      BinaryTreeNode * tmp = initNode(value);
      tree_node->right_child = tmp;
      return true;
    }
    return InsertRecursive(tree_node->right_child, value);
  }
}

// Used as a helper for the RemoveRecursive helper (like Inception!). This
// function finds the "buddy" node. Read through the link above to find out what
// a buddy is. It would also set the pointer to the buddy node in the parent to
// nullptr. That's why the node is passed in as a reference to a pointer to a
// BinaryTreeNode (so it can be nulled)
BinaryTreeNode* GetNode(BinaryTreeNode* tree_node, int value) {
  if(!tree_node) return nullptr;
  if(tree_node->left_child && value == tree_node->left_child->data) return tree_node;
  if(tree_node->right_child && value == tree_node->right_child->data) return tree_node;
  if(value < tree_node->data && tree_node->left_child) return GetNode(tree_node->left_child, value);
  if(value > tree_node->data && tree_node->right_child) return GetNode(tree_node->right_child, value);
}

// This was the hardest helper for me to write! Removing from a binary tree
// isn't as easy as it at first seems. Read the link above to see why. In this
// helper I also passed the node in as a reference to a pointer to a
// BinaryTreeNode so that I could nullptr the pointer that was pointing to the
// doomed node. That's a lot of pointer right there! Before you can do that
// though, you need to re-arrange the tree so it's still a valid binary search
// tree. If the whole reference to a pointer thing isn't sparkling with you,
// then you can freely make your own helpers :)
bool RemoveRecursive(BinaryTreeNode*& tree_node, int value) {
  if(!tree_node) return false;
  if(!tree_node->left_child && !tree_node->right_child) {
    delete tree_node;
    tree_node = nullptr;
    return true;
  }
  if(!tree_node->right_child) {
    BinaryTreeNode * tmp = tree_node->left_child;
    delete tree_node;
    tree_node = tmp;
    return true;
  }
  if(!tree_node->left_child) {
    BinaryTreeNode * tmp = tree_node->right_child;
    delete tree_node;
    tree_node = tmp;
    return true;
  }
  if(tree_node->left_child && tree_node->right_child) {
    tree_node->data = tree_node->left_child->data;
    return RemoveRecursive(tree_node->left_child, value);
  }
  
  return false;
}

// This is a helper used by the "ToString" method. It is implemented to show you
// how you can recursive traverse a tree. This type of traversal is called
// "depth-first". Take a look at the "ToString()" method to see how the helper
// is used.
std::string ToStringRecursiveDepthFirst(const BinaryTreeNode* tree_node,
                                        int depth) {
  if (!tree_node) {
    return "";
  }
  return ToStringRecursiveDepthFirst(tree_node->left_child, depth + 1) + "d" +
         std::to_string(depth) + "-" + std::to_string(tree_node->data) + " " +
         ToStringRecursiveDepthFirst(tree_node->right_child, depth + 1);
}

void ClearRecursive(BinaryTreeNode * tree_node) {
  if(tree_node->left_child) {
    ClearRecursive(tree_node->left_child);
    delete tree_node->left_child;
    tree_node->left_child = nullptr;
  }
  if(tree_node->right_child) {
    ClearRecursive(tree_node->right_child);
    delete tree_node->right_child;
    tree_node->right_child = nullptr;
  }
  return;
}

}  // namespace

//==============================================================================
//==  METHODS  =================================================================
//==============================================================================
// This is where the methods for the BinaryTree class live. If you chose to use
// recursion (I highly recommend you do or life will kind of suck) then most of
// your code will be in the helper functions you make above. These members will
// just call the helper functions, and maybe check a edge case or two, like if
// the head pointer is equal to nullptr. Take a look at the ToString method to
// see that in action.  Don't forget to read through the helpers to see if you
// can catch any hints on how to get started on these!

// The constructor for the BinaryTree class. Just like the LinkedList
// assignment, it should start by setting "head" to nullptr. There are 2 ways to
// do this in a constructor, you can use either.
BinaryTree::BinaryTree() { head = nullptr; }

// The Size method for the BinaryTree class. This will have to 'count' how many
// nodes you have because we don't store that number anywhere. Only a non-null
// node counts toward that number. Take a look at the recursive "SizeRecursive"
// helper above!
int BinaryTree::Size() { return SizeRecursive(head); }

// The Contains method for the BinaryTree class. Checks the tree to see if
// "value" is in the tree (aka there is a node somewhere who's "data" is set to
// "value"). Returns true if the tree does have the value, and false if the tree
// does not have it. Again, the link above has a good description on how to do
// this.
bool BinaryTree::Contains(int value) { return ContainsRecursive(head, value); }

// The Insert method for the BinaryTree class. Inserts a new node (you'll need
// to "new" a "BinaryTreeNode" for that) into the tree if and only if the value
// isn't a duplicate. If the value is a duplicate, return false. Otherwise
// return true. See the link for how to do this, and the "InsertRecursive"
// helper above for hints on how to do it recursively.
bool BinaryTree::Insert(int value) {
  if(Contains(value)) return false;
  if(head == nullptr) {
    head = initNode(value);
    return true;
  }
  else return InsertRecursive(head, value);
}

// The Remove method for the BinaryTree class. This is by far the hardest to
// implement. Removing from a binary search tree is a little tricky. See the
// link above to understand why. This function returns false if the value isn't
// anywhere in the tree, and true if the value was removed. You'll need to use
// the "delete" operator so you don't leak memory in this one.
bool BinaryTree::Remove(int value) { 
  if(!Contains(value) || head == nullptr) return false;
  BinaryTreeNode * match;
  if(head->data != value) match = GetNode(head, value);
  if(!match) {
    return false;
  }
  if(match->left_child && value == match->left_child->data)
    return RemoveRecursive(match->left_child, value);
  if(match->right_child && value == match->right_child->data)
    return RemoveRecursive(match->right_child, value);
  return RemoveRecursive(head, value);
}

// Extra Credit
// The Clear method for the BinaryTree class. Needs to call "delete" on each
// node, and set head to nullptr.
void BinaryTree::Clear() {
  ClearRecursive(head);
  if(!head->left_child && !head->right_child) {
    delete head;
    head = nullptr;
  }
}

// Already done for you
// The ToString method for the BinaryTree clsss. This will print out a binary
// tree, in the order of it's values. That means it does a "depth first"
// traversal of the tree (Google that). Take a look at the helper
// ToStringRecursiveDepthFirst for how that is done with recursion.
// The values are printed in the format:
// [ d<the depth in the tree this node is at>-<value> d<...>-<...> ]
// So [ d1-1 d0-2 d1-3 d2-4 ] is a tree that looks like:
//
//      2       // Depth 0
//   ___|___
//   |     |
//   1     3    // Depth 1
//         |
//         ___
//           |
//           4  // Depth 2
//
// If you hate that format, you are welcome to change the code here, or in the
// ToStringRecursiveDepthFirst helper so that it looks less, terrible.
std::string BinaryTree::ToString() {
  return "[ " + ToStringRecursiveDepthFirst(head, 0) + "]";
}

}  // namespace binary_tree
}  // namespace assignments
}  // namespace csci2270
}  // namespace external
}  // namespace thilenius
