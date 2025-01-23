#include "s21_array.h"

using namespace s21;

template <typename T, size_t N>
Array<T, N>::Array() : capacity_(N) {
  if (N == 0) return;
  array_ = new T[capacity_];

  for (size_t i = 0; i < capacity_; i++) array_[i] = T();
}

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const& items)
    : capacity_(N) {
  array_ = new T[capacity_];

  for (size_t i = 0; i < capacity_; i++) {
    if (i < items.size()) {
      array_[i] = items.begin()[i];
      continue;
    }

    array_[i] = T();
  }
}

template <typename T, size_t N>
Array<T, N>::Array(const Array& a)
    : capacity_(a.capacity_), array_(new T[a.capacity_]) {
  for (size_t i = 0; i < a.size(); ++i) array_[i] = a.array_[i];
}

template <typename T, size_t N>
Array<T, N>::Array(Array<T, N>&& a) : capacity_(N) {
  if (N == 0) return;
  array_ = new T[capacity_];

  std::move(a.array_, a.array_ + N, array_);
}

template <typename T, size_t N>
Array<T, N>::~Array() {
  if (capacity_ != 0) delete[] array_;
}