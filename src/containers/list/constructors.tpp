#include "s21_list.h"

using namespace s21;

template <typename T>
List<T>::List() {
  head_ = fake_;
}

template <typename T>
List<T>::List(size_type n) {
  for (size_t i = 0; i < n; i++) this->push_back(T());
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(); it != items.end(); it++) this->push_back(*it);
}

template <typename T>
List<T>::List(const List& l) {
  for (auto it = l.cbegin(); it != l.cend(); it++) this->push_back(*it);
}

template <typename T>
List<T>::List(List&& l) {
  *this = std::move(l);
}

template <typename T>
List<T>::~List() {
  this->clear();
}