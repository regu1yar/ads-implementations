#pragma once

#include <limits>
#include <random>

template <typename ValueType>
struct TreapImplicit {
  struct Node {
   public:
    ValueType value;
    int64_t priority;

    Node(const ValueType& value, int64_t priority)
        : value(value)
        , priority(priority)
        , size_(1) {
    }

    ~Node() {
      delete left_;
      delete right_;
    }

    [[nodiscard]] size_t getSize() const {
      return size_;
    }

    Node* getLeft() const {
      return left_;
    }

    Node* getRight() const {
      return right_;
    }

    void setLeft(Node* left) {
      left_ = left;
      updateSize();
    }

    void setRight(Node* right) {
      right_ = right;
      updateSize();
    }

   private:
    void updateSize() {
      size_ = 1;
      if (left_ != nullptr) {
        size_ += left_->getSize();
      }

      if (right_ != nullptr) {
        size_ += right_->getSize();
      }
    }

   private:
    size_t size_;
    Node* left_{nullptr};
    Node* right_{nullptr};
  };

  struct SplitResult {
    Node* left{nullptr};
    Node* right{nullptr};
  };

  explicit TreapImplicit(int64_t random_seed)
      : random_engine_(random_seed)
      , distribution_(
          std::numeric_limits<int64_t>::min(),
          std::numeric_limits<int64_t>::max()) {
  }

  ~TreapImplicit() {
    delete root_;
  }

  void insert(size_t id, const ValueType& value) {
    Node* new_node = new Node(
        value,
        distribution_(random_engine_)
    );

    auto split_result = split(root_, id);
    auto left_part = merge(split_result.left, new_node);
    root_ = merge(left_part, split_result.right);
  }

  void erase(size_t id) {
    auto right_split = split(root_, id + 1);
    auto left_split = split(right_split.left, id);
    delete left_split.right;
    root_ = merge(left_split.left, right_split.right);
  }

  bool get(size_t id, ValueType* value) const {
    if (root_ == nullptr) {
      return false;
    }

    Node* cur_node = root_;
    size_t cur_id = 0;
    if (root_->getLeft() != nullptr) {
      cur_id = root_->getLeft()->getSize();
    }

    while (cur_id != id) {
      if (cur_id < id) {
        cur_node = cur_node->getRight();
        if (cur_node == nullptr) {
          return false;
        }

        ++cur_id;
        if (cur_node->getLeft() != nullptr) {
          cur_id += cur_node->getLeft()->getSize();
        }
      } else {
        cur_node = cur_node->getLeft();
        assert(cur_node != nullptr);
        --cur_id;
        if (cur_node->getRight() != nullptr) {
          cur_id -= cur_node->getRight()->getSize();
        }
      }
    }

    *value = cur_node->value;
    return true;
  }

  static SplitResult split(Node* node, size_t id) {
    SplitResult split_result;
    if (node == nullptr) {
      return split_result;
    }

    size_t node_id = 0;
    if (node->getLeft() != nullptr) {
      node_id = node->getLeft()->getSize();
    }

    if (node_id < id) {
      split_result.left = node;
      auto next_split = split(node->getRight(), id - node_id - 1);
      split_result.left->setRight(next_split.left);
      split_result.right = next_split.right;
    } else {
      split_result.right = node;
      auto next_split = split(node->getLeft(), id);
      split_result.right->setLeft(next_split.right);
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
      right->setLeft(merge(left, right->getLeft()));
      return right;
    } else {
      left->setRight(merge(left->getRight(), right));
      return left;
    }
  }

  std::default_random_engine random_engine_;
  std::uniform_int_distribution<int64_t> distribution_;
  Node* root_{nullptr};
};
