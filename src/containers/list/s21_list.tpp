#include "s21_list.h"

using namespace s21;

template <typename T>
typename List<T>::size_type List<T>::size() {
  return size_;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
bool List<T>::empty() {
  return size_ == 0;
}

template <typename T>
void List<T>::clear() {
  if (head_ == nullptr) {
    if (fake_ != nullptr) delete fake_;
    return;
  }

  Node<T>* current = head_;

  while (current != nullptr) {
    Node<T>* next = current->next;
    delete current;

    current = next;
  }

  head_ = nullptr;
  tail_ = nullptr;
  fake_ = nullptr;

  size_ = 0;
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return empty() ? end() : iterator(head_);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(fake_);
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const {
  return size_ == 0 ? cend() : const_iterator(head_);
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const {
  return const_iterator(fake_);
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  Node<T>* newNode = new Node<T>(value);

  if (fake_ == nullptr) fake_ = new Node<T>(T());

  if (empty()) {
    head_ = newNode;
    tail_ = head_;

    tail_->next = fake_;
    fake_->prev = tail_;
  } else if (pos == begin()) {
    newNode->next = head_;
    head_->prev = newNode;

    head_ = newNode;
  } else if (pos == end()) {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;

    tail_->next = fake_;
    fake_->prev = tail_;
  } else {
    Node<T>* current = pos.getNode();
    newNode->prev = current->prev;
    newNode->next = current;

    current->prev->next = newNode;
    current->prev = newNode;
  }

  size_++;
  return iterator(newNode);
}

template <typename T>
typename List<T>::size_type List<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node<T>) / 2;
}

template <typename T>
typename List<T>::const_reference List<T>::front() {
  return *begin();
}

template <typename T>
typename List<T>::const_reference List<T>::back() {
  return tail_->data;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (empty() || pos == end()) return;

  Node<T>* current = pos.getNode();

  if (size_ == 1) {
    clear();
    return;
  }

  Node<T>* next = current->next;
  Node<T>* prev = current->prev;

  if (pos == begin()) {
    next->prev = nullptr;
    head_ = next;
  } else {
    next->prev = prev;
    prev->next = next;

    if (current == tail_) tail_ = current->prev;
  }

  delete current;
  size_--;
}

template <typename T>
void List<T>::pop_back() {
  erase(tail_);
}

template <typename T>
void List<T>::pop_front() {
  erase(head_);
}

template <typename T>
void List<T>::reverse() {
  Node<T>* leftPtr = head_;
  Node<T>* rightPtr = tail_;

  for (size_t i = 0; i < size_ / 2; i++) {
    std::swap(leftPtr->data, rightPtr->data);
    leftPtr = leftPtr->next;
    rightPtr = rightPtr->prev;
  }
}

template <typename T>
void List<T>::swap(List& other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->fake_, other.fake_);
  std::swap(this->size_, other.size_);
}

template <typename T>
List<T>& List<T>::operator=(List&& v) {
  if (this == &v) return *this;
  clear();
  head_ = v.head_;
  tail_ = v.tail_;
  fake_ = v.fake_;
  size_ = v.size_;

  v.head_ = nullptr;
  v.tail_ = nullptr;
  v.fake_ = nullptr;
  v.size_ = 0;

  return *this;
}

template <typename T>
void List<T>::unique() {
  if (size() == 0) return;

  auto leftIter = begin();
  auto rightIter = leftIter;
  rightIter++;

  while (leftIter != end() && rightIter != end()) {
    while (*leftIter == *rightIter && rightIter != end()) {
      auto tmp = rightIter;
      tmp++;

      erase(rightIter);
      rightIter = tmp;
    }

    leftIter++;
    rightIter = leftIter;
    rightIter++;
  }
}

template <typename T>
void List<T>::merge(List& other) {
  if (other.empty()) return;

  auto iter = other.begin();
  while (iter != other.end()) push_back(*iter++);

  other.clear();
}

template <typename T>
void List<T>::splice(const_iterator pos, List& other) {
  if (other.empty()) return;

  if (empty()) {
    *this = std::move(other);
    return;
  }

  auto iter = other.begin();
  while (iter != other.end()) insert(pos, *iter++);
  other.clear();
}

template <typename T>
void List<T>::sort() {
  if (size_ < 2) return;

  List<T> left;
  List<T> right;

  auto mid = begin();
  for (size_t i = 0; i < size_ / 2; i++) {
    left.push_back(*mid);
    mid++;
  }

  while (mid != end()) {
    right.push_back(*mid);
    mid++;
  }

  left.sort();
  right.sort();

  mergeSort(left, right);
}

template <typename T>
void List<T>::mergeSort(List<T>& left, List<T>& right) {
  clear();

  auto leftIter = left.begin();
  auto rightIter = right.begin();

  while (leftIter != left.end() && rightIter != right.end()) {
    if (*leftIter < *rightIter) {
      push_back(*leftIter);
      leftIter++;
    } else {
      push_back(*rightIter);
      rightIter++;
    }
  }

  while (leftIter != left.end()) {
    push_back(*leftIter);
    leftIter++;
  }

  while (rightIter != right.end()) {
    push_back(*rightIter);
    rightIter++;
  }
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it = iterator(pos);

  (insert(it, std::forward<Args>(args)), ...);

  return it;
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args&&... args) {
  (push_front(std::forward<Args>(args)), ...);
}