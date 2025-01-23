#include <gtest/gtest.h>

#include <vector>

#include "../containers/vector/s21_vector.h"

//
// vector()
//
TEST(vector_constructor, 0) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  ASSERT_EQ(v1.capacity(), v2.capacity());
  ASSERT_EQ(v1.size(), v2.size());
}

TEST(vector_constructor, 1) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  ASSERT_EQ(v1.capacity(), v2.capacity());
  ASSERT_EQ(v1.size(), v2.size());
}

TEST(vector_constructor, 2) {
  s21::Vector<int> v1(2);
  std::vector<int> v2(2);

  ASSERT_EQ(v1.capacity(), v2.capacity());
  ASSERT_EQ(v1.size(), v2.size());
}

TEST(vector_constructor, 3) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);
  std::vector<int> v2(initList);

  ASSERT_EQ(v1.capacity(), v2.capacity());
  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v2.size(); i++) ASSERT_EQ(v1.at(i), v2.at(i));
}

TEST(vector_constructor, 4) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);
  s21::Vector<int> v1_copy(v1);

  ASSERT_EQ(v1.capacity(), v1_copy.capacity());
  ASSERT_EQ(v1.size(), v1_copy.size());

  for (size_t i = 0; i < initList.size(); i++) {
    ASSERT_EQ(v1.at(i), v1_copy.at(i));
  }
}

TEST(vector_constructor, 5) {
  s21::Vector<int> v1;
  s21::Vector<int> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
}

TEST(vector_constructor, 6) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);
  s21::Vector<int> v1_copy(v1);
  s21::Vector<int> v2(std::move(v1));

  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.size(), 0);

  ASSERT_EQ(v2.size(), v1_copy.size());
  ASSERT_EQ(v2.capacity(), v1_copy.capacity());

  for (size_t i = 0; i < initList.size(); i++) {
    ASSERT_EQ(v2.at(i), v1_copy.at(i));
  }
}

//
// max_size
//

TEST(vector_max_size, 0) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector_max_size, 1) {
  s21::Vector<char> v1;
  std::vector<char> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector_max_size, 2) {
  s21::Vector<unsigned char> v1;
  std::vector<unsigned char> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector_max_size, 3) {
  s21::Vector<long long int> v1;
  std::vector<long long int> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector_max_size, 4) {
  s21::Vector<double> v1;
  std::vector<double> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

//
// at
//

TEST(vector_at, 0) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);

  size_t size = initList.size();

  ASSERT_ANY_THROW(v1.at(size + 1));
}

TEST(vector_at, 1) {
  s21::Vector<int> v1;

  ASSERT_ANY_THROW(v1.at(0));
  ASSERT_ANY_THROW(v1.at(1));
}

//
// begin
//

TEST(vector_begin, 0) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);
  std::vector<int> v2(initList);

  ASSERT_EQ(*v1.begin(), *v2.begin());
}

TEST(vector_begin, 1) {
  s21::Vector<int> v1(1);
  std::vector<int> v2(1);

  ASSERT_EQ(*v1.begin(), *v2.begin());
}

TEST(vector_begin, 2) {
  s21::Vector<int> v1;

  ASSERT_EQ(v1.begin(), v1.end());
}

//
// end
//

TEST(vector_end, 0) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);

  ASSERT_EQ(v1.at(initList.size() - 1), *(v1.end() - 1));
}

//
// operator=
//

TEST(vector_operator_mv, 0) {
  s21::Vector<int> v1;
  s21::Vector<int> v2 = std::move(v1);

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
}

TEST(vector_operator_mv, 1) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};

  s21::Vector<int> v1(initList);
  s21::Vector<int> v1_copy(v1);
  s21::Vector<int> v2 = std::move(v1);

  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.size(), 0);

  ASSERT_EQ(v2.size(), v1_copy.size());
  ASSERT_EQ(v2.capacity(), v1_copy.capacity());

  for (size_t i = 0; i < initList.size(); i++) {
    ASSERT_EQ(v2.at(i), v1_copy.at(i));
  }
}

//
// empty
//

TEST(vector_empty, 0) {
  s21::Vector<int> v1;

  ASSERT_TRUE(v1.empty());
}

TEST(vector_empty, 1) {
  s21::Vector<int> v1(1);

  ASSERT_FALSE(v1.empty());
}

//
// operator[]
//

