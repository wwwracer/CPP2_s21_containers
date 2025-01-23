#pragma once

template <typename T>
struct Node {
  T data;
  Node* next = nullptr;
  Node* prev = nullptr;

  Node(const T& value) : data(value) {}
};