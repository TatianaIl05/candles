#include <vector>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>

#include "candle.h"


TEST(CandleTest, BodyContainsGreen) {
  Candle candle{0.0, 3.0, 3.0, 3.0};
  int price = 5;
  ASSERT_EQ(candle.body_contains(price), false);
}

TEST(CandleTest, BodyContainsRed) {
  Candle candle{5.0, 4.0, 2.0, 3.0};
  int price = 3;
  ASSERT_EQ(candle.body_contains(price), true);
}

TEST(CandleTest, BodyContainsUndefined) {
  Candle candle{8.0, 1.0, 0.0, 8.0};
  int price = 8;
  ASSERT_EQ(candle.body_contains(price), true);
}

TEST(CandleTest, ContainsStandardTrue) {
  Candle candle{7.0, 1.0, 0.0, 8.0};
  int price = 0.5;
  ASSERT_EQ(candle.contains(price), true);
}

TEST(CandleTest, ContainsStandardFalse) {
  Candle candle{8.0, 1.0, 0.0, 4.0};
  int price = 10;
  ASSERT_EQ(candle.contains(price), false);
}

TEST(CandleTest, ContainsLimit) {
  Candle candle{8.0, 3.0, 1.0, 7.0};
  int price = 1;
  ASSERT_EQ(candle.contains(price), true);
}

TEST(CandleTest, FullSizeHighLow) {
  Candle candle{5.0, 6.0, 1.0, 2.0};
  ASSERT_EQ(candle.full_size(), 5);
}

TEST(CandleTest, FullSizeLowHigh) {
  Candle candle{9.0, 1.0, 6.0, 7.0};
  ASSERT_EQ(candle.full_size(), 5);
}

TEST(CandleTest, FullSizeZero) {
  Candle candle{8.0, 2.0, 2.0, 6.0};
  ASSERT_EQ(candle.full_size(), 0);
}

TEST(CandleTest, BodySizeOpenClose) {
  Candle candle{5.0, 6.0, 1.0, 2.0};
  ASSERT_EQ(candle.body_size(), 3);
}

TEST(CandleTest, BodySizeCloseOpen) {
  Candle candle{7.0, 1.0, 6.0, 9.0};
  ASSERT_EQ(candle.body_size(), 2);
}

TEST(CandleTest, BodySizeZero) {
  Candle candle{6.0, 2.0, 5.0, 6.0};
  ASSERT_EQ(candle.body_size(), 0);
}

static std::vector<std::function<bool()>> tests;

//тест 1
bool test1()
{
  //пример какого-то теста
  return 42 == (41 + 1); //passed
}

//тест 2
bool test2()
{
  //пример какого-то теста
  return 42 != (41 + 1); //failed
}

//тест 3
bool test3()
{
  Candle candle{ 0.0, 3.0, 3.0, 3.0 };

  //пример какого-то теста
  return candle.high == 3.0;
}

void initTests()
{
  tests.push_back(test1);
  tests.push_back(test2);
  tests.push_back(test3);
  //tests.push_back(test4);
  //tests.push_back(test5);
}

int launchTests()
{
  int total = 0;
  int passed = 0;

  for (const auto& test : tests)
  {
    std::cout << "test #" << (total + 1);
    if (test())
    {
      passed += 1;
      std::cout << " passed\n";
    }
    else
    {
      std::cout << " failed\n";
    }
    total += 1;
  }

  std::cout << "\ntests " << passed << "/" << total << " passed!" << std::endl;

  //0 = success
  return total - passed;
}

