#pragma once

#include <limits>

#include "../RBtree/RBtree.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <typename Key>
class set : public RBtree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBtree<Key, Key>::iterator;
  using const_iterator = typename RBtree<Key, Key>::const_iterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();

  set& operator=(const set& s);
  set& operator=(set&& s);

  bool contains(const Key& key);

  bool empty();

  size_type size();

  size_type max_size();

  void clear();

  iterator find(const Key& key);

  iterator begin() { return iterator(findMin(this->root)); }

  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() { return const_iterator(findMin(this->root)); }

  const_iterator cend() { return const_iterator(nullptr); }

  std::pair<iterator, bool> insert(const value_type& value);

  void erase(iterator pos);

  void swap(set& other);

  void merge(set& other);

  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::Vector<std::pair<iterator, bool>> results;
    (results.push_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  typename RBtree<Key, Key>::Node* findMin(
      typename RBtree<Key, Key>::Node* node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  typename RBtree<Key, Key>::Node* findMax(
      typename RBtree<Key, Key>::Node* node) {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }
};

}  // namespace s21

#include "s21_set.tpp"