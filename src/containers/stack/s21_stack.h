#pragma once

#include "../../s21_containers.h"
#include "../list/iterators/list_const_iterator.h"
#include "../list/iterators/list_iterator.h"

namespace s21 {

template <typename T, class container = List<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  using iterator = ListIterator<T>;

  Stack() noexcept : cont() {}
  Stack(std::initializer_list<value_type> const &items) : cont(items) {}
  Stack(const Stack &q) = default;
  Stack(Stack &&q) noexcept = default;
  ~Stack() noexcept = default;

  Stack<T> &operator=(Stack &&q) = default;

  const_reference top() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { cont.push_back(value); }
  void pop() { cont.pop_back(); }
  void swap(Stack &other) { cont.swap(other.cont); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    cont.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  container cont;
};

}  // namespace s21
