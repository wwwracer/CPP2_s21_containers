#include "RBtree.h"

// Реализация методов
template <typename K, typename D>
void RBtree<K, D>::rotateLeft(Node *&node) {
  Node *child = node->right;
  node->right = child->left;
  if (node->right != nullptr) node->right->parent = node;
  child->parent = node->parent;
  if (node->parent == nullptr)
    root = child;
  else if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
  child->left = node;
  node->parent = child;
}

template <typename K, typename D>
void RBtree<K, D>::rotateRight(Node *&node) {
  Node *child = node->left;
  node->left = child->right;
  if (node->left != nullptr) node->left->parent = node;
  child->parent = node->parent;
  if (node->parent == nullptr)
    root = child;
  else if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
  child->right = node;
  node->parent = child;
}

template <typename K, typename D>
void RBtree<K, D>::fixInsert(Node *&node) {
  Node *parent = nullptr;
  Node *grandparent = nullptr;
  while (node != root && node->color == RED && node->parent->color == RED) {
    parent = node->parent;
    grandparent = parent->parent;
    if (parent == grandparent->left) {
      Node *uncle = grandparent->right;
      if (uncle != nullptr && uncle->color == RED) {
        grandparent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        node = grandparent;
      } else {
        if (node == parent->right) {
          rotateLeft(parent);
          node = parent;
          parent = node->parent;
        }
        rotateRight(grandparent);
        std::swap(parent->color, grandparent->color);
        node = parent;
      }
    } else {
      Node *uncle = grandparent->left;
      if (uncle != nullptr && uncle->color == RED) {
        grandparent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        node = grandparent;
      } else {
        if (node == parent->left) {
          rotateRight(parent);
          node = parent;
          parent = node->parent;
        }
        rotateLeft(grandparent);
        std::swap(parent->color, grandparent->color);
        node = parent;
      }
    }
  }
  root->color = BLACK;
}

template <typename K, typename D>
typename RBtree<K, D>::Node *RBtree<K, D>::minValueNode(Node *&node) {
  Node *current = node;
  while (current->left != nullptr) current = current->left;
  return current;
}

template <typename K, typename D>
void RBtree<K, D>::transplant(Node *&root, Node *&u, Node *&v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr) v->parent = u->parent;
}

// Public

template <typename K, typename D>
void RBtree<K, D>::Insert(const K &key, const D &data) {
  Node *node = new Node(key, data);
  Node *parent = nullptr;
  Node *current = root;
  while (current != nullptr) {
    parent = current;
    if (node->key_ < current->key_)
      current = current->left;
    else if (node->key_ >= current->key_)
      current = current->right;
  }
  node->parent = parent;
  if (parent == nullptr)
    root = node;
  else if (node->key_ < parent->key_)
    parent->left = node;
  else
    parent->right = node;
  fixInsert(node);
}

template <typename K, typename D>
void RBtree<K, D>::InsertSet(const K &key) {
  Node *node = new Node(key, 0);
  Node *parent = nullptr;
  Node *current = root;
  while (current != nullptr) {
    parent = current;
    if (node->key_ < current->key_)
      current = current->left;
    else if (node->key_ >= current->key_)
      current = current->right;
  }
  node->parent = parent;
  if (parent == nullptr)
    root = node;
  else if (node->key_ < parent->key_)
    parent->left = node;
  else
    parent->right = node;
  fixInsert(node);
}

template <typename K, typename D>
typename RBtree<K, D>::Node *RBtree<K, D>::InsertSetWithNode(const K &key) {
  Node *node = new Node(key, 0);
  Node *parent = nullptr;
  Node *current = root;
  while (current != nullptr) {
    parent = current;
    if (node->key_ < current->key_)
      current = current->left;
    else if (node->key_ >= current->key_)
      current = current->right;
  }
  node->parent = parent;
  if (parent == nullptr)
    root = node;
  else if (node->key_ < parent->key_)
    parent->left = node;
  else
    parent->right = node;
  fixInsert(node);

  Node *result = root;
  while (result != nullptr) {
    if (key == result->key_)
      break;
    else if (key < result->key_)
      result = result->left;
    else
      result = result->right;
  }
  return result;  // Более правильный вывод ноды
}

template <typename K, typename D>
void RBtree<K, D>::remove(K key) {
  Node *node = root;
  Node *z = nullptr;
  Node *x = nullptr;
  Node *y = nullptr;
  while (node != nullptr) {
    if (node->key_ == key) {
      z = node;
    }
    if (node->key_ <= key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }
  if (z == nullptr) {
    return;  // key not found
  }
  y = z;
  if (z->left == nullptr) {
    x = z->right;
    transplant(root, z, z->right);
  } else if (z->right == nullptr) {
    x = z->left;
    transplant(root, z, z->left);
  } else {
    y = minValueNode(z->right);
    x = y->right;
    if (y->parent == z) {
      if (x != nullptr) x->parent = y;
    } else {
      transplant(root, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
}

template <typename K, typename D>
void RBtree<K, D>::deleteTree(Node *node) {
  if (node != nullptr) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

template <typename K, typename D>
D &RBtree<K, D>::find(K key) {
  Node *current = root;

  while (current != nullptr) {
    if (key == current->key_) {
      return current->data_;
    } else if (key < current->key_) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  throw std::out_of_range("Key not found");
}

template <typename K, typename D>
typename RBtree<K, D>::Node *RBtree<K, D>::findNode(K key) {
  Node *current = root;

  while (current != nullptr) {
    if (key == current->key_) {
      return current;
    } else if (key < current->key_) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  throw std::out_of_range("Key not found");
}

template <typename K, typename D>
bool RBtree<K, D>::checkContain(K key) {
  try {
    find(key);
    return true;
  } catch (const std::out_of_range &) {
    return false;
  }
}

template <typename K, typename D>
typename RBtree<K, D>::Node *RBtree<K, D>::updateNode(const K &key,
                                                      const D &data) {
  Node *current = this->findNode(key);
  current->data_ = data;
  return current;
}

template <typename K, typename D>
typename RBtree<K, D>::Node *RBtree<K, D>::RBtreeIterator::next(Node *node) {
  // Реализация остается той же
  if (node == nullptr) return nullptr;

  if (node->right) {
    node = node->right;
    while (node->left) {
      node = node->left;
    }
    return node;
  } else {
    Node *parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }
}

template <typename K, typename D>
typename RBtree<K, D>::Node *RBtree<K, D>::RBtreeConstIterator::next(
    Node *node) {
  if (node->right) {
    node = node->right;
    while (node->left) {
      node = node->left;
    }
  } else {
    Node *parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return node;
}
