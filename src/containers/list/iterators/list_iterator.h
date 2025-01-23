#pragma once

#include <stdexcept>

#include "../node.h"

template <typename T>
class ListIterator {
 private:
  using NodeT = Node<T>;
  NodeT* current;

 public:
  ListIterator(Node<T>* value) : current(value) {}

  NodeT* getNode() const { return current; }

  T& operator*() {
    if (!current) throw std::invalid_argument("value is nullptr");
    return current->data;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    current = current->next;
    return temp;
  }

  ListIterator operator--(int) {
    ListIterator temp = *this;
    current = current->prev;
    return temp;
  }
  ListIterator& operator++() {
    current = current->next;
    return *this;
  }

  ListIterator& operator--() {
    current = current->prev;
    return *this;
  }

  bool operator==(const ListIterator& other) const {
    return current == other.current;
  }

  bool operator!=(const ListIterator& other) const {
    return current != other.current;
  }
};