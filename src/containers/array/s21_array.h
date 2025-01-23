#pragma once

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T, size_t N>
class Array {
 private:
  const size_t capacity_{0};
  T* array_{nullptr};

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // constructors
  Array();
  Array(std::initializer_list<value_type> const& items);
  Array(const Array& a);
  Array(Array&& a);
  ~Array();

  // operators
  Array& operator=(Array&& a);
  reference operator[](size_type pos);

  // element access
  reference at(size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // iterators
  iterator begin();
  iterator end();

  // capacity
  bool empty();
  size_type size() const;
  size_type max_size();

  // modifiers
  void swap(Array& other);
  void fill(const_reference value);
};

}  // namespace s21

#include "constructors.tpp"
#include "s21_array.tpp"