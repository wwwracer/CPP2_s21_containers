#pragma once

#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

#include "../RBtree/RBtree.h"

namespace s21 {
template <typename Key, typename T>
class map : public RBtree<Key, T> {
  class MapIterator : public RBtree<Key, T> {
    using Node = typename RBtree<Key, T>::Node;

   private:
    Node* currentNode;
    Node* next(Node* node);
    std::pair<Key, T> tmp;

   public:
    MapIterator() : currentNode(nullptr) {}

    MapIterator(Node* rootNode) : currentNode(rootNode) {
      if (rootNode) tmp = {rootNode->key_, rootNode->data_};
    }

    ~MapIterator() = default;

    //  Оператор разыменования
    std::pair<const Key, T>& operator*() { return tmp; }

    const std::pair<const Key, T>& operator*() const { return tmp; }

    // Оператор доступа
    std::pair<const Key, T>* operator->() {
      return reinterpret_cast<std::pair<const Key, T>*>(&tmp);
    }

    // Префексный оператор инкремента
    MapIterator& operator++() {
      currentNode = next(currentNode);
      if (!currentNode) {
        return *this;
      }
      tmp = {currentNode->key_, currentNode->data_};
      return *this;
    }

    // Постфиксный оператор инкремента
    MapIterator operator++(int) {
      MapIterator temp = *this;
      ++(*this);
      return temp;
    }

    // Оператор сравнения
    bool operator==(const MapIterator& other) const {
      return currentNode == other.currentNode;
    }

    bool operator!=(const MapIterator& other) const {
      return currentNode != other.currentNode;
    }
  };
  class MapConstIterator : public RBtree<Key, T> {
   public:
    using Node = typename RBtree<Key, T>::Node;

    MapConstIterator() : currentNode(nullptr) {}

    MapConstIterator(Node* rootNode) : currentNode(rootNode) {}

    ~MapConstIterator() {
      if (tmp != nullptr) delete tmp;
    }

    // Оператор разыменования
    const std::pair<const Key, T> operator*() const {
      return {currentNode->key_, currentNode->data_};
    }

    // Оператор доступа
    const std::pair<const Key, T>* operator->() {
      if (tmp != nullptr) delete tmp;
      tmp = new std::pair<const Key, T>(currentNode->key_, currentNode->data_);

      return tmp;
    }

    // Префиксный оператор инкремента
    MapConstIterator& operator++() {
      currentNode = next(currentNode);
      return *this;
    }

    // Постфиксный оператор инкремента
    MapConstIterator operator++(int) {
      MapConstIterator temp = *this;
      ++(*this);
      this->tmp = nullptr;
      return temp;
    }

    // Оператор сравнения
    bool operator==(const MapConstIterator& other) const {
      return currentNode == other.currentNode;
    }

    bool operator!=(const MapConstIterator& other) const {
      return currentNode != other.currentNode;
    }

   private:
    Node* currentNode;
    std::pair<const Key, T>* tmp = nullptr;
    Node* next(Node* node);
  };

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);

  map(map&& m) noexcept;

  ~map();
  // this->deleteTree(this->root);

  map& operator=(const map& other);

  map& operator=(map&& m) noexcept;

  T& at(const Key& key);

  T& operator[](const Key& key);

  bool contains(const Key& key);

  iterator begin() { return iterator(findMin(this->root)); }

  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() { return const_iterator(findMin(this->root)); }

  const_iterator cend() { return const_iterator(nullptr); }

  std::pair<iterator, bool> insert(const value_type& value);

  std::pair<iterator, bool> insert(const Key& key, const T& obj);

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.push_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(
      std::initializer_list<value_type> const& pairs) {
    std::vector<std::pair<iterator, bool>> results;
    for (const auto& pair : pairs) {
      results.push_back(this->insert(pair));
    }
    return results;
  }

  bool empty();

  void clear();

  size_type size();

  size_type max_size() const;

  void swap(map& other);

  void erase(iterator pos);

  void merge(map& other);

 private:
  typename RBtree<Key, T>::Node* findMin(typename RBtree<Key, T>::Node* node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }
};

}  // namespace s21

#include "s21_map.tpp"