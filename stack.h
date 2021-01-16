#pragma once

#include <utility>

#include "list.h"

template <typename T>
class Stack {
 public:
  template <typename U>
  void push(U&& value) {
    list_.template pushFront(std::forward<U>(value));
  }

  void pop() {
    list_.popFront();
  }

  const T& top() const {
    return list_.front();
  }

  T& front() {
    return list_.front();
  }

 private:
  List<T> list_;
};