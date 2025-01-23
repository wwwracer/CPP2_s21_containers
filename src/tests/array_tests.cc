#include <gtest/gtest.h>

#include <array>

#include "../containers/array/s21_array.h"

//
// Array()
//

TEST(array_constructor, 1) {
  s21::Array<int, 10> v1;

  ASSERT_EQ(v1.size(), 10);
}

TEST(array_constructor, 2) {
  s21::Array<int, 0> v1;

  ASSERT_EQ(v1.size(), 0);
}

TEST(array_constructor, 3) {
  s21::Array<int, 5> v1 = {1, 2, 3, 4, 5};
  std::array<int, 5> v2 = {1, 2, 3, 4, 5};

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v1[i], v2[i]);
  }
}

TEST(array_constructor, 4) {
  s21::Array<int, 50> v1 = {1, 2, 3, 4, 5};
  std::array<int, 50> v2 = {1, 2, 3, 4, 5};

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v1[i], v2[i]);
  }
}

TEST(array_constructor, 5) {
  s21::Array<int, 10> v1 = {};
  std::array<int, 10> v2 = {};

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v1[i], v2[i]);
  }
}

TEST(array_constructor, 6) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};

  s21::Array<int, 10> v1(init_list);
  s21::Array<int, 10> v1_copy(v1);

  std::array<int, 10> v2 = {1, 2, 3, 4, 5};
  std::array<int, 10> v2_copy(v2);

  ASSERT_EQ(v1_copy.size(), v2_copy.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1_copy[i], v2_copy[i]);
}

TEST(array_constructor, 7) {
  s21::Array<int, 5> v1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> v1_moved(std::move(v1));

  EXPECT_EQ(v1_moved.size(), 5);

  for (size_t i = 1; i <= v1_moved.size(); i++) EXPECT_EQ(v1_moved[i - 1], i);
}

//
// size()
//

TEST(array_size, 1) {
  s21::Array<int, 10> v1;

  ASSERT_EQ(v1.size(), 10);
}

TEST(array_size, 2) {
  s21::Array<int, 0> v1;

  ASSERT_EQ(v1.size(), 0);
}

TEST(array_size, 3) {
  s21::Array<int, 100> v1;

  ASSERT_EQ(v1.size(), 100);
}

//
// max_size()
//

TEST(array_max_size, 1) {
  s21::Array<int, 10> v1;

  ASSERT_EQ(v1.max_size(), v1.size());
}

TEST(array_max_size, 2) {
  s21::Array<int, 150> v1;

  ASSERT_EQ(v1.max_size(), v1.size());
}

TEST(array_max_size, 3) {
  s21::Array<int, 0> v1;

  ASSERT_EQ(v1.max_size(), v1.size());
}

//
// empty()
//

TEST(array_empty, 1) {
  s21::Array<int, 10> v1;

  ASSERT_FALSE(v1.empty());
}

TEST(array_empty, 2) {
  s21::Array<int, 0> v1;

  ASSERT_TRUE(v1.empty());
}

//
// data()
//

TEST(array_data, 1) {
  s21::Array<int, 10> v1;
  v1.data()[1] = 10;

  ASSERT_EQ(10, v1.data()[1]);
}

TEST(array_data, 2) {
  s21::Array<int, 10> v1;
  v1.data()[1] = 50;

  ASSERT_NE(10, v1.data()[1]);
}

//
// at()
//

TEST(array_at, 1) {
  s21::Array<int, 10> v1;

  ASSERT_EQ(v1.at(5), 0);
  v1.at(5) = 10;
  ASSERT_EQ(v1.at(5), 10);
}

TEST(array_at, 2) {
  s21::Array<int, 10> v1;

  ASSERT_THROW(v1.at(11), std::out_of_range);
}

//
// operators
//

TEST(array_operators, 1) {
  s21::Array<int, 10> v1;

  ASSERT_EQ(v1[5], 0);
  v1[5] = 10;
  ASSERT_EQ(v1[5], 10);
}

TEST(array_operators, 2) {
  s21::Array<int, 10> v1;

  ASSERT_NO_THROW(v1[20]);
}

TEST(array_operators, 3) {
  std::initializer_list<int> init_list_1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> init_list_2 = {6, 7, 8, 9, 10};

  s21::Array<int, 5> v1(init_list_1);
  s21::Array<int, 5> v2(init_list_2);

  v1 = std::move(v2);

  for (size_t i = 0; i < v1.size(); i++)
    EXPECT_EQ(v1[i], init_list_2.begin()[i]);
}

//
// begin()
//

TEST(array_begin, 1) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  s21::Array<int, 5> v1(init_list);

  for (size_t i = 0; i < init_list.size(); i++) {
    ASSERT_EQ(*(init_list.begin() + i), *(v1.begin() + i));
  }
}

//
// end()
//

TEST(array_end, 1) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  s21::Array<int, 5> v1(init_list);

  for (size_t i = 1; i <= init_list.size(); i++) {
    ASSERT_EQ(*(init_list.end() - i), *(v1.end() - i));
  }
}

TEST(array_end, 2) {
  s21::Array<int, 0> v1;

  ASSERT_EQ(v1.begin(), v1.end());
}

//
// front()
//

TEST(array_front, 1) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  s21::Array<int, 5> v1(init_list);

  ASSERT_EQ(v1.front(), 1);
}

TEST(array_front, 2) {
  std::initializer_list<int> init_list = {4};
  s21::Array<int, 5> v1(init_list);

  ASSERT_EQ(v1.front(), 4);
}

//
// back()
//

TEST(array_back, 1) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  s21::Array<int, 5> v1(init_list);

  ASSERT_EQ(v1.back(), 5);
}

TEST(array_back, 2) {
  std::initializer_list<int> init_list = {4};
  s21::Array<int, 1> v1(init_list);

  ASSERT_EQ(v1.back(), 4);
}

//
// fill()
//

TEST(array_fill, 1) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  s21::Array<int, 100> v1(init_list);

  v1.fill(4);

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v1.at(i), 4);
  }
}

TEST(array_fill, 2) {
  s21::Array<int, 100> v1;

  v1.fill(132);

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v1.at(i), 132);
  }
}

//
// swap()
//

TEST(array_swap, 1) {
  std::initializer_list<int> init_list_1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> init_list_2 = {6, 7, 8, 9, 10};

  s21::Array<int, 5> v1 = init_list_1;
  s21::Array<int, 5> v2 = init_list_2;

  v1.swap(v2);

  for (size_t i = 0; i < init_list_1.size(); i++) {
    ASSERT_EQ(v2[i], init_list_1.begin()[i]);
  }

  for (size_t i = 0; i < init_list_2.size(); i++) {
    ASSERT_EQ(v1[i], init_list_2.begin()[i]);
  }
}