TEST(vector_operator_get, 0) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};
  s21::Vector<int> v1(initList);

  for (size_t i = 0; i < initList.size(); i++) ASSERT_EQ(v1[i], i);
}

TEST(vector_operator_get, 1) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5};
  s21::Vector<int> v1(initList);

  for (size_t i = 0; i < initList.size(); i++) {
    v1[i] *= 2;

    ASSERT_EQ(v1[i], i * 2);
  }
}

//
// front
//

TEST(vector_front, 0) {
  std::initializer_list<int> initList = {6, 4, 5, 2, 1, 3};
  s21::Vector<int> v1(initList);

  ASSERT_EQ(v1.front(), 6);
}

TEST(vector_front, 1) {
  std::initializer_list<int> initList = {4};
  s21::Vector<int> v1(initList);

  ASSERT_EQ(v1.front(), 4);
}

//
// back
//

TEST(vector_back, 0) {
  std::initializer_list<int> initList = {6, 4, 5, 2, 1, 3};
  s21::Vector<int> v1(initList);

  ASSERT_EQ(v1.back(), 3);
}

TEST(vector_back, 1) {
  std::initializer_list<int> initList = {4};
  s21::Vector<int> v1(initList);

  ASSERT_EQ(v1.front(), 4);
}

//
// data
//

TEST(vector_data, 0) {
  std::initializer_list<int> initList = {6, 4, 5, 2, 1, 3};
  s21::Vector<int> v1(initList);
  int* arr = v1.data();

  for (size_t i = 0; i < initList.size(); i++) {
    ASSERT_EQ(arr[i], v1[i]);
  }
}

TEST(vector_data, 1) {
  std::initializer_list<int> initList = {3};
  s21::Vector<int> v1(initList);
  int* arr = v1.data();

  for (size_t i = 0; i < initList.size(); i++) {
    ASSERT_EQ(arr[i], v1[i]);
  }
}

//
// clear
//

TEST(vector_clear, 0) {
  std::initializer_list<int> initList = {6, 4, 5, 2, 1, 3};
  s21::Vector<int> v1(initList);

  v1.clear();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), initList.size());
}

TEST(vector_clear, 1) {
  std::initializer_list<int> initList = {6};
  s21::Vector<int> v1(initList);

  v1.clear();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), initList.size());
}

TEST(vector_clear, 2) {
  s21::Vector<int> v1;

  v1.clear();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
}

//
// reserve
//

TEST(vector_reserve, 0) {
  s21::Vector<int> v;
  v.reserve(10);
  ASSERT_EQ(v.capacity(), 10);
}

TEST(vector_reserve, 1) {
  s21::Vector<int> v;
  v.reserve(10);
  v.reserve(5);
  ASSERT_EQ(v.capacity(), 10);
}

TEST(vector_reserve, 2) {
  s21::Vector<int> v;
  ASSERT_ANY_THROW(v.reserve(v.max_size() + 1));
}

TEST(vector_reserve, 3) {
  s21::Vector<int> v;
  v.reserve(10);
  ASSERT_EQ(v.capacity(), 10);

  for (size_t i = 0; i < 10; ++i) ASSERT_EQ(v[i], 0);
}

//
// push_back
//

TEST(vector_push_back, 0) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  for (int i = 0; i < 10000; i++) {
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    v1.push_back(i);
    v2.push_back(i);
  }

  for (size_t i = 0; i < 10000; i++) ASSERT_EQ(v1[i], v2[i]);
}

//
// pop_back
//

TEST(vector_pop_back, 0) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  for (int i = 0; i < 10000; i++) {
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    v1.push_back(i);
    v2.push_back(i);
  }

  for (int h = 0; h < 10000; h++) {
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    v1.pop_back();
    v2.pop_back();
  }

  for (size_t i = 0; i < 10000; i++) {
    ASSERT_EQ(v1[i], v2[i]);
  }
}

//
// shrink_to_fit
//

TEST(vector_shrink_to_fit, 0) {
  s21::Vector<int> v1(100);
  std::vector<int> v2(100);

  v1.push_back(10);
  v2.push_back(10);

  v1.shrink_to_fit();
  v2.shrink_to_fit();

  ASSERT_EQ(v1.size(), v2.size());
  ASSERT_EQ(v1.capacity(), v2.capacity());
}

