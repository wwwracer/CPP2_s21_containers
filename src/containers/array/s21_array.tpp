#include "s21_array.h"

using namespace s21;

template <typename T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const {
  return capacity_;
}

template <typename T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() {
  return size();
}

template <typename T, size_t N>
bool Array<T, N>::empty() {
  return capacity_ == 0;
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return array_;
}

template <typename T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= capacity_) throw std::out_of_range("out of range");

  return array_[pos];
}

template <typename T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return array_[pos];
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  return array_;
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  return array_ + capacity_;
}

template <typename T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  return array_[0];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  return array_[capacity_ - 1];
}

template <typename T, size_t N>
void Array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < capacity_; i++) array_[i] = value;
}

template <typename T, size_t N>
void Array<T, N>::swap(Array<T, N> &other) {
  std::swap_ranges(array_, array_ + capacity_, other.array_);
}

template <typename T, std::size_t N>
typename Array<T, N>::Array &Array<T, N>::operator=(Array<T, N> &&a) {
  for (size_t i = 0; i < N; ++i) array_[i] = std::move(a.array_[i]);

  return *this;
}