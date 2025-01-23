#pragma once

#include <limits>

#include "../RBtree/RBtree.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <typename Key>
class multiset : public RBtree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBtree<Key, Key>::iterator;
  using const_iterator = typename RBtree<Key, Key>::const_iterator;
  using size_type = size_t;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& s);
  multiset(multiset&& s);
  ~multiset();

  multiset& operator=(const multiset& s);
  multiset& operator=(multiset&& s);

  iterator begin() { return iterator(findMin(this->root)); }
  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() { return const_iterator(findMin(this->root)); }
  const_iterator cend() { return const_iterator(nullptr); }

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type& value);

  template <typename... Args>
  s21::Vector<iterator> insert_many(Args&&... args) {
    s21::Vector<iterator> results;
    (results.push_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }

  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

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

  iterator findLust(const_reference value);
  iterator ex_find(const Key& key);
};

}  // namespace s21

#include "s21_multiset.tpp"
