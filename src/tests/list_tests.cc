#include <gtest/gtest.h>

#include <list>

#include "../containers/list/s21_list.h"

//
// constructor
//

TEST(list_constructor, 1) {
  s21::List<int> v1;
  std::list<int> v2;

  v1.push_back(1);
}

TEST(list_constructor, 2) {
  s21::List<int> v1(10);
  std::list<int> v2(10);

  ASSERT_EQ(v1.size(), v2.size());
}

TEST(list_constructor, 3) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};

  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_constructor, 4) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};

  s21::List<int> v1(initList);
  s21::List<int> v1_copy(v1);

  auto iter1 = v1.begin();
  auto iter2 = v1_copy.begin();

  ASSERT_EQ(v1.size(), v1_copy.size());
  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_constructor, 5) {
  std::initializer_list<int> initList = {1, 2};

  s21::List<int> v1(initList);
  s21::List<int> v1_copy(v1);

  auto iter1 = v1.begin();
  auto iter2 = v1_copy.begin();

  ASSERT_EQ(v1.size(), v1_copy.size());
  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_constructor, 6) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};

  s21::List<int> v1(initList);
  s21::List<int> v1_moved = std::move(v1);

  ASSERT_TRUE(v1.empty());

  auto listIter = v1_moved.begin();
  auto initIter = initList.begin();

  for (size_t i = 0; i < initList.size(); i++) {
    ASSERT_EQ(*listIter++, *initIter++);
  }
}

TEST(list_constructor, 7) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};

  s21::List<int> v1(initList);
  s21::List<int> v1_copy = v1;

  auto iter1 = v1.begin();
  auto iter2 = v1_copy.begin();

  ASSERT_EQ(v1.size(), v1_copy.size());
  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_constructor, 8) {
  std::initializer_list<int> initList = {1, 2};

  s21::List<int> v1(initList);
  s21::List<int> v1_copy = v1;

  auto iter1 = v1.begin();
  auto iter2 = v1_copy.begin();

  ASSERT_EQ(v1.size(), v1_copy.size());
  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

//
// size
//

TEST(list_size, 1) {
  s21::List<int> v1;
  std::list<int> v2;

  ASSERT_EQ(v1.size(), v2.size());

  for (int i = 0; i < 100; i++) {
    v1.push_back(i);
    v2.push_back(i);
    ASSERT_EQ(v1.size(), v2.size());
  }
}

//
// clear
//

TEST(list_clear, 1) {
  s21::List<int> v1;
  v1.push_back(1);
  v1.clear();

  ASSERT_EQ(v1.size(), 0);
}

//
// empty
//

TEST(list_empty, 1) {
  s21::List<int> v1;
  ASSERT_TRUE(v1.empty());
}

TEST(list_empty, 2) {
  s21::List<int> v1;
  v1.push_back(1);
  ASSERT_FALSE(v1.empty());
}

TEST(list_empty, 3) {
  s21::List<int> v1;
  v1.push_back(1);
  v1.clear();
  ASSERT_TRUE(v1.empty());
}

//
// push_back
//

TEST(list_push_back, 1) {
  s21::List<int> v1;
  std::list<int> v2;

  for (int i = 0; i < 100; i++) {
    v1.push_back(i);
    v2.push_back(i);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (int i = 0; i < 100; i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_push_back, 2) {
  s21::List<int> v1;
  std::list<int> v2;

  for (int i = 0; i < 131; i++) {
    v1.push_back(i);
    v2.push_back(i);
  }

  ASSERT_EQ(v1.size(), v2.size());
}

//
// push_front
//

TEST(list_push_front, 1) {
  s21::List<int> v1;
  std::list<int> v2;

  for (int i = 0; i < 100; i++) {
    v1.push_front(i);
    v2.push_front(i);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (int i = 0; i < 100; i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_push_front, 2) {
  s21::List<int> v1;
  std::list<int> v2;

  for (int i = 0; i < 131; i++) {
    v1.push_front(i);
    v2.push_front(i);
  }

  ASSERT_EQ(v1.size(), v2.size());
}

//
// begin
//

TEST(list_begin, 1) {
  s21::List<int> v1;

  for (int i = 5; i < 10; i++) v1.push_back(10);

  ASSERT_EQ(*v1.begin(), 10);
}

TEST(list_begin, 2) {
  s21::List<int> v1;

  ASSERT_EQ(v1.begin(), v1.end());
}

//
// end
//

TEST(list_end, 1) {
  s21::List<int> v1 = {1};

  ASSERT_EQ(*(--v1.end()), 1);
}

//
// cbegin
//

TEST(list_cbegin, 1) {
  s21::List<int> v1;

  for (int i = 5; i < 10; i++) v1.push_back(10);

  ASSERT_EQ(*v1.cbegin(), 10);
}

TEST(list_cbegin, 2) {
  s21::List<int> v1;

  ASSERT_EQ(v1.cbegin(), v1.cend());
}

//
// cend
//

TEST(list_cend, 1) {
  s21::List<int> v1 = {1};

  ASSERT_EQ(*(--v1.cend()), 1);
}

//
// insert
//

TEST(list_insert, 1) {
  s21::List<int> v1 = {1, 2, 3};
  std::list<int> v2 = {1, 2, 3};

  for (int i = 0; i < 10; i++) {
    auto insertResult1 = v1.insert(v1.begin(), i);
    auto insertResult2 = v2.insert(v2.begin(), i);

    ASSERT_EQ(*insertResult1, *insertResult2);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert, 2) {
  s21::List<int> v1 = {1, 2, 3};
  std::list<int> v2 = {1, 2, 3};

  for (int i = 0; i < 10; i++) {
    auto insertResult1 = v1.insert(v1.end(), i);
    auto insertResult2 = v2.insert(v2.end(), i);

    ASSERT_EQ(*insertResult1, *insertResult2);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert, 3) {
  s21::List<int> v1;
  std::list<int> v2;

  for (int i = 0; i < 10; i++) {
    auto insertResult1 = v1.insert(v1.begin(), i);
    auto insertResult2 = v2.insert(v2.begin(), i);

    ASSERT_EQ(*insertResult1, *insertResult2);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert, 4) {
  s21::List<int> v1;
  std::list<int> v2;

  for (int i = 0; i < 10; i++) {
    auto insertResult1 = v1.insert(v1.end(), i);
    auto insertResult2 = v2.insert(v2.end(), i);

    ASSERT_EQ(*insertResult1, *insertResult2);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert, 5) {
  s21::List<int> v1 = {1, 2, 3};
  std::list<int> v2 = {1, 2, 3};

  for (int i = 0; i < 10; i++) {
    auto insertResult1 = v1.insert(++v1.begin(), i);
    auto insertResult2 = v2.insert(++v2.begin(), i);

    ASSERT_EQ(*insertResult1, *insertResult2);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert, 6) {
  s21::List<int> v1 = {1, 2, 3};
  std::list<int> v2 = {1, 2, 3};

  for (int i = 0; i < 10; i++) {
    auto insertResult1 = v1.insert(--v1.end(), i);
    auto insertResult2 = v2.insert(--v2.end(), i);

    ASSERT_EQ(*insertResult1, *insertResult2);
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

//
// max_size
//

TEST(list_max_size, 1) {
  s21::List<int> v1;
  std::list<int> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(list_max_size, 2) {
  s21::List<int> v1 = {1, 2, 3};
  std::list<int> v2 = {1, 2, 3};

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(list_max_size, 3) {
  s21::List<char> v1;
  std::list<char> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(list_max_size, 4) {
  s21::List<long long int> v1;
  std::list<long long int> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}
TEST(list_max_size, 5) {
  s21::List<double> v1;
  std::list<double> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(list_max_size, 6) {
  s21::List<float> v1;
  std::list<float> v2;

  ASSERT_EQ(v1.max_size(), v2.max_size());
}

//
// front
//

TEST(list_front, 1) {
  s21::List<int> v1 = {1, 2, 3};

  ASSERT_EQ(v1.front(), 1);
}

TEST(list_front, 2) {
  s21::List<int> v1 = {3};

  ASSERT_EQ(v1.front(), 3);
}

TEST(list_front, 3) {
  s21::List<int> v1 = {5, 1, 7, 2, 8, 21};

  ASSERT_EQ(v1.front(), 5);
}

//
// back
//

TEST(list_back, 1) {
  s21::List<int> v1 = {1, 2, 3};

  ASSERT_EQ(v1.back(), 3);
}

TEST(list_back, 2) {
  s21::List<int> v1 = {3};

  ASSERT_EQ(v1.back(), 3);
}

TEST(list_back, 3) {
  s21::List<int> v1 = {5, 1, 7, 2, 8, 21};

  ASSERT_EQ(v1.back(), 21);
}

//
// erase
//

TEST(list_erase, 1) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < v1.size(); i++) {
    v1.erase(v1.begin());
    v2.erase(v2.begin());
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_erase, 2) {
  s21::List<int> v1 = {1};

  v1.erase(--v1.end());

  ASSERT_TRUE(v1.empty());
}

TEST(list_erase, 3) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 4; i++) {
    v1.erase(--v1.end());
    v2.erase(--v2.end());
  }

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_erase, 4) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 5; i++) v1.erase(--v1.end());

  ASSERT_TRUE(v1.empty());
}

//
// pop_back
//

TEST(list_pop_back, 1) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 4; i++) {
    v1.pop_back();
    v2.pop_back();

    auto iter1 = v1.begin();
    auto iter2 = v2.begin();

    for (size_t j = 0; j < v1.size(); j++) {
      ASSERT_EQ(*iter1++, *iter2++);
    }
  }
}

TEST(list_pop_back, 2) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 5; i++) {
    v1.pop_back();
    v2.pop_back();

    ASSERT_EQ(v1.size(), v2.size());
  }
}

//
// pop_front
//

TEST(list_pop_front, 1) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 4; i++) {
    v1.pop_front();
    v2.pop_front();

    auto iter1 = v1.begin();
    auto iter2 = v2.begin();

    for (size_t j = 0; j < v1.size(); j++) {
      ASSERT_EQ(*iter1++, *iter2++);
    }
  }
}

TEST(list_pop_front, 2) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 5; i++) {
    v1.pop_front();
    v2.pop_front();

    ASSERT_EQ(v1.size(), v2.size());
  }
}

//
// reverse
//

TEST(list_reverse, 1) {
  std::initializer_list<int> initList = {5, 3, 67, 3, 52, 3};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 4; i++) {
    v1.reverse();
    v2.reverse();

    auto iter1 = v1.begin();
    auto iter2 = v2.begin();

    for (size_t j = 0; j < v1.size(); j++) {
      ASSERT_EQ(*iter1++, *iter2++);
    }
  }
}

TEST(list_reverse, 2) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5, 6, 7};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  for (size_t i = 0; i < 4; i++) {
    v1.reverse();
    v2.reverse();

    auto iter1 = v1.begin();
    auto iter2 = v2.begin();

    for (size_t j = 0; j < v1.size(); j++) {
      ASSERT_EQ(*iter1++, *iter2++);
    }
  }
}

