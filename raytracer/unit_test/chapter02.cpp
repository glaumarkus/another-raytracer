#include "imgui/color.hpp"
#include "math/constants.hpp"
#include <gtest/gtest.h>

TEST(chapter02, color_init) {
  Color c(-0.5, 0.4, 1.7);
  EXPECT_TRUE(equal(c.r(), -0.5));
  EXPECT_TRUE(equal(c.g(), 0.4));
  EXPECT_TRUE(equal(c.b(), 1.7));
}

TEST(chapter02, color_add) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color c3 = c1 + c2;
  EXPECT_EQ(c3.r(), 1.6);
  EXPECT_EQ(c3.g(), 0.7);
  EXPECT_EQ(c3.b(), 1.0);
}

TEST(chapter02, color_substract) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color c3 = c1 - c2;

  EXPECT_TRUE(equal(c3.r(), 0.2));
  EXPECT_TRUE(equal(c3.g(), 0.5));
  EXPECT_TRUE(equal(c3.b(), 0.5));
}

TEST(chapter02, color_mut) {
  Color c1(0.2, 0.3, 0.4);
  c1 *= 2;

  EXPECT_EQ(c1.r(), 0.4);
  EXPECT_EQ(c1.g(), 0.6);
  EXPECT_EQ(c1.b(), 0.8);

  Color c2(1, 0.2, 0.4);
  Color c3(0.9, 1, 0.1);
  c2 *= c3;
  EXPECT_TRUE(equal(c2.r(), 0.9));
  EXPECT_TRUE(equal(c2.g(), 0.2));
  EXPECT_TRUE(equal(c2.b(), 0.04));
}
