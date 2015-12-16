// Copyright 2015 Alec Thilenius
// All rights reserved.
/*
    Tyler Polen
    TA: Upendra Sabnis
    linked_list.h
      Linked List class header file
*/

#ifndef EXTERNAL_CSCI2270_ASSIGNMENTS_02_LINKED_LIST_H_
#define EXTERNAL_CSCI2270_ASSIGNMENTS_02_LINKED_LIST_H_

struct LinkedListNode {
  int data;
  LinkedListNode* next_node;
};

class LinkedList {
 public:
  LinkedList();
  int Size();
  bool InsertAtIndex(int value, int index);
  void PushFront(int value);
  void PushBack(int value);
  int& operator[] (int index);
  bool RemoveAtIndex(int index);
  void Clear();

  void RemoveAll(int value);

  LinkedListNode* head;
};




#endif  // EXTERNAL_CSCI2270_ASSIGNMENTS_02_LINKED_LIST_H_
