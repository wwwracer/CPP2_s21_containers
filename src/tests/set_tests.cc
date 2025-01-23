#include <gtest/gtest.h>

#include <set>

#include "../containers/set/s21_set.h"

TEST(set_constructor, constructor_with_data) {
  s21::set<char> myset = {'a', 'b', 'd', 'c', 'e'};
  char expect[] = {'a', 'b', 'c', 'd', 'e'};
  int i = 0;

  for (auto it : myset) {
    ASSERT_EQ(it, expect[i]);
    i++;
  }
}

TEST(set_constructor, copy_constructor) {
  s21::set<double> myset = {2.5, 1.1, 1.0, 6.3};
  s21::set<double> copyset = myset;

  auto cit = copyset.begin();

  for (auto it : myset) {
    ASSERT_EQ(it, *cit);
    cit++;
  }
}

TEST(set_constructor, move_constructor) {
  s21::set<long> myset = {10000000};
  s21::set<long> moved_set = std::move(myset);

  auto it = moved_set.begin();

  ASSERT_EQ(10000000, *it);
  ASSERT_EQ(myset.empty(), 1);
}

TEST(set_constructor, move_constructor_2) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  s21::set<int> moveset;

  moveset = std::move(myset);

  ASSERT_EQ(myset.empty(), 1);
  ASSERT_EQ(moveset.empty(), 0);
}

TEST(set_insert, standard_insert) {
  s21::set<int> myset;
  myset.insert(1);
  myset.insert(-6);

  std::set<int> orset;
  orset.insert(1);
  orset.insert(-6);

  auto it = myset.begin();
  auto orit = orset.begin();

  for (; it != myset.end(); it++) {
    ASSERT_EQ(*it, *orit);
    orit++;
  }
}

TEST(set_insert, insert_with_erase) {
  s21::set<int> myset = {2, 5};
  myset.insert(10);
  myset.insert(5);
  myset.erase(++myset.begin());

  std::set<int> stdmyset = {2, 5};
  stdmyset.insert(10);
  stdmyset.insert(5);
  stdmyset.erase(++stdmyset.begin());

  auto it = myset.begin();
  auto orit = stdmyset.begin();

  for (; it != myset.end(); it++) {
    ASSERT_EQ(*it, *orit);
    orit++;
  }
}

TEST(set_modifiers, clear) {
  s21::set<int> myset = {1, 2, 3, 4, 5};

  ASSERT_EQ(myset.empty(), 0);

  myset.clear();

  ASSERT_EQ(myset.empty(), 1);
}

TEST(set_modifiers, merge) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  std::set<int> orset = {1, 2, 3, 4, 5};

  s21::set<int> myset2 = {5, 6, 7, 8, 9};
  std::set<int> orset2 = {5, 6, 7, 8, 9};

  myset.merge(myset2);
  orset.merge(orset2);

  auto it = myset.begin();
  auto orit = orset.begin();

  for (; it != myset.end(); it++) {
    ASSERT_EQ(*it, *orit);
    orit++;
  }
}

TEST(set_modifiers, swap) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  std::set<int> orset = {1, 2, 3, 4, 5};

  s21::set<int> myset2 = {5, 6, 7, 8, 9};
  std::set<int> orset2 = {5, 6, 7, 8, 9};

  myset.swap(myset2);
  orset.swap(orset2);

  auto it = myset.cbegin();
  auto orit = orset.cbegin();

  for (; it != myset.cend(); it++) {
    ASSERT_EQ(*it, *orit);
    orit++;
  }
}

TEST(set_find, find1) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  std::set<int> orset = {1, 2, 3, 4, 5};

  auto it = myset.find(3);
  auto orit = orset.find(3);

  ASSERT_EQ(*it, *orit);
}

TEST(set_find, find2) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  std::set<int> orset = {1, 2, 3, 4, 5};

  auto it = myset.find(10);
  auto orit = orset.find(10);

  ASSERT_EQ(*it, *orit);
}

TEST(set_contains, contains) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  std::set<int> orset = {1, 2, 3, 4, 5};

  ASSERT_EQ(myset.contains(3), 1);
}

TEST(set_contains, contains2) {
  s21::set<int> myset = {1, 2, 3, 4, 5};
  std::set<int> orset = {1, 2, 3, 4, 5};

  ASSERT_EQ(myset.contains(10), 0);
}

TEST(set_size, size) {
  s21::set<int> myset = {1, 2, 3, 4, 5};

  ASSERT_EQ(myset.size(), 5);
}

TEST(set_size, max_size) {
  s21::set<int> myset = {1, 2, 3, 4};

  ASSERT_EQ(myset.max_size(), 461168601842738790);
}

TEST(insert_many, insert_many_test1) {
  s21::set<int> myset;

  auto res = myset.insert_many(1, 2, 3, 3, 4, 5);

  int exp1[] = {1, 2, 3, 3, 4, 5};
  int exp2[] = {1, 1, 1, 0, 1, 1};

  int i = 0;

  for (const auto& re : res) {
    ASSERT_EQ(*re.first, exp1[i]);
    ASSERT_EQ(re.second, exp2[i]);
    i++;
  }
}
