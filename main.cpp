#include <iostream>

#include "vector.h"
#include "deque.h"
#include "segment_tree.h"
#include "treap.h"
#include "treap_implicit.h"

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

  {
    std::cout << "----------------SegmentTree begin--------------------\n";
    std::vector<int> initial_values{
      0, 1, 2, 3, 4, 5, 6, 7
    };

    SegmentTree<int> segment_tree(initial_values);
    segment_tree.print();

    std::cout << "add 3 on (0, 3)" << std::endl;
    segment_tree.add(3, 0, 3);
    std::cout << "Min of (2, 5): " << segment_tree.getMin(2, 5) << std::endl;

    segment_tree.print();

    std::cout << "----------------SegmentTree begin--------------------\n";
  }

  {
    std::cout << "----------------TreapImplicit begin--------------------\n";
    TreapImplicit<int> treap_implicit(42);
    for (int i = 0; i < 10; ++i) {
      treap_implicit.insert(i, i);
    }

    for (size_t i = 0; i < 10; ++i) {
      int value;
      if (treap_implicit.get(i, &value)) {
        std::cout << value << ' ';
      }
    }

    std::cout << std::endl;

    for (int i = 4; i >= 0; --i) {
      treap_implicit.erase(i * 2);
    }

    for (int i = 0; i < 10; ++i) {
      int value;
      if (treap_implicit.get(i, &value)) {
        std::cout << value << ' ';
      }
    }

    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
      treap_implicit.erase(0);
    }

    for (int i = 0; i < 15; ++i) {
      int value;
      if (treap_implicit.get(i, &value)) {
        std::cout << value << ' ';
      } else {
        std::cout << i << "? ";
      }
    }

    std::cout << std::endl;
    std::cout << "----------------TreapImplicit begin--------------------\n";
  }
}
