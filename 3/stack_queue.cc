/*
    Tyler Polen
    TA: Upendra Sabnis
    stack_queue.cc
      Assignment 3 main and menu functions
*/
#include <iostream>

#include "linked_list.h"

using namespace std;

int startMenu();
bool structureMenu();

void stackArray();
void stackLinked();
void queueArray();
void queueLinked();

int main() {
  bool running = true;
  bool useArr = true;
  while(running) {
    switch(startMenu()) {
      case 1:
        if(structureMenu()) stackArray();
        else stackLinked();
        break;
      case 2:
        if(structureMenu()) queueArray();
        else queueLinked();
        break;
      case 3:
        running = false;
        break;
      default:
        break;
    }
  }
  return false;
}

int startMenu() {
  cout << endl;
  cout << "1. Create Stack" << endl;
  cout << "2. Create Queue" << endl;
  cout << "3. Exit program" << endl;
  int rv = 0;
  cout << "Enter your choice: ";
  cin >> rv;
  return rv;
}

bool structureMenu() {
  bool running = true;
  while(running) {
    cout << endl;
    cout << "1. Array" << endl;
    cout << "2. Singly linked lists" << endl;
    int rv = 0;
    cout << "Enter your choice: ";
    cin >> rv;
    switch(rv) {
      case 1:
        return true;
      case 2:
          return false;
      default:
        break;
    }
  }
  return -1;
}


void stackArray() {
  bool running = true;
  int max = 5;
  int top = 0;
  int * stack = new int[max];
  while(running) {
    cout << endl;
    cout << "1. PUSH" << endl;
    cout << "2. POP" << endl;
    cout << "3. PRINT STACK" << endl;
    cout << "5. Exit program" << endl;
    int rv = 0;
    cout << "Enter your choice: ";
    cin >> rv;
    cout << endl;
    switch(rv) {
      case 1:
        cout << "What integer: ";
        cin >> stack[top];
        top++;
        break;
      case 2:
        if(top == 0) {
          cout << "Empty" << endl;
          break;
        }
        cout << stack[top - 1] << endl;
        top--;
        break;
      case 3:
        if(top == 0) {
          cout << "Empty" << endl;
          break;
        }
        for(int i = 0; i < top; i++) {
          cout << stack[i] << " ";
        }
        cout << endl;
        break;
      case 5:
        delete stack;
        running = false;
        break;
      default:
        break;
    }
    if(top == max) {
      max = max * 2;
      int * tmp = new int[max];
      for(int i = 0; i < top; i++) tmp[i] = stack[i];
      delete stack;
      stack = tmp;
    }
  }
}


void stackLinked() {
  bool running = true;
  LinkedList * stack = new LinkedList();
  while(running) {
    cout << endl;
    cout << "1. PUSH" << endl;
    cout << "2. POP" << endl;
    cout << "3. PRINT STACK" << endl;
    cout << "5. Exit program" << endl;
    int rv = 0;
    cout << "Enter your choice: ";
    cin >> rv;
    cout << endl;
    
    switch(rv) {
      case 1:
        cout << "What integer: ";
        int tmp;
        cin >> tmp;
        stack->PushFront(tmp);
        break;
      case 2:
        if(!stack->Size()) {
          cout << "Empty" << endl;
          break;
        }
        cout << ((*stack)[0]) << endl;
        stack->RemoveAtIndex(0);
        break;
      case 3:
        if(!stack->Size()) {
          cout << "Empty" << endl;
          break;
        } 
        for(int i = stack->Size()-1; i >= 0; i--)
          cout << ((*stack)[i]) << " ";
        cout << endl;
        break;
      case 5:
        stack->Clear();
        delete stack;
        running = false;
        break;
      default:
        break;
    }
  }
}

void queueArray() {
  bool running = true;
  int max = 2;
  int bottom = 0;
  int top = 0;
  int * queue = new int[max];
  while(running) {
    cout << endl;
    cout << "1. ENQUEUE" << endl;
    cout << "2. DEQUEUE" << endl;
    cout << "3. PRINT QUEUE" << endl;
    cout << "5. Exit program" << endl;
    int rv = 0;
    cout << "Enter your choice: ";
    cin >> rv;
    cout << endl;
    switch(rv) {
      case 1:
        cout << "What integer: ";
        cin >> queue[top];
        top++;
        break;
      case 2:
        if(top == 0) {
          cout << "Empty" << endl;
          break;
        }
        cout << queue[bottom] << endl;
        bottom++;
        break;
      case 3:
        if(top == 0) {
          cout << "Empty" << endl;
          break;
        }
        for(int i = bottom; i < top; i++) {
          cout << queue[i] << " ";
        }
        cout << endl;
        break;
      case 5:
        delete queue;
        running = false;
        break;
      default:
        break;
    }
    if(top == max) {
      max = max * 2;
      int * tmp = new int[max];
      for(int i = 0; i < top; i++) tmp[i] = queue[bottom + i];
      top = top - bottom;
      bottom = 0;
      delete queue;
      queue = tmp;
    }
  }
}

void queueLinked() {
  bool running = true;
  LinkedList * queue = new LinkedList();
  while(running) {
    cout << endl;
    cout << "1. ENQUEUE" << endl;
    cout << "2. DEQUEUE" << endl;
    cout << "3. PRINT QUEUE" << endl;
    cout << "5. Exit program" << endl;
    int rv = 0;
    cout << "Enter your choice: ";
    cin >> rv;
    cout << endl;
    
    switch(rv) {
      case 1:
        cout << "What integer: ";
        int tmp;
        cin >> tmp;
        queue->PushBack(tmp);
        break;
      case 2:
        if(!queue->Size()) {
          cout << "Empty" << endl;
          break;
        }
        cout << ((*queue)[0]) << endl;
        queue->RemoveAtIndex(0);
        break;
      case 3:
        if(!queue->Size()) {
          cout << "Empty" << endl;
          break;
        } 
        for(int i = 0; i < queue->Size(); i++)
          cout << ((*queue)[i]) << " ";
        cout << endl;
        break;
      case 5:
        queue->Clear();
        delete queue;
        running = false;
        break;
      default:
        break;
    }
  }
}
