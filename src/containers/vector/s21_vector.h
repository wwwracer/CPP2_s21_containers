#pragma once

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <limits>

namespace s21 {

template <typename T>
class Vector {
 private:
  size_t size_{0};
  size_t capacity_{0};
  T* array_{nullptr};

  void deallocate();

 public:
  // type overrides
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // constructors
  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v);
  ~Vector();

  // operators
  Vector& operator=(Vector&& v);
  reference operator[](size_type pos);

  // methods for accessing the elements
  reference at(size_type pos);
  const_reference front() const;
  const_reference back() const;
  T* data();

  // methods for iterating over class elements
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // methods for accessing the container capacity information
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // methods for modifying a container
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "constructors.tpp"
#include "s21_vector.tpp"