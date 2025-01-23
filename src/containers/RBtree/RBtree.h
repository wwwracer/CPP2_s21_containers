#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

enum Color { RED, BLACK };

template <typename K, typename D>
class RBtree {
 protected:
  struct Node {
    K key_;
    D data_;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    Node(K key, D data)
        : key_(key),
          data_(data),
          color(RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  Node *root;

  Node *copyTree(const Node *node, Node *parent = nullptr) {
    if (!node) return nullptr;
    Node *newNode = new Node(node->key_, node->data_);
    newNode->color = node->color;
    newNode->parent = parent;
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
  }

  void deleteTree(Node *node);

  class RBtreeIterator {
   public:
    RBtreeIterator() : currentNode(nullptr) {}
    RBtreeIterator(Node *rootNode) : currentNode(rootNode) {}
    // Оператор разыменования
    K &operator*() const { return currentNode->key_; }
    // Оператор доступа
    K *operator->() const { return currentNode->key_; }
    // Постфиксный оператор инкремента
    RBtreeIterator operator++(int) {
      RBtreeIterator temp = *this;
      ++(*this);
      return temp;
    }
    // Префекстный оператор инкремента
    RBtreeIterator &operator++() {
      currentNode = next(currentNode);
      return *this;
    }
    // Оператор сравнения
    bool operator==(const RBtreeIterator &other) const {
      return currentNode == other.currentNode;
    }
    bool operator!=(const RBtreeIterator &other) const {
      return currentNode != other.currentNode;
    }

   private:
    Node *currentNode;

    Node *next(Node *node);
  };
  class RBtreeConstIterator {
   public:
    RBtreeConstIterator() : currentNode(nullptr) {}
    RBtreeConstIterator(Node *rootNode) : currentNode(rootNode) {}
    // Оператор разыменования
    const K &operator*() const { return currentNode->key_; }
    // Оператор доступа
    const K *operator->() const { return currentNode->key_; }
    // Префиксный оператор инкремента
    RBtreeConstIterator &operator++() {
      currentNode = next(currentNode);
      return *this;
    }
    // Постфиксный оператор инкремента
    RBtreeConstIterator operator++(int) {
      RBtreeConstIterator temp = *this;
      ++(*this);
      return temp;
    }
    // Оператор сравнения
    bool operator==(const RBtreeConstIterator &other) const {
      return currentNode == other.currentNode;
    }
    bool operator!=(const RBtreeConstIterator &other) const {
      return currentNode != other.currentNode;
    }

   private:
    Node *currentNode;
    Node *next(Node *node);
  };

 private:
  void rotateLeft(Node *&node);
  void rotateRight(Node *&node);
  void fixInsert(Node *&node);
  Node *minValueNode(Node *&node);
  void transplant(Node *&root, Node *&u, Node *&v);

 public:
  using iterator = RBtreeIterator;
  using const_iterator = RBtreeConstIterator;
  // Конструктор
  RBtree() : root(nullptr) {}
  // Конструктор копирования
  RBtree(const RBtree &other) { root = copyTree(other.root); }
  // Конструктор переноса
  RBtree(RBtree &&other) noexcept : root(other.root) { other.root = nullptr; }
  // Деструктор
  ~RBtree() { deleteTree(root); }
  D &find(K key);  // Сделать перегрузку на возвращение ссылки на ноду
  Node *findNode(K key);
  bool checkContain(K key);
  void remove(K key);
  void Insert(const K &key, const D &data);
  void InsertSet(const K &key);
  Node *updateNode(const K &key, const D &data);
  Node *InsertSetWithNode(const K &key);
};

#include "RBtree.tpp"
