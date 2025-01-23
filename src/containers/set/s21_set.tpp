#include "s21_set.h"

using namespace s21;

template <typename Key>
set<Key>::set() : RBtree<Key, Key>() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items)
    : RBtree<Key, Key>() {
  for (const auto& item : items) {
    this->InsertSet(item);
  }
}

template <typename Key>
set<Key>::set(const set& s) : RBtree<Key, Key>(s) {}

template <typename Key>
set<Key>::set(set&& s) {
  this->root = s.root;
  s.root = nullptr;
}

template <typename Key>
set<Key>::~set() {}

template <typename Key>
typename set<Key>::set& set<Key>::operator=(const set& s) {
  if (this != &s) {
    this->root = this->RBtree<Key, Key>::copyTree(s.root);
  }
  return *this;
}

template <typename Key>
typename set<Key>::set& set<Key>::operator=(set&& s) {
  if (this != &s) {
    this->deleteTree(this->root);

    this->root = s.root;
    s.root = nullptr;
  }
  return *this;
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return this->checkContain(key);
}

template <typename Key>
bool set<Key>::empty() {
  if (this->begin() == nullptr) {
    return true;
  } else {
    return false;
  }
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  size_type size = 0;
  for ([[maybe_unused]] auto _ : *this) {
    size++;
  }
  return size;
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return (std::numeric_limits<size_type>::max() /
          sizeof(typename RBtree<Key, Key>::Node));
}

template <typename Key>
void set<Key>::clear() {
  this->deleteTree(this->root);
  this->root = nullptr;
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  auto it = this->begin();
  for (; it != this->end(); it++) {
    if (*it == key) return it;
  }
  return iterator(findMax(this->root));
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  if (!contains(value)) {
    this->InsertSet(value);
    return {this->findNode(value), true};
  } else {
    return {this->findNode(value), false};
  }
}

template <typename Key>
void set<Key>::swap(set& other) {
  std::swap(this->root, other.root);
}

template <typename Key>
void set<Key>::merge(set& other) {
  if (other.empty()) return;

  for (auto it = other.begin(); it != other.end();) {
    this->insert(*it);
    other.erase(it++);
  }
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (pos != this->end()) this->remove(*pos);
}
