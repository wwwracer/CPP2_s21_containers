#pragma once

#include "../../s21_containers.h"
#include "../list/iterators/list_const_iterator.h"
#include "../list/iterators/list_iterator.h"

namespace s21 {

template <typename T, class container = List<T>>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  using iterator = ListIterator<T>;

  Queue() : cont() {}
  Queue(std::initializer_list<value_type> const &items) : cont(items) {}
  Queue(const Queue &q) = default;
  Queue(Queue &&q) = default;
  ~Queue() = default;

  Queue<T> &operator=(Queue &&q) = default;

  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  void push(const_reference data_) { cont.push_back(data_); }
  void pop() { cont.pop_front(); }
  void swap(Queue &other) { cont.swap(other.cont); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    cont.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  container cont;

};  // class

}  // namespace s21