#pragma once

#include <stdexcept>

#include "../node.h"
#include "list_iterator.h"

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  using ListIterator<T>::ListIterator;

  const T& operator*() const {
    if (!this->getNode()) throw std::invalid_argument("value is nullptr");
    return this->getNode()->data;
  }
};