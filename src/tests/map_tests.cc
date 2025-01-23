#include <gtest/gtest.h>

#include <map>

#include "../containers/map/s21_map.h"

TEST(map_constructor, maptest1) {
  s21::map<int, int> mymap = {{2, 2}, {3, 1}, {1, 2}};
  std::map<int, int> origmap = {{2, 2}, {3, 1}, {1, 2}};

  for (auto it = mymap.begin(); it != mymap.end(); it++) {
    ASSERT_EQ(it->second, origmap.at(it->first));
  }
}

TEST(map_constructor, maptest2) {
  s21::map<char, int> mymap;  // Стандартный конструктор

  mymap.insert('c', 5);

  mymap.insert('h', 10);

  ASSERT_EQ(mymap.at('c'), 5);

  s21::map<char, int> newmap =
      std::move(mymap);  // Стандартный конструктор переноса

  ASSERT_EQ(newmap.at('c'), 5);

  ASSERT_ANY_THROW(mymap.at('c'));  // Error

  s21::map<char, int> alsonewmap;

  alsonewmap = std::move(newmap);  // Перегрузка конструктора переноса

  ASSERT_EQ(alsonewmap.at('c'), 5);

  ASSERT_ANY_THROW(newmap.at('c'));

  s21::map<char, int> copymap;

  copymap = alsonewmap;  // Конструктор копирования

  ASSERT_EQ(copymap.at('c'), 5);

  ASSERT_EQ(alsonewmap.at('c'), 5);

  s21::map<char, int> copyagain = alsonewmap;

  ASSERT_EQ(copyagain.at('c'), alsonewmap.at('c'));
}

TEST(map_insert, maptest1) {
  s21::map<int, int> mymap = {
      {1, 1},
      {2, 2},
  };

  mymap.insert(2, 3);  // Not inserted

  int expect[] = {1, 2};
  int i = 0;

  for (auto it = mymap.begin(); it != mymap.end(); it++) {
    ASSERT_EQ(it->second, expect[i]);
    i++;
  }
}

TEST(map_conteins, maptest1) {
  s21::map<int, int> mymap = {{1, 1}, {2, 2}, {5, 3}, {6, 4}};

  ASSERT_EQ(mymap.contains(5), true);
}

TEST(map_operators, maptest1) {
  s21::map<int, int> mymap = {{1, 1}, {2, 5}};

  ASSERT_EQ(mymap[2], 5);

  ASSERT_EQ(mymap[4], 0);
}

TEST(map_const_iterator, maptest1) {
  s21::map<int, int> mymap = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}};

  for (auto it = mymap.cbegin(); it != mymap.cend(); it++) {
    ASSERT_EQ(it->second, 1);
  }
}

TEST(map_insert, maptest2) {
  s21::map<int, int> mymap;

  mymap.insert({1, 1});
  mymap.insert(2, 1);
  mymap.insert(2, 5);
  mymap.insert({2, 2});

  int expect[] = {1, 1};
  int i = 0;

  for (auto it = mymap.begin(); it != mymap.end(); it++) {
    ASSERT_EQ(it->second, expect[i]);
    i++;
  }
}

TEST(map_insert_or_assign, maptest1) {
  s21::map<int, int> mymap;

  mymap.insert_or_assign(1, 1);
  mymap.insert_or_assign(2, 5);
  mymap.insert_or_assign(2, 3);

  int expect[] = {1, 3};
  int i = 0;

  for (auto it = mymap.begin(); it != mymap.end(); it++) {
    ASSERT_EQ(it->second, expect[i]);
    i++;
  }
}

TEST(map_empty, maptest1) {
  s21::map<int, int> mymap;

  ASSERT_EQ(mymap.empty(), true);

  mymap.insert(1, 1);

  ASSERT_EQ(mymap.empty(), false);
}

TEST(map_clear, maptest1) {
  s21::map<int, int> mymap;

  mymap.insert(1, 1);

  ASSERT_EQ(mymap.empty(), false);

  mymap.clear();

  ASSERT_EQ(mymap.empty(), true);
}

TEST(map_size, maptest1) {
  s21::map<int, int> mymap = {{1, 1}, {2, 1}, {4, 5}, {3, 2}};

  ASSERT_EQ(mymap.size(), 4);
}

TEST(map_max_size, maptest1) {
  s21::map<int, int> mymap;
  size_t s = 461168601842738790;

  ASSERT_EQ(mymap.max_size(), s);
}

TEST(map_max_size, maptest2) {
  s21::map<char, double> mymap;
  size_t s = 384307168202282325;

  ASSERT_EQ(mymap.max_size(), s);
}

TEST(map_swap, maptest1) {
  s21::map<int, int> fmap = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};

  s21::map<int, int> smap = {
      {1, 9},
      {2, 8},
      {3, 7},
      {4, 6},
  };

  s21::map<int, int> fomap = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};

  s21::map<int, int> somap = {
      {1, 9},
      {2, 8},
      {3, 7},
      {4, 6},
  };

  fmap.swap(smap);
  fomap.swap(somap);

  for (auto it = fmap.begin(); it != fmap.end(); it++) {
    ASSERT_EQ(it->second, fomap[it->first]);
  }

  for (auto it = smap.begin(); it != smap.end(); it++) {
    ASSERT_EQ(it->second, somap[it->first]);
  }
}

TEST(map_erase, maptest1) {
  s21::map<int, int> mymap = {{1, 1}, {2, 2}};

  mymap.erase(++mymap.begin());

  ASSERT_EQ(mymap.at(1), 1);

  ASSERT_ANY_THROW(mymap.at(2));
}

TEST(map_merge, maptest1) {
  s21::map<int, int> mymap1 = {{1, 1}, {2, 2}};
  s21::map<int, int> mymap2 = {{2, 5}, {3, 2}};

  mymap1.merge(mymap2);
  std::map<int, int> omymap1 = {{1, 1}, {2, 2}};
  std::map<int, int> omymap2 = {{2, 5}, {3, 2}};

  omymap1.merge(omymap2);

  for (auto it = omymap1.begin(); it != omymap1.end(); it++) {
    ASSERT_EQ(it->second, mymap1.at(it->first));
  }
}

TEST(map_insert_many, insert_many_test1) {
  s21::map<int, int> mymap1;
  auto res = mymap1.insert_many(std::make_pair(1, 1), std::make_pair(2, 2),
                                std::make_pair(3, 3));
  for (auto re : res) {
    ASSERT_EQ(re.first->second, mymap1[re.first->first]);
  }
}

TEST(map_insert_many, insert_many_test2) {
  s21::map<int, int> mymap1;
  auto res = mymap1.insert_many({{1, 1}, {2, 2}, {3, 3}});
  for (auto re : res) {
    ASSERT_EQ(re.first->second, mymap1[re.first->first]);
  }
}