TEST(vector_shrink_to_fit, 1) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  v1.shrink_to_fit();
  v2.shrink_to_fit();

  ASSERT_EQ(v1.size(), v2.size());
  ASSERT_EQ(v1.capacity(), v2.capacity());
}

//
// erase
//

TEST(vector_erase, 0) {
  s21::Vector<int> v1;
  std::vector<int> v2;

  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    v1.push_back(i);
    v2.push_back(i);
  }

  for (size_t i = 0; i < 1000; i++) {
    if (i % 2) {
      v1.erase(v1.end());
      v2.erase(v2.end());
    } else {
      v1.erase(v1.begin());
      v2.erase(v2.begin());
    }

    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    for (size_t j = 0; j < v1.size(); j++) ASSERT_EQ(v1[j], v2[j]);
  }
}

//
// insert
//

TEST(vector_insert, 0) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  int* iter = nullptr;

  s21::Vector<int> v1 = initList;
  std::vector<int> v2 = initList;

  for (int i = 0; i < 1000; i++) {
    if (i % 2) {
      iter = v1.insert(v1.begin(), i);
      v2.insert(v2.begin(), i);
    } else {
      iter = v1.insert(v1.end(), i);
      v2.insert(v2.end(), i);
    }

    ASSERT_EQ(*iter, i);
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    for (size_t j = 0; j < v1.size(); j++) ASSERT_EQ(v1[j], v2[j]);
  }
}

TEST(vector_insert, 1) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};

  s21::Vector<int> v1 = initList;
  std::vector<int> v2 = initList;

  for (int i = 0; i < 100; i++) {
    auto iter1 = v1.insert(v1.begin(), i);
    auto iter2 = v2.insert(v2.begin(), i);

    ASSERT_EQ(*iter1, *iter2);
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    for (size_t j = 0; j < v1.size(); j++) ASSERT_EQ(v1[j], v2[j]);
  }
}

TEST(vector_insert, 2) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};

  s21::Vector<int> v1 = initList;
  std::vector<int> v2 = initList;

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (int i = 0; i < 100; i++) {
    iter1 = v1.insert(iter1++, i);
    iter2 = v2.insert(iter2++, i);

    ASSERT_EQ(*iter1, *iter2);
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v1.capacity(), v2.capacity());

    for (size_t j = 0; j < v1.size(); j++) ASSERT_EQ(v1[j], v2[j]);
  }
}

//
// swap
//

TEST(vector_swap, 0) {
  s21::Vector<int> v1 = {1, 2};
  s21::Vector<int> v1_copy = v1;

  s21::Vector<int> v2 = {4, 5, 6};
  s21::Vector<int> v2_copy = v2;

  v1.swap(v2);

  ASSERT_EQ(v1.size(), v2_copy.size());
  ASSERT_EQ(v2.size(), v1_copy.size());
}

//
// insert_many
//

TEST(vector_insert_many, 1) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {4, 1, 5, 3, 2, 1, 1, 2, 3};

  auto insertResult = v1.insert_many(v1.begin(), 1, 2, 3, 5, 1, 4);

  ASSERT_EQ(*insertResult, 4);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many, 2) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {4, 1, 2, 3};

  auto insertResult = v1.insert_many(v1.begin(), 4);

  ASSERT_EQ(*insertResult, 4);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many, 3) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {1, 2, 3, 4};

  auto insertResult = v1.insert_many(v1.end(), 4);

  ASSERT_EQ(*insertResult, 4);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many, 4) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {1, 2, 3, 6, 7, 5, 4};

  auto insertResult = v1.insert_many(v1.end(), 4, 5, 7, 6);

  ASSERT_EQ(*insertResult, 6);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

//
// insert_many_back
//

TEST(vector_insert_many_back, 1) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {1, 2, 3, 2, 1};

  v1.insert_many_back(1, 2);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many_back, 2) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {1, 2, 3, 4};

  v1.insert_many_back(4);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many_back, 3) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {1, 2, 3, 1, 4};

  v1.insert_many_back(4, 1);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many_back, 4) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {1, 2, 3, 6, 7, 5, 4};

  v1.insert_many_back(4, 5, 7, 6);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}

TEST(vector_insert_many_back, 5) {
  s21::Vector<int> v1;
  s21::Vector<int> v2 = {1, 2, 3};

  v1.insert_many_back(3, 2, 1);

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(v1[i], v2[i]);
}
