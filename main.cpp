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

TEST(CandleTest, IsRedTrue) {
  Candle candle{19.0, 2.0, 5.0, 6.0};
  ASSERT_EQ(candle.is_red(), true);
}

TEST(CandleTest, IsRedFalse) {
  Candle candle{1.0, 2.0, 5.0, 6.0};
  ASSERT_EQ(candle.is_red(), false);
}

TEST(CandleTest, IsRedFalseLimit) {
  Candle candle{6.0, 2.0, 5.0, 6.0};
  ASSERT_EQ(candle.is_red(), false);
}

TEST(CandleTest, IsGreenTrue) {
  Candle candle{6.0, 2.0, 5.0, 11.0};
  ASSERT_EQ(candle.is_green(), true);
}

TEST(CandleTest, IsGreenFalse) {
  Candle candle{6.0, 2.0, 5.0, 1.0};
  ASSERT_EQ(candle.is_green(), false);
}

TEST(CandleTest, IsGreenFalseLimit) {
  Candle candle{6.0, 2.0, 5.0, 6.0};
  ASSERT_EQ(candle.is_green(), false);
}
