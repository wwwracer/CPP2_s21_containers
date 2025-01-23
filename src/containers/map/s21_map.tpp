#include "s21_map.h"

using namespace s21;

template <typename Key, typename T>
map<Key, T>::map() : RBtree<Key, T>(){};

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items)
    : RBtree<Key, T>() {
  for (const auto& item : items) {
    if (!this->contains(item.first)) this->Insert(item.first, item.second);
  }
};

template <typename Key, typename T>
map<Key, T>::map(const map& m) : RBtree<Key, T>(m){};

template <typename Key, typename T>
typename map<Key, T>::map& map<Key, T>::operator=(const map& other) {
  if (this != &other) {
    this->root = this->RBtree<Key, T>::copyTree(other.root);
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>::map(map&& m) noexcept {
  this->root = m.root;
  m.root = nullptr;
};

template <typename Key, typename T>
map<Key, T>::~map(){
    // this->deleteTree(this->root);
};

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map<Key, T>&& m) noexcept {
  if (this != &m) {  // Проверка на самоприсваивание
    // Освобождаем текущие ресурсы
    this->deleteTree(this->root);

    // Перемещаем ресурсы
    this->root = m.root;
    m.root = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  return this->checkContain(key);
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  if (!this->checkContain(key)) {
    this->RBtree<Key, T>::Insert(key, T());
  }
  return this->RBtree<Key, T>::find(key);
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  if (!this->checkContain(key)) {
    throw std::out_of_range("Key not found");
  }
  return this->RBtree<Key, T>::find(key);
};

template <typename Key, typename T>
typename RBtree<Key, T>::Node* map<Key, T>::MapIterator::next(Node* node) {
  // Реализация остается той же
  if (node == nullptr) return nullptr;

  if (node->right) {
    node = node->right;
    while (node->left) {
      node = node->left;
    }
    return node;
  } else {
    Node* parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }
};

template <typename Key, typename T>
typename RBtree<Key, T>::Node* map<Key, T>::MapConstIterator::next(Node* node) {
  if (node->right) {
    node = node->right;
    while (node->left) {
      node = node->left;
    }
  } else {
    Node* parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return node;
};

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  if (!this->contains(value.first)) {
    this->Insert(value.first, value.second);
    return {this->findNode(value.first), true};  // insert and find
  } else {
    return {this->findNode(value.first), false};
  }
};

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  if (!this->contains(key)) {
    this->Insert(key, obj);
    return {this->findNode(key), true};  // insert and find
  } else {
    return {this->findNode(key), false};
  }
};

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  if (!this->contains(key)) {
    this->Insert(key, obj);
    return {this->findNode(key), true};
  } else {
    return {this->updateNode(key, obj), false};
  }
};

template <typename Key, typename T>
bool map<Key, T>::empty() {
  if (this->begin() == nullptr) {
    return true;
  } else {
    return false;
  }
};

template <typename Key, typename T>
void map<Key, T>::clear() {
  this->deleteTree(this->root);
  this->root = nullptr;
};

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  size_t Size = 0;
  for (auto it = this->begin(); it != this->end(); it++) {
    Size++;
  }
  return Size;
};

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const {
  return (std::numeric_limits<size_type>::max() /
          sizeof(typename RBtree<Key, T>::Node));
};

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  std::swap(this->root, other.root);
};

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  this->remove(pos->first);
};

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  if (other.empty()) return;

  for (auto it = other.begin(); it != other.end();) {
    auto check = this->insert(it->first, it->second);
    if (check.second) {
      other.erase(it++);
      continue;
    }
    ++it;
  }
};
