#include <gtest/gtest.h>

#include <stack>

#include "../containers/stack/s21_stack.h"

TEST(stack_constructor, 1) {
  s21::Stack<int> v1;
  std::stack<int> v2;

  EXPECT_EQ(v1.empty(), v2.empty());
}

TEST(stack_constructor, 2) {
  s21::Stack<int> v1({5, 1, 4, 24});
  std::stack<int> v2({5, 1, 4, 24});

  EXPECT_EQ(v1.size(), v2.size());
}

TEST(stack_constructor, 3) {
  s21::Stack<int> s21_stack{1, 2, 4};
  EXPECT_EQ(s21_stack.size(), 3);
  EXPECT_EQ(s21_stack.top(), 4);
}

TEST(stack_constructor, 4) {
  std::initializer_list<int> b;

  s21::Stack<int> s21_stack{b};
  std::stack<int> std_stack{b};

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack_constructor, 5) {
  std::initializer_list<int> tc1 = {1, 2, 3};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_copy{s21_stack};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_copy{std_stack};

  EXPECT_EQ(s21_stack_copy.size(), std_stack_copy.size());
  EXPECT_EQ(s21_stack_copy.top(), std_stack_copy.top());
}

TEST(stack_constructor, 6) {
  s21::Stack<int> v1({5, 1, 4, 24});
  std::stack<int> v2({5, 1, 4, 24});

  s21::Stack<int> t1({std::move(v1)});
  std::stack<int> t2({std::move(v2)});

  EXPECT_EQ(t1.size(), t2.size());
  EXPECT_EQ(t1.empty(), t2.empty());
}

TEST(stack_constructor, 7) {
  std::initializer_list<int> tc1 = {1, 2, 3};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_move{s21_stack};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_move{std_stack};

  EXPECT_EQ(s21_stack_move.size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.top(), std_stack_move.top());
}

TEST(stack_func, 1) {
  std::initializer_list<int> tc1 = {1, 2, 3};
  std::initializer_list<int> tc2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_move{tc2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_move{tc2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_func, 2) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};
  std::initializer_list<int> tc2 = {1, 2, 3};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_move{tc2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_move{tc2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_func, 3) {
  std::initializer_list<int> tc1;
  std::initializer_list<int> tc2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_move{tc2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_move{tc2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_access, 1) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};

  std::stack<int> std_stack{tc1};

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_capacity, 1) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack_capacity, 2) {
  std::initializer_list<int> tc1;

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack_capacity, 3) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack_capacity, 4) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack_modifiers, 1) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  s21_stack.push(1);
  std_stack.push(1);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_modifiers, 2) {
  std::initializer_list<int> tc1;

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  s21_stack.push(1);
  std_stack.push(1);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_modifiers, 3) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_modifiers, 4) {
  std::initializer_list<int> tc1;

  s21::Stack<int> s21_stack{tc1};
  std::stack<int> std_stack{tc1};

  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.size(), 0);
}

TEST(stack_modifiers, 5) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};
  std::initializer_list<int> tc2 = {1, 2, 3};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_swap{tc2};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_swap{tc2};

  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(stack_modifiers, 6) {
  std::initializer_list<int> tc1 = {1, 2, 3};
  std::initializer_list<int> tc2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_swap{tc2};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_swap{tc2};

  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(stack_modifiers, 7) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};
  std::initializer_list<int> tc2;

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_swap{tc2};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_swap{tc2};

  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(stack_modifiers, 8) {
  std::initializer_list<int> tc1;
  std::initializer_list<int> tc2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_swap{tc2};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_swap{tc2};

  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(stack_modifiers, 9) {
  std::initializer_list<int> tc1;
  std::initializer_list<int> tc2;

  s21::Stack<int> s21_stack{tc1};
  s21::Stack<int> s21_stack_swap{tc2};

  std::stack<int> std_stack{tc1};
  std::stack<int> std_stack_swap{tc2};

  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(stack_modifiers, 10) {
  std::initializer_list<int> tc1 = {4, 5, 6, 7};
  std::initializer_list<int> tc2 = {4, 5, 6, 7};

  s21::Stack<int> v1{tc1};
  s21::Stack<int> s21_stack_swap{tc2};

  std::stack<int> t1{tc1};
  std::stack<int> std_stack_swap{tc2};

  v1.swap(s21_stack_swap);
  t1.swap(std_stack_swap);

  EXPECT_EQ(v1.size(), t1.size());
  EXPECT_EQ(v1.top(), t1.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(stack_insert_many_back, 1) {
  s21::Stack<int> v1 = {1, 2, 3};
  s21::Stack<int> v2 = {1, 2, 3, 1, 2, 3, 5, 1, 4};

  v1.insert_many_back(1, 2, 3, 5, 1, 4);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1.top(), v2.top());
    v1.pop();
    v2.pop();
  }
}