#pragma once

#include <limits>
#include <random>

template <typename IntKeyType, typename ValueType>
struct Treap {
  struct Node {
    IntKeyType key;
    ValueType value;
    int64_t priority;
    Node* left{nullptr};
    Node* right{nullptr};

    Node(IntKeyType key, const ValueType& value, int64_t priority)
        : key(key)
        , value(value)
        , priority(priority) {
    }

    ~Node() {
      delete left;
      delete right;
    }
  };

  struct SplitResult {
    Node* left{nullptr};
    Node* right{nullptr};
  };

  explicit Treap(int64_t random_seed)
      : random_engine_(random_seed)
      , distribution_(
          std::numeric_limits<int64_t>::min(),
          std::numeric_limits<int64_t>::max()) {
  }

  ~Treap() {
    delete root_;
  }

  void insert(IntKeyType key, const ValueType& value) {
    Node* new_node = new Node(
        key,
        value,
        distribution_(random_engine_)
        );

    auto split_result = split(root_, new_node->key);
    auto left_part = merge(split_result.left, new_node);
    root_ = merge(left_part, split_result.right);
  }

  void erase(IntKeyType key) {
    auto left_split = split(root_, key);
    auto right_split = split(left_split.right, key + 1);
    delete right_split.left;
    root_ = merge(left_split.left, right_split.right);
  }

  bool get(IntKeyType key, ValueType* value) const {
    Node* cur_node = root_;
    while (cur_node != nullptr && cur_node->key != key) {
      if (cur_node->key < key) {
        cur_node = cur_node->right;
      } else {
        cur_node = cur_node->left;
      }
    }

    if (cur_node == nullptr) {
      return false;
    }

    *value = cur_node->value;
    return true;
  }

  static SplitResult split(Node* node, IntKeyType key_value) {
    SplitResult split_result;
    if (node == nullptr) {
      return split_result;
    }

    if (node->key < key_value) {
      split_result.left = node;
      auto next_split = split(node->right, key_value);
      split_result.left->right = next_split.left;
      split_result.right = next_split.right;
    } else {
      split_result.right = node;
      auto next_split = split(node->left, key_value);
      split_result.right->left = next_split.right;
      split_result.left = next_split.left;
    }

    return split_result;
  }

  static Node* merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }

    if (right == nullptr) {
      return left;
    }

    if (left->priority < right->priority) {
      right->left = merge(left, right->left);
      return right;
    } else {
      left->right = merge(left->right, right);
      return left;
    }
  }

  std::default_random_engine random_engine_;
  std::uniform_int_distribution<int64_t> distribution_;
  Node* root_{nullptr};
};
