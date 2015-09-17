// Copyright 2015 Alec Thilenius
// All rights reserved.

#include "cpp_refresher.h"

void PrintHelloWorld() {
  // Here you need to cout something (I recommend "Hello, world!" because
  // Computer Science, naturally).
  // Don't forget to include iostream!
  std::cout << "Hello World";
}

void CallUberFunctions() {
  // There is a magic function, called "UberFunction" that is capable of taking
  // anything for an argument. You need to call "UberFunction" with the
  // following types: int, int* int** and char[]
  // You also need to call "OtherUberFunction" in the namespace
  // "uber_namespace" once, with no arguments.

  // The first one has been done for you:
  int a = 42;
  UberFunction(a);
  int* b;
  UberFunction(b);
  int** c;
  UberFunction(c);
  char d[1];
  UberFunction(d);
  uber_namespace::OtherUberFunction();
}

void Loops(int number_of_times) {
  // Call "DoesAwesomeLoopyThings" without passing in anything,
  // "number_of_times" times. Some type of a loop is a good candidate for this.
  for (int i = 0; i < number_of_times; i++) {
    DoesAwesomeLoopyThings();
  }
}

void CopyArrayOnHeap(const char* str) {
  // This ones a bit more tricky! The char* str here is a C style string.
  // Remember that C strings end in a NULL, aka a 0
  // Hint: You can find the length of the string knowing that piece of
  // information.
  // The goal is to create another C string (a char*) on the heap of the exact
  // same size as str, including the 0 at the end.
  // Then clean up memory by freeing the string on the heap.
  // You MUST use "new" and "delete", you cannot use malloc and free.
  int i = 0;
  while (str[i]) {
    i++;
  }
  char* strcpy;
  strcpy = new char [i+1];
  delete[] strcpy;
}

void UseingObjects(UberClass& uber_class_1, UberClass* uber_class_2,
                   UberClass** uber_class_3) {
  // UbserCLass is a class with a member function (also called a method) called
  // "UberMethod" and a member variable (often just called a member) called
  // "uber_member".
  // For each of the instances of the UberClass that was passed in (aka. for
  // each of the objects) you need to call the member function (the method)
  // You also need to set the member variable to 42.
  uber_class_1.UberMethod();
  uber_class_1.uber_member = 42;
  
  uber_class_2->UberMethod();
  uber_class_2->uber_member = 42;
  
  (**uber_class_3).UberMethod();
  (**uber_class_3).uber_member = 42;
}

// Extra Credit
void InPlaceReverse(char* str) {
  // This is a really tricky one! You must reverse the order of the C string
  // without allocating a new C string. Think about how to do this without
  // creating a second string, it's possible, I promise :)
  int n = 0;
  while (str[n]) {
    n++;
  }

  char* t = &str[n + 1];

  for(int i = 0; i < n/2; i++) {
    *t = str[i];
    str[i] = str[n-i-1];
    str[n-i-1] = *t;
  }
  str[n+1] = '\0';
}