//
// swap
//

TEST(list_swap, 1) {
  std::initializer_list<int> initList1 = {1, 2, 3, 4, 5, 6, 7};
  std::initializer_list<int> initList2 = {10, 11, 10, 9, 8};

  s21::List<int> v1(initList1);
  std::list<int> v1_std(initList1);

  s21::List<int> v2(initList2);
  std::list<int> v2_std(initList2);

  v1.swap(v2);
  v1_std.swap(v2_std);

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t j = 0; j < v1.size(); j++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }

  iter1 = v2.begin();
  iter2 = v2_std.begin();

  for (size_t j = 0; j < v1.size(); j++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_swap, 2) {
  std::initializer_list<int> initList1 = {1, 2, 3, 4, 5, 6, 7};
  std::initializer_list<int> initList2;

  s21::List<int> v1(initList1);
  std::list<int> v1_std(initList1);

  s21::List<int> v2(initList2);
  std::list<int> v2_std(initList2);

  v1.swap(v2);
  v1_std.swap(v2_std);

  auto iter1 = v2.begin();
  auto iter2 = v2_std.begin();

  for (size_t j = 0; j < v2.size(); j++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

//
// pop_front
//

TEST(list_unique, 1) {
  std::initializer_list<int> initList = {1, 2, 3, 4, 5, 4, 3, 2, 1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 2) {
  std::initializer_list<int> initList = {0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 3) {
  std::initializer_list<int> initList = {1, 1, 11,  1, 1, 2, 3, 2, 2, 3, 6,
                                         2, 4, 621, 2, 2, 3, 1, 2, 2, 3};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();
}

TEST(list_unique, 4) {
  std::initializer_list<int> initList = {1, 1, 11,  1, 1, 2, 3, 2, 2, 3, 6,
                                         2, 4, 621, 2, 2, 3, 1, 2, 2, 3, 3};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 5) {
  std::initializer_list<int> initList = {1, 1, 11,  1, 1, 2, 3, 2, 2, 3, 6,
                                         2, 4, 621, 2, 2, 3, 1, 2, 2, 3, 4};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 6) {
  std::initializer_list<int> initList;
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  ASSERT_EQ(v1.size(), v2.size());
}

TEST(list_unique, 7) {
  std::initializer_list<int> initList = {1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 8) {
  std::initializer_list<int> initList = {1, 1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 9) {
  std::initializer_list<int> initList = {1, 1, 1, 1, 1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_unique, 10) {
  std::initializer_list<int> initList = {1, 1, 1, 1, 1, 1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.unique();
  v2.unique();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

//
// merge
//

TEST(list_merge, 1) {
  std::initializer_list<int> init1 = {1, 2, 3};
  std::initializer_list<int> init2 = {3, 2, 1, 4, 2, 2, 5, 6};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.merge(v2);
  v1_std.merge(v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_merge, 2) {
  std::initializer_list<int> init1 = {1, 2, 3};
  std::initializer_list<int> init2 = {};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.merge(v2);
  v1_std.merge(v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_merge, 3) {
  std::initializer_list<int> init1 = {1};
  std::initializer_list<int> init2 = {2};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.merge(v2);
  v1_std.merge(v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_merge, 4) {
  std::initializer_list<int> init1 = {};
  std::initializer_list<int> init2 = {2, 5, 2};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.merge(v2);
  v1_std.merge(v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_merge, 5) {
  std::initializer_list<int> init1 = {};
  std::initializer_list<int> init2 = {};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.merge(v2);
  v1_std.merge(v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());
}

//
// splice
//

TEST(list_splice, 1) {
  std::initializer_list<int> init1 = {5, 6, 7, 8};
  std::initializer_list<int> init2 = {1, 2, 3, 4};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_splice, 2) {
  std::initializer_list<int> init1 = {5, 5, 3, 5, 1};
  std::initializer_list<int> init2 = {1, 2, 3, 4};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_splice, 3) {
  std::initializer_list<int> init1 = {5, 5, 3, 5, 1};
  std::initializer_list<int> init2 = {8, 3, 5, 1, 3};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_splice, 4) {
  std::initializer_list<int> init1 = {5, 5, 3, 5, 1};
  std::initializer_list<int> init2 = {};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_splice, 5) {
  std::initializer_list<int> init1 = {};
  std::initializer_list<int> init2 = {5, 4, 3, 5, 2};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}
TEST(list_splice, 6) {
  std::initializer_list<int> init1 = {5, 5, 3, 5, 1, 4};
  std::initializer_list<int> init2 = {};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}

TEST(list_splice, 7) {
  std::initializer_list<int> init1 = {};
  std::initializer_list<int> init2 = {5, 4, 3, 5, 2, 1};

  s21::List<int> v1 = init1;
  s21::List<int> v2 = init2;

  std::list<int> v1_std = init1;
  std::list<int> v2_std = init2;

  v1.splice(v1.cbegin(), v2);
  v1_std.splice(v1_std.cbegin(), v2_std);

  ASSERT_EQ(v1.size(), v1_std.size());
  ASSERT_EQ(v2.size(), v2_std.size());

  auto iter1 = v1.begin();
  auto iter2 = v1_std.begin();

  for (size_t i = 0; i < v1.size(); i++) ASSERT_EQ(*iter1++, *iter2++);
}

//
// sort()
//

TEST(list_sort, 1) {
  std::initializer_list<int> initList = {6, 5, 4, 3};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 2) {
  std::initializer_list<int> initList = {1, 2, 3};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 3) {
  std::initializer_list<int> initList = {67, 1, 3, 8, 32, 1, 2, 2};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 4) {
  std::initializer_list<int> initList = {67, 1, 3, 8, 32, 1, 2, 2, 3};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 5) {
  std::initializer_list<int> initList = {67, 1, 3, 8, 32, 1, 2, 2, 2};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 6) {
  std::initializer_list<int> initList = {1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 7) {
  std::initializer_list<int> initList = {1, 2};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 8) {
  std::initializer_list<int> initList = {2, 1};
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  ASSERT_EQ(v1.size(), v2.size());

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_sort, 9) {
  std::initializer_list<int> initList;
  s21::List<int> v1(initList);
  std::list<int> v2(initList);

  v1.sort();
  v2.sort();

  ASSERT_EQ(v1.size(), v2.size());
}

//
// insert_many
//

TEST(list_insert_many, 1) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 2, 3, 5, 1, 4, 1, 2, 3};

  auto insertResult = v1.insert_many(v1.cbegin(), 1, 2, 3, 5, 1, 4);

  ASSERT_EQ(*insertResult, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many, 2) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 1, 2, 3};

  auto insertResult = v1.insert_many(v1.cbegin(), 1);

  ASSERT_EQ(*insertResult, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many, 3) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 2, 3, 1, 2, 1};

  v1.insert_many(v1.cend(), 1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many, 4) {
  s21::List<int> v1;
  s21::List<int> v2 = {1, 2, 1};

  v1.insert_many(v1.cbegin(), 1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many, 5) {
  s21::List<int> v1;
  s21::List<int> v2 = {1, 2, 1};

  v1.insert_many(v1.cend(), 1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

//
// insert_many_back
//

TEST(list_insert_many_back, 1) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 2, 3, 1, 2, 3, 5, 1, 4};

  v1.insert_many_back(1, 2, 3, 5, 1, 4);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_back, 2) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 2, 3, 1};

  v1.insert_many_back(1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_back, 3) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 2, 3, 1, 2, 1};

  v1.insert_many_back(1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_back, 4) {
  s21::List<int> v1;
  s21::List<int> v2 = {1, 2, 1};

  v1.insert_many_back(1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_back, 5) {
  s21::List<int> v1;
  s21::List<int> v2 = {1, 2, 1, 1};

  v1.insert_many_back(1, 2, 1, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

//
// insert_many_front
//

TEST(list_insert_many_front, 1) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {4, 1, 5, 3, 2, 1, 1, 2, 3};

  v1.insert_many_front(1, 2, 3, 5, 1, 4);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_front, 2) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 1, 2, 3};

  v1.insert_many_front(1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_front, 3) {
  s21::List<int> v1 = {1, 2, 3};
  s21::List<int> v2 = {1, 2, 1, 1, 2, 3};

  v1.insert_many_front(1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_front, 4) {
  s21::List<int> v1;
  s21::List<int> v2 = {1, 2, 1};

  v1.insert_many_front(1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}

TEST(list_insert_many_front, 5) {
  s21::List<int> v1;
  s21::List<int> v2 = {1, 2, 1, 1};

  v1.insert_many_front(1, 1, 2, 1);

  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  for (size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(*iter1++, *iter2++);
  }
}
