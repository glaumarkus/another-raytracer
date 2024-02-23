#include "math/constants.hpp"
#include "math/vector2d.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <gtest/gtest.h>

TEST(chapter01, tupels_init) {

  Point p(4.3, -4.2, 3.1);
  EXPECT_EQ(p.w(), 1.0);

  Vector v(4.3, -4.2, 3.1);
  EXPECT_EQ(v.w(), 0.0);
}

TEST(chapter01, constants) {
  EXPECT_TRUE(equal(0.0, 0.0));
  EXPECT_FALSE(equal(0.0, 0.01));
}

TEST(chapter01, tupels_operations_addition) {
  Vector v1(3, -2, 5);
  Vector v2(-2, 3, 1);
  Vector v3 = v1 + v2;
  EXPECT_EQ(v3.x(), 1.0);
  EXPECT_EQ(v3.y(), 1.0);
  EXPECT_EQ(v3.z(), 6.0);
}

TEST(chapter01, tupels_operations_substraction) {
  Vector v1(3, 2, 1);
  Vector v2(5, 6, 7);
  Vector v3 = v1 - v2;
  EXPECT_EQ(v3.x(), -2.0);
  EXPECT_EQ(v3.y(), -4.0);
  EXPECT_EQ(v3.z(), -6.0);

  // substract vector from point
  Point p(3, 2, 1);
  Vector v(5, 6, 7);
  Point p1 = p - v;
  EXPECT_EQ(p1.x(), -2.0);
  EXPECT_EQ(p1.y(), -4.0);
  EXPECT_EQ(p1.z(), -6.0);
  EXPECT_EQ(p1.w(), 1.0);
}

TEST(chapter01, tupels_negate) {
  Vector v1(1, -2, 3);
  v1.Negate();
  EXPECT_EQ(v1.x(), -1.0);
  EXPECT_EQ(v1.y(), 2.0);
  EXPECT_EQ(v1.z(), -3.0);
}

TEST(chapter01, tupels_multiplication) {
  Vector v1(1, -2, 3, -4);
  v1 *= 3.5;
  EXPECT_EQ(v1.x(), 3.5);
  EXPECT_EQ(v1.y(), -7);
  EXPECT_EQ(v1.z(), 10.5);
  EXPECT_EQ(v1.w(), -14);

  Vector v2(1, -2, 3, -4);
  v2 *= 0.5;
  EXPECT_EQ(v2.x(), 0.5);
  EXPECT_EQ(v2.y(), -1);
  EXPECT_EQ(v2.z(), 1.5);
  EXPECT_EQ(v2.w(), -2);
}

TEST(chapter01, tupels_division) {
  Vector v1(1, -2, 3, -4);
  v1 /= 2;
  EXPECT_EQ(v1.x(), 0.5);
  EXPECT_EQ(v1.y(), -1);
  EXPECT_EQ(v1.z(), 1.5);
  EXPECT_EQ(v1.w(), -2);
}

TEST(chapter01, tuples_magnitude) {
  Vector v(1, 0, 0);
  EXPECT_EQ(v.Magnitude(), 1.0);
  v = Vector(0, 1, 0);
  EXPECT_EQ(v.Magnitude(), 1.0);
  v = Vector(0, 0, 1);
  EXPECT_EQ(v.Magnitude(), 1.0);
  v = Vector(1, 2, 3);
  EXPECT_EQ(v.Magnitude(), std::sqrt(14));
  v = Vector(-1, -2, -3);
  EXPECT_EQ(v.Magnitude(), std::sqrt(14));
}

TEST(chapter01, tuples_normalized) {
  Vector v(4, 0, 0);
  v.Normalize();
  EXPECT_EQ(v.x(), 1.0);

  v = Vector(1, 2, 3);
  auto v1 = v.Normalized();
  EXPECT_EQ(v1.x(), 1.0 / std::sqrt(14));
  EXPECT_EQ(v1.y(), 2.0 / std::sqrt(14));
  EXPECT_EQ(v1.z(), 3.0 / std::sqrt(14));
}

TEST(chapter01, tuples_dot) {
  Vector v1(1, 2, 3);
  Vector v2(2, 3, 4);
  EXPECT_EQ(v1.Dot(v2), 20.0);
  EXPECT_EQ(Dot(v1, v2), 20.0);
}

TEST(chapter01, tuples_cross) {
  Vector v1(1, 2, 3);
  Vector v2(2, 3, 4);

  auto cross1 = v1.Cross(v2);
  auto cross2 = v2.Cross(v1);

  EXPECT_EQ(cross1.x(), -1.0);
  EXPECT_EQ(cross1.y(), 2.0);
  EXPECT_EQ(cross1.z(), -1.0);

  EXPECT_EQ(cross2.x(), 1.0);
  EXPECT_EQ(cross2.y(), -2.0);
  EXPECT_EQ(cross2.z(), 1.0);
}