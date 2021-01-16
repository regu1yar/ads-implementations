#pragma once

#include <utility>

template <typename T>
class Deque {
 public:
  Deque() : data_(static_cast<T*>(operator new(sizeof(T) * INITIAL_CAPACITY)))
      , head_offset_(0)
      , size_(0)
      , capacity_(INITIAL_CAPACITY) {

  }

  template <typename U>
  void pushBack(U&& value) {
    if (size_ == capacity_) {
      resize(size_ * INCREASE_SCALE_FACTOR);
    }

    new (data_ + ((head_offset_ + size_) % capacity_)) T(std::forward<U>(value));
    ++size_;
  }

  template <typename U>
  void pushFront(U&& value) {
    if (size_ == capacity_) {
      resize(size_ * INCREASE_SCALE_FACTOR);
    }

    head_offset_ = (head_offset_ + capacity_ - 1) % capacity_;
    new (data_ + head_offset_) T(std::forward<U>(value));
    ++size_;
  }

  void popBack() {
    data_[(head_offset_ + size_) % capacity_].~T();
    --size_;

    if (size_ * DECREASE_SCALE_TRIGGER < capacity_) {
      resize(capacity_ / DECREASE_SCALE_FACTOR);
    }
  }

  void popFront() {
    data_[head_offset_].~T();
    --size_;
    head_offset_ = (head_offset_ + 1) % capacity_;

    if (size_ * DECREASE_SCALE_TRIGGER < capacity_) {
      resize(capacity_ / DECREASE_SCALE_FACTOR);
    }
  }

  const T& operator[](size_t i) const {
    return data_[(head_offset_ + i) % capacity_];
  }

  T& operator[](size_t i) {
    return data_[(head_offset_ + i) % capacity_];
  }

  [[nodiscard]] size_t size() const {
    return size_;
  }

 private:
  void resize(size_t new_capacity) {
    T* resized_data = static_cast<T*>(operator new(sizeof(T) * new_capacity));
    for (size_t i = 0; i != size_; ++i) {
      auto current_index = (head_offset_ + i) % capacity_;
      new (resized_data + i) T(std::move(data_[current_index]));
      data_[current_index].~T();
    }

    delete [] data_;
    data_ = resized_data;
    head_offset_ = 0;
    capacity_ = new_capacity;
  }

 private:
  static const size_t INITIAL_CAPACITY = 2;
  static const size_t INCREASE_SCALE_FACTOR = 2;
  static const size_t DECREASE_SCALE_TRIGGER = 4;
  static const size_t DECREASE_SCALE_FACTOR = 2;

  T* data_;
  size_t head_offset_;
  size_t size_ = 0;
  size_t capacity_;
};