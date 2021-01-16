#include <iostream>

#include "vector.h"
#include "deque.h"

int main(int argc, char** argv) {
  {
    Vector<int> v;
    for (size_t i = 0; i < 10; ++i) {
      v.pushBack(i);
    }

    for (size_t i = 0; i < v.size(); ++i) {
      std::cout << v[i] << ' ';
    }

    std::cout << std::endl;

    for (size_t i = 0; i < 5; ++i) {
      v.popBack();
    }

    for (size_t i = 0; i < v.size(); ++i) {
      std::cout << v[i] << ' ';
    }

    std::cout << std::endl;
  }

  {
    Deque<int> deque;
    for (size_t i = 0; i < 10; ++i) {
      deque.pushBack(i);
    }

    for (size_t i = 0; i < deque.size(); ++i) {
      std::cout << deque[i] << ' ';
    }

    std::cout << std::endl;

    for (size_t i = 0; i < 5; ++i) {
      deque.popFront();
    }

    for (size_t i = 0; i < deque.size(); ++i) {
      std::cout << deque[i] << ' ';
    }

    std::cout << std::endl;

    for (size_t i = 0; i < 5; ++i) {
      deque.popBack();
    }

    for (size_t i = 0; i < deque.size(); ++i) {
      std::cout << deque[i] << ' ';
    }

    std::cout << std::endl;
  }
}
