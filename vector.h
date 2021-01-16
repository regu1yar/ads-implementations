#pragma once

#include <utility>

template <typename T>
class Vector {
 public:
  Vector() : data_(static_cast<T*>(operator new(sizeof(T) * INITIAL_CAPACITY)))
           , size_(0)
           , capacity_(INITIAL_CAPACITY) {

  }

  template <typename U>
  void pushBack(U&& value) {
    if (size_ == capacity_) {
      resize(capacity_ * INCREASE_SCALE_FACTOR);
    }

    new (data_ + size_) T(std::forward<U>(value));
    ++size_;
  }

  void popBack() {
    data_[size_].~T();
    --size_;

    if (size_ * DECREASE_SCALE_TRIGGER < capacity_) {
      resize(capacity_ / DECREASE_SCALE_FACTOR);
    }
  }

  const T& operator[](size_t i) const {
    return data_[i];
  }

  T& operator[](size_t i) {
    return data_[i];
  }

  [[nodiscard]] size_t size() const {
    return size_;
  }

 private:
  void resize(size_t new_capacity) {
    T* resized_data = static_cast<T*>(operator new(sizeof(T) * new_capacity));
    for (size_t i = 0; i < size_; ++i) {
      new (resized_data + i) T(std::move(data_[i]));
      data_[i].~T();
    }

    delete [] data_;
    data_ = resized_data;
    capacity_ = new_capacity;
  }

 private:
  static const size_t INITIAL_CAPACITY = 2;
  static const size_t INCREASE_SCALE_FACTOR = 2;
  static const size_t DECREASE_SCALE_TRIGGER = 4;
  static const size_t DECREASE_SCALE_FACTOR = 2;

  T* data_;
  size_t size_;
  size_t capacity_;
};
