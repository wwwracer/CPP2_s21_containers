#include "s21_vector.h"

using namespace s21;

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return array_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return array_ + size_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return array_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return array_ + size_;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::exception();
  return array_[pos];
}

template <typename T>
bool Vector<T>::empty() const {
  return begin() == end();
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& v) {
  if (this == &v) return *this;
  deallocate();
  capacity_ = v.capacity_;
  size_ = v.size_;
  array_ = v.array_;

  v.size_ = 0;
  v.capacity_ = 0;
  v.array_ = nullptr;

  return *this;
}

template <typename T>
void Vector<T>::deallocate() {
  if (array_ == nullptr) return;

  delete[] array_;
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return array_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return array_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return array_[size_ - 1];
}

template <typename T>
T* Vector<T>::data() {
  return array_;
}

template <typename T>
void Vector<T>::clear() {
  for (size_type i = 0; i < size_; i++) array_[i] = T();

  size_ = 0;
}

template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size > max_size()) throw std::exception();
  if (size <= capacity_) return;

  value_type* newArray = new value_type[size];
  for (size_type i = 0; i < size_; i++) newArray[i] = array_[i];
  for (size_type i = size_; i < size; i++) newArray[i] = value_type();

  deallocate();

  capacity_ = size;
  array_ = newArray;
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (size_ == 0) reserve(1);
  if (size_ == capacity_) reserve(capacity_ * 2);

  array_[size_] = value;
  size_++;
}

template <typename T>
void Vector<T>::pop_back() {
  size_--;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (size_ == capacity_) return;
  value_type* newArray = new value_type[size_];

  for (size_type i = 0; i < size_; i++) {
    newArray[i] = array_[i];
  }

  deallocate();
  array_ = newArray;
  capacity_ = size_;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  size_type index = static_cast<size_type>(pos - array_);

  for (size_type i = index; i < size_ - 1; ++i)
    array_[i] = std::move(array_[i + 1]);

  size_--;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = static_cast<size_type>(pos - array_);

  if (size_ == 0) reserve(1);
  if (size_ == capacity_) reserve(capacity_ * 2);

  for (size_type i = size_; i > index; i--)
    array_[i] = std::move(array_[i - 1]);

  array_[index] = value;
  size_++;

  return array_ + index;
}

template <typename T>
void Vector<T>::swap(Vector& other) {
  std::swap(array_, other.array_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  size_type index = static_cast<size_type>(pos - array_);

  (insert(begin() + index, std::forward<Args>(args)), ...);

  return begin() + index;
}

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args&&... args) {
  insert_many(end(), args...);
}
