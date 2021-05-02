#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template <typename NumericT>
struct SegmentTree {
 public:
  explicit SegmentTree(
      const std::vector<NumericT>& initial_values)
      : result_(initial_values.size() * 4 + 1)
      , buffered_(initial_values.size() * 4 + 1, 0)
      , is_buffered_(initial_values.size() * 4 + 1, false) {
    build(initial_values, 1, 0, initial_values.size() - 1);
  }

  void add(NumericT value, size_t left_request, size_t right_request) {
    add(value, left_request, right_request, 1, 0, getInitialRightBound());
  }

  NumericT getMin(size_t left_request, size_t right_request) {
    return getMin(left_request, right_request,
                  1, 0, getInitialRightBound());
  }

  void print() {
    size_t line = 0;
    size_t power = 2;
    size_t wideness = getInitialRightBound() + 1;
    for (size_t i = 1; i < wideness * 2; ++i) {
      push(i);
      std::cout << std::string(wideness / (line + 1), ' ')
                << result_[i]
                << std::string(wideness / (line + 1), ' ');

      if (i == power - 1) {
        std::cout << std::endl;
        ++line;
        power *= 2;
      }
    }

    std::cout << std::endl;
  }

 private:
  [[nodiscard]] size_t getInitialRightBound() const {
    return (result_.size() - 1) / 4 - 1;
  }

  void build(const std::vector<NumericT>& initial_values,
             size_t node_id,
             size_t left_bound,
             size_t right_bound) {
    if (left_bound == right_bound) {
      result_[node_id] = initial_values[left_bound];
      return;
    }

    size_t middle = (left_bound + right_bound) / 2;
    build(initial_values, node_id * 2, left_bound, middle);
    build(initial_values, node_id * 2 + 1, middle + 1, right_bound);
    result_[node_id] = std::min(result_[node_id * 2], result_[node_id * 2 + 1]);
  }

  void add(NumericT value, size_t left_request, size_t right_request,
           size_t node_id, size_t left_bound, size_t right_bound) {
    if (left_bound == left_request && right_bound == right_request) {
      buffered_[node_id] += value;
      is_buffered_[node_id] = true;
      result_[node_id] += value;
      return;
    }

    push(node_id);
    size_t middle = (left_bound + right_bound) / 2;
    if (left_request <= middle) {
      add(value, left_request, std::min(right_bound, middle), node_id * 2, left_bound, middle);
    }

    if (right_request > middle) {
      add(value, std::max(left_request, middle + 1), right_request, node_id * 2 + 1, middle + 1, right_bound);
    }
  }

  NumericT getMin(size_t left_request, size_t right_request,
                  size_t node_id, size_t left_bound, size_t right_bound) {
    if (left_bound == left_request && right_bound == right_request) {
      return result_[node_id];
    }

    push(node_id);
    size_t middle = (left_bound + right_bound) / 2;
    bool found_left = false;
    NumericT result;
    if (left_request <= middle) {
      result = getMin(left_request, std::min(right_bound, middle),
                      node_id * 2, left_bound, middle);
      found_left = true;
    }

    if (right_request > middle) {
      auto right_min = getMin(std::max(left_request, middle + 1),
                              right_request, node_id * 2 + 1, middle + 1,
                              right_bound);

      if (found_left) {
        result = std::min(result, right_min);
      } else {
        result = right_min;
      }
    }

    return result;
  }

  void push(size_t node_id) {
    if (!is_buffered_[node_id]) {
      return;
    }

    size_t left_child = node_id * 2;
    size_t right_child = left_child + 1;

    buffered_[left_child] += buffered_[node_id];
    is_buffered_[left_child] = true;
    result_[left_child] += buffered_[node_id];

    buffered_[right_child] += buffered_[node_id];
    is_buffered_[right_child] = true;
    result_[right_child] += buffered_[node_id];

    buffered_[node_id] = 0;
    is_buffered_[node_id] = false;
  }

 private:
  std::vector<NumericT> result_;
  std::vector<NumericT> buffered_;
  std::vector<bool> is_buffered_;
};
