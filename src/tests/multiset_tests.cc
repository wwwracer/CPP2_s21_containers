#include <gtest/gtest.h>

#include <set>

#include "../containers/multiset/s21_multiset.h"

TEST(multiset_constructor, test1) {
  s21::multiset<int> myset = {1, 2, 3, 4, 5};
  s21::multiset<int> myset2;

  myset2 = std::move(myset);

  ASSERT_EQ(myset2.contains(1), 1);

  s21::multiset<int> myset4 = {1, 2, 3, 4};
  s21::multiset<int> myset3 = std::move(myset4);

  ASSERT_EQ(myset3.contains(4), 1);
}

TEST(multiset_iterator, test2) {
  s21::multiset<char> myset = {'a', 'c', 'c', 'a', 'f'};

  char expect[] = {'a', 'a', 'c', 'c', 'f'};
  int i = 0;

  for (auto it : myset) {
    ASSERT_EQ(it, expect[i]);
    i++;
  }

  i = 0;

  for (auto const_it = myset.cbegin(); const_it != myset.cend(); const_it++) {
    ASSERT_EQ(*const_it, expect[i]);
    i++;
  }
}

TEST(multiset_insert, test3) {
  s21::multiset<char> myset = {'a'};

  myset.insert('a');
  myset.insert('b');

  char expect[] = {'a', 'a', 'b'};

  int i = 0;
  for (auto it : myset) {
    ASSERT_EQ(it, expect[i]);
    i++;
  }
}

TEST(multiset_erase, test4) {
  s21::multiset<double> myset = {2.5, 1.2};

  myset.erase(myset.begin());

  ASSERT_EQ(myset.size(), 1);
}

TEST(multiset_find, test5) {
  s21::multiset<char> myset = {'a', 'c', 'b', 'f', 'g'};

  auto it = myset.find('c');

  ASSERT_EQ(*it, 'c');

  auto lower_it = myset.lower_bound('c');

  ASSERT_EQ(*lower_it, 'c');

  auto up_it = myset.upper_bound('c');

  ASSERT_EQ(*up_it, 'f');

  auto pair_it = myset.equal_range('c');

  ASSERT_EQ(*pair_it.first, 'c');

  ASSERT_EQ(*pair_it.second, 'f');
}

TEST(multiset_upper_bound, test9) {
  s21::multiset<char> myset = {'b', 'c', 'b'};

  auto it = myset.upper_bound('z');

  ASSERT_EQ(it, myset.end());

  auto it2 = myset.upper_bound('a');

  ASSERT_EQ(it2, myset.end());
}

TEST(multiset_merge_swap, test6) {
  s21::multiset<int> myset = {1, 2, 3, 4};
  s21::multiset<int> myset2 = {3, 4, 5};

  std::multiset<int> myset3 = {1, 2, 3, 4};
  std::multiset<int> myset4 = {3, 4, 5};

  myset.swap(myset2);
  myset3.swap(myset4);

  auto it2 = myset3.begin();
  for (auto it : myset) {
    ASSERT_EQ(it, *it2);
    it2++;
  }

  myset.merge(myset2);
  myset3.merge(myset4);

  auto it3 = myset3.begin();
  for (auto it : myset) {
    ASSERT_EQ(it, *it3);
    it3++;
  }
}

TEST(multiset_empty_clear, test7) {
  s21::multiset<int> myset = {1, 2, 3, 4, 5, 6, 7};

  ASSERT_EQ(myset.empty(), 0);

  auto it = myset.find(8);

  auto empty_it = myset.lower_bound(8);

  ASSERT_EQ(empty_it, myset.end());

  ASSERT_EQ(*it, 7);

  myset.clear();

  ASSERT_EQ(myset.empty(), 1);
}

TEST(multiset_max_size, test8) {
  s21::multiset<char> myset = {'a', 'b', 'c'};

  ASSERT_EQ(myset.size(), 3);

  ASSERT_EQ(myset.max_size(), 576460752303423487);
}

TEST(multiset_count, test10) {
  s21::multiset<int> myset = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};

  std::multiset<int> myset2 = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};

  ASSERT_EQ(myset.count(4), myset2.count(4));

  ASSERT_EQ(myset.count(10), myset2.count(10));
}

TEST(multiset_insert_many, insert_many_test1) {
  s21::multiset<int> myset;

  auto res = myset.insert_many(1, 2, 3, 3, 4, 5);

  int exp[] = {1, 2, 3, 3, 4, 5};
  int i = 0;

  for (auto it : res) {
    ASSERT_EQ(*it, exp[i]);
    i++;
  }
}
