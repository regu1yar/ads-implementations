#include <iostream>

#include "vector.h"
#include "deque.h"
#include "treap.h"

int main(int argc, char** argv) {
  {
    std::cout << "----------------Vector begin--------------------\n";
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
    std::cout << "----------------Vector end--------------------\n\n";
  }

  {
    std::cout << "----------------Deque begin--------------------\n";
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
    std::cout << "----------------Deque begin--------------------\n";
  }

  {
    std::cout << "----------------Treap begin--------------------\n";
    Treap<int, int> treap(42);
    for (int i = 0; i < 10; ++i) {
      treap.insert(i, i);
    }

    for (int i = -5; i < 15; ++i) {
      int value;
      if (treap.get(i, &value)) {
        std::cout << value << ' ';
      } else {
        std::cout << i << "? ";
      }
    }

    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
      treap.erase(i * 2);
    }

    for (int i = -5; i < 15; ++i) {
      int value;
      if (treap.get(i, &value)) {
        std::cout << value << ' ';
      } else {
        std::cout << i << "? ";
      }
    }

    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
      treap.erase(i * 2 + 1);
    }

    for (int i = -5; i < 15; ++i) {
      int value;
      if (treap.get(i, &value)) {
        std::cout << value << ' ';
      } else {
        std::cout << i << "? ";
      }
    }

    std::cout << std::endl;
    std::cout << "----------------Treap begin--------------------\n";
  }
}
