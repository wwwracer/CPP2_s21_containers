#include "s21_vector.h"

using namespace s21;

template <typename T>
Vector<T>::Vector() {}

template <typename T>
Vector<T>::Vector(size_type n) : size_(n), capacity_(n) {
  array_ = new T[capacity_];

  for (size_type i = 0; i < size_; i++) {
    array_[i] = T();
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const& items)
    : size_(items.size()), capacity_(items.size()) {
  array_ = new T[capacity_];

  size_type index = 0;

  for (auto it = items.begin(); it != items.end(); it++) {
    array_[index++] = *it;
  }
}

template <typename T>
Vector<T>::Vector(const Vector& v) : Vector(v.capacity()) {
  size_ = v.size();

  for (size_type i = 0; i < v.size(); i++) {
    array_[i] = v.array_[i];
  }
}

template <typename T>
Vector<T>::Vector(Vector&& v) {
  *this = std::move(v);
}

template <typename T>
Vector<T>::~Vector() {
  deallocate();
  capacity_ = 0;
  size_ = 0;
}