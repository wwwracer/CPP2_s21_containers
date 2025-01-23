#include "s21_multiset.h"

using namespace s21;

template <typename Key>
multiset<Key>::multiset() : RBtree<Key, Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : RBtree<Key, Key>() {
  for (const auto& item : items) {
    this->InsertSet(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& s) : RBtree<Key, Key>(s) {}

template <typename Key>
multiset<Key>::multiset(multiset&& s) {
  this->root = s.root;
  s.root = nullptr;
}

template <typename Key>
multiset<Key>::~multiset() {}

template <typename Key>
typename multiset<Key>::multiset& multiset<Key>::operator=(const multiset& s) {
  if (this != &s) {
    this->root = this->RBtree<Key, Key>::copyTree(s.root);
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::multiset& multiset<Key>::operator=(multiset&& s) {
  if (this != &s) {
    this->deleteTree(this->root);

    this->root = s.root;
    s.root = nullptr;
  }
  return *this;
}

template <typename Key>
bool multiset<Key>::empty() {
  if (this->begin() == nullptr) {
    return true;
  } else {
    return false;
  }
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  size_type Size = 0;
  for ([[maybe_unused]] auto _ :
       *this) {  // maybe_unsused - говорит компилятору что переменная может не
                 // использоваться
    Size++;
  }
  return Size;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return (std::numeric_limits<size_type>::max() /
          sizeof(typename RBtree<Key, Key>::Node));
}

template <typename Key>
void multiset<Key>::clear() {
  this->deleteTree(this->root);
  this->root = nullptr;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  return this->InsertSetWithNode(value);
}

template <typename Key>  // Ошибка сегментации в fixDelete
void multiset<Key>::erase(iterator pos) {
  if (pos != this->end()) this->remove(*pos);
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  /*
    multiset<Key> temp = *this;
  *this = other;
  other = temp;
  */
  std::swap(this->root, other.root);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  if (other.empty()) return;

  for (auto it = other.begin(); it != other.end();) {
    this->insert(*it);
    other.erase(it++);
  }
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_type size = 0;
  for (auto it = this->begin(); it != this->end(); it++) {
    if (*it == key) size++;
  }
  return size;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  auto it = this->begin();
  for (; it != this->end(); it++) {
    if (*it == key) return it;
  }
  return iterator(findMax(this->root));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::ex_find(const Key& key) {
  auto it = this->begin();
  for (; it != this->end(); it++) {
    if (*it == key) return it;
  }
  return this->end();
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  return this->checkContain(key);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return {this->lower_bound(key), this->upper_bound(key)};
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  for (auto it = this->begin(); it != this->end(); it++) {
    if (*it == key) return it;
  }
  return this->end();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return this->findLust(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::findLust(
    const_reference value) {
  auto it = this->ex_find(value);
  if (it == this->end()) return this->end();
  auto copy_it = it;
  if (++copy_it == this->end()) return this->end();
  for (; *it == value && it != this->end(); it++) {
  }
  return it;
}
