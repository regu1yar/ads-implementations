#pragma once

#include <utility>

template <typename T>
class Node {
 public:
  explicit Node(const T& value) : value_(value) {
  }

  explicit Node(T&& value) : value_(std::move(value)) {
  }

  ~Node() {
    if (next_ != nullptr) {
      delete next_;
    }
  }

  void setNext(Node* next) {
    next_ = next;
  }

  const T& getValue() const {
    return value_;
  }

  Node* getNext() const {
    return next_;
  }

 private:
  T value_;
  Node* next_{nullptr};
};

template <typename T>
class List {
 public:
  ~List() {
    if (head_ != nullptr) {
      delete head_;
    }
  }

  template <typename U>
  void pushFront(U&& value) {
    Node* new_node = new Node(std::forward<U>(value));
    if (head_ != nullptr) {
      new_node->setNext(head_);
    }

    head_ = new_node;
  }

  void popFront() {
    Node* old_head = head_;
    head_ = head_->getNext();
    delete old_head;
  }

  const T& front() const {
    return head_->getValue();
  }

  T& front() {
    return head_->getValue();
  }

 private:
  Node<T>* head_{nullptr};
};
