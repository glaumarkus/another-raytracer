#include "math/constants.hpp"
#include "math/mat.hpp"
#include <gtest/gtest.h>

TEST(chapter04, mat_translation) {
  auto m1 = math_constants::TranslationMatrix(5, -3, 2);
  auto p1 = Point(-3, 4, 5);
  auto v1 = Vector(-3, 4, 5);
  auto p2 = Point(2, 1, 7);
  // check that only points get translated
  EXPECT_EQ((m1 * p1).x(), 2);
  EXPECT_EQ((m1 * v1).x(), v1.x());
}

TEST(chapter04, mat_scaling) {
  auto m1 = math_constants::ScaleMatrix(2, 3, 4);
  auto p1 = Point(-4, 6, 8);
  EXPECT_EQ((m1 * p1).x(), -8);
}

TEST(chapter04, mat_rotate_x) {
  auto m1 = math_constants::RotationMatrixX(M_PI_4);
  auto m2 = math_constants::RotationMatrixX(M_PI_2);
  auto p1 = Point(0, 1, 0);
  auto p2 = m1 * p1;
  auto p3 = m2 * p1;

  EXPECT_TRUE(equal(p2.x(), 0));
  EXPECT_TRUE(equal(p2.y(), std::sqrt(2) / 2));
  EXPECT_TRUE(equal(p2.z(), std::sqrt(2) / 2));

  EXPECT_TRUE(equal(p3.x(), 0));
  EXPECT_TRUE(equal(p3.y(), 0));
  EXPECT_TRUE(equal(p3.z(), 1));
}

TEST(chapter04, mat_rotate_y) {
  auto m1 = math_constants::RotationMatrixY(M_PI_4);
  auto m2 = math_constants::RotationMatrixY(M_PI_2);
  auto p1 = Point(0, 0, 1);
  auto p2 = m1 * p1;
  auto p3 = m2 * p1;

  EXPECT_TRUE(equal(p2.x(), std::sqrt(2) / 2));
  EXPECT_TRUE(equal(p2.y(), 0));
  EXPECT_TRUE(equal(p2.z(), std::sqrt(2) / 2));

  EXPECT_TRUE(equal(p3.x(), 1));
  EXPECT_TRUE(equal(p3.y(), 0));
  EXPECT_TRUE(equal(p3.z(), 0));
}

TEST(chapter04, mat_rotate_z) {
  auto m1 = math_constants::RotationMatrixZ(M_PI_4);
  auto m2 = math_constants::RotationMatrixZ(M_PI_2);
  auto p1 = Point(0, 1, 0);
  auto p2 = m1 * p1;
  auto p3 = m2 * p1;

  EXPECT_TRUE(equal(p2.x(), -std::sqrt(2) / 2));
  EXPECT_TRUE(equal(p2.y(), std::sqrt(2) / 2));
  EXPECT_TRUE(equal(p2.z(), 0));

  EXPECT_TRUE(equal(p3.x(), -1));
  EXPECT_TRUE(equal(p3.y(), 0));
  EXPECT_TRUE(equal(p3.z(), 0));
}

TEST(chapter04, mat_shear) {
  auto m1 = math_constants::ShearMatrix(0, 0, 0, 0, 0, 1);
  auto p1 = Point(2, 3, 4);
  auto p2 = m1 * p1;

  EXPECT_TRUE(equal(p2.x(), 2));
  EXPECT_TRUE(equal(p2.y(), 3));
  EXPECT_TRUE(equal(p2.z(), 7));
}