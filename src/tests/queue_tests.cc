#include <gtest/gtest.h>

#include <queue>

#include "../containers/queue/s21_queue.h"

// constructor

TEST(queue_constructor, 1) {
  s21::Queue<int> v1;
  std::queue<int> v2;

  EXPECT_EQ(v1.empty(), v2.empty());
}

TEST(queue_constructor, 2) {
  s21::Queue<int> v1({5, 1, 4, 24});
  std::queue<int> v2({5, 1, 4, 24});

  EXPECT_EQ(v1.back(), v2.back());
}

TEST(queue_constructor, 3) {
  s21::Queue<int> v1({5, 1, 4, 24});
  std::queue<int> v2({5, 1, 4, 24});

  s21::Queue<int> t1(v1);
  std::queue<int> t2(v2);

  EXPECT_EQ(v1.size(), t2.size());
}

TEST(queue_constructor, 4) {
  s21::Queue<int> v1({5, 1, 4, 24});
  std::queue<int> v2({5, 1, 4, 24});

  s21::Queue<int> t1(v1);
  std::queue<int> t2(v2);

  EXPECT_EQ(t1.back(), v2.back());
}

TEST(queue_constructor, 5) {
  s21::Queue<int> v1({5});
  std::queue<int> v2({5});

  EXPECT_EQ(v1.size(), v2.size());
}

TEST(queue_constructor, 6) {
  s21::Queue<int> v1({5, 1, 4, 24});
  std::queue<int> v2({5, 1, 4, 24});

  s21::Queue<int> t1({std::move(v1)});
  std::queue<int> t2({std::move(v2)});

  EXPECT_EQ(t1.size(), t2.size());
  EXPECT_EQ(t1.empty(), t2.empty());
}

TEST(queue_operator, 1) {
  s21::Queue<int> tc1{1, 2, 3, 4};

  s21::Queue<int> v1({1, 2, 3, 4});
  s21::Queue<int> v2({2, 2, 2, 2, 3, 4});

  v1 = std::move(v2);

  EXPECT_EQ(v1.empty(), tc1.empty());
}

// access

TEST(queue_access, 1) {
  s21::Queue<int> v1({31, 54, 11, 45, 7, 44});
  std::queue<int> v2({31, 54, 11, 45, 7, 44});

  EXPECT_EQ(v1.front(), v2.front());
}

TEST(queue_access, 2) {
  s21::Queue<int> v1({31, 54, 11, 45, 7, 44});
  std::queue<int> v2({31, 54, 11, 45, 7, 44});

  s21::Queue<int> t1(v1);
  std::queue<int> t2(v2);

  EXPECT_EQ(t1.back(), t2.back());
}

TEST(queue_access, 4) {
  s21::Queue<int> v1({31, 54, 11, 45, 7, 44});
  std::queue<int> v2({31, 54, 11, 45, 7, 44});

  EXPECT_EQ(v1.front(), v2.front());
}

TEST(queue_access, 5) {
  s21::Queue<int> v1({31, 54, 11, 45, 7, 44});
  std::queue<int> v2({31, 54, 11, 45, 7, 44});

  s21::Queue<int> t1(v1);
  std::queue<int> t2(v2);

  EXPECT_EQ(t1.back(), t2.back());
}

// capacity

TEST(queue_capacity, 1) {
  s21::Queue<int> v1;
  std::queue<int> v2;

  EXPECT_EQ(v1.empty(), v2.empty());
}

TEST(queue_capacity, 2) {
  s21::Queue<int> v1({11, 22, 33, 44, 55});
  std::queue<int> v2({11, 22, 33, 44, 55});

  EXPECT_EQ(v1.empty(), v2.empty());
}

TEST(queue_capacity, 3) {
  s21::Queue<int> v1({11, 22, 33, 44, 55});
  std::queue<int> v2({11, 22, 33, 44, 55});

  EXPECT_EQ(v1.size(), v2.size());
}

TEST(queue_capacity, 5) {
  s21::Queue<int> v1;
  std::queue<int> v2;

  for (auto i = 0; i < 111; i++) {
    v1.push(i);
    v2.push(i);
    EXPECT_EQ(v1.size(), v2.size());
  }
}

// modifiers

TEST(queue_modifiers, 1) {
  s21::Queue<int> v1({11, 22, 33, 44, 55});
  std::queue<int> v2({11, 22, 33, 44, 55});

  int last = 10;
  v1.push(last);
  v2.push(last);

  EXPECT_EQ(v1.back(), v2.back());
}

TEST(queue_modifiers, 2) {
  s21::Queue<int> v1({11, 22, 33, 44, 55});
  std::queue<int> v2({11, 22, 33, 44, 55});

  EXPECT_EQ(v1.front(), v2.front());

  for (size_t i = 0; i < v1.size(); i++) {
    v1.pop();
    v2.pop();
    EXPECT_EQ(v1.front(), v2.front());
  }
}

TEST(queue_modifiers, 3) {
  s21::Queue<int> v1({1, 2, 3, 4});
  s21::Queue<int> v2({4, 3, 2, 1});
  s21::Queue<int> tc({4, 3, 2, 1});

  std::queue<int> tc1({4, 3, 2, 1});
  v1.swap(v2);

  ASSERT_EQ(v1.front(), tc.front());
  ASSERT_EQ(v1.front(), tc1.front());
}

TEST(queue_modifiers, 5) {
  s21::Queue<int> v1({11, 22, 33, 44, 55});
  std::queue<int> v2({11, 22, 33, 44, 55});

  EXPECT_EQ(v1.front(), v2.front());

  while (!v1.empty() && !v2.empty()) {
    v1.pop();
    v2.pop();
    if (!v1.empty() && !v2.empty()) {
      EXPECT_EQ(v1.front(), v2.front());
    }
  }
}

TEST(queue_insert_many_back, 1) {
  s21::Queue<int> v1 = {1, 2, 3};
  s21::Queue<int> v2 = {1, 2, 3, 1, 2, 3, 5, 1, 4};

  v1.insert_many_back(1, 2, 3, 5, 1, 4);

  size_t size = v1.size();

  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(v1.front(), v2.front());
    v1.pop();
    v2.pop();
  }
}