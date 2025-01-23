#pragma once

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

#include "iterators/list_const_iterator.h"
#include "iterators/list_iterator.h"
#include "node.h"

namespace s21 {

template <typename T>
class List {
 private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Node<T>* fake_ = new Node<T>(T());

  size_t size_ = 0;

  void mergeSort(List<T>& left, List<T>& right);

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  // constructors
  List();
  List(size_type n);
  List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l);
  ~List();

  // operators
  List& operator=(List&& l);

  // element access
  const_reference front();
  const_reference back();

  // iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // capacity
  bool empty();
  size_type size();
  size_type max_size();

  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void pop_front();
  void push_front(const_reference value);
  void swap(List& other);
  void merge(List& other);
  void splice(const_iterator pos, List& other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);
};

}  // namespace s21

#include "constructors.tpp"
#include "s21_list.tpp"