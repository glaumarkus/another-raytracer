#include "math/constants.hpp"
#include "math/mat.hpp"
#include <gtest/gtest.h>

TEST(chapter03, mat_init) {
  auto m1 = Matrix<2>();
  auto m2 = Matrix<2>(1, 2, 3, 4);
  auto m3 = Matrix<3>(1, 2, 3, 4, 5, 6, 7, 8, 9);
  auto m4 = Matrix<4>(1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  auto m5 = Matrix<4>(1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  auto m6 = Matrix<4>(2, 1, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  EXPECT_TRUE(m4 == m5);
  EXPECT_TRUE(m4 != m6);
  EXPECT_EQ(m4.Eigen()(0, 0), 1);
  EXPECT_EQ(m4.Eigen()(0, 3), 4);
  EXPECT_EQ(m4.Eigen()(1, 0), 5);
  EXPECT_EQ(m4.Eigen()(1, 2), 7);
}

TEST(chapter03, mat_mut) {
  auto m1 = Matrix<4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
  auto m2 = Matrix<4>(-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8);
  auto m3 = m1 * m2;
  EXPECT_EQ(m3.Eigen()(0, 0), 20);
  EXPECT_EQ(m3.Eigen()(0, 3), 48);
  EXPECT_EQ(m3.Eigen()(1, 0), 44);
  EXPECT_EQ(m3.Eigen()(1, 2), 114);

  auto m4 = Matrix<4>(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1);
  Tuple t(1, 2, 3, 1);
  auto m5 = m4 * t;
  EXPECT_EQ(m5.x(), 18);
  EXPECT_EQ(m5.y(), 24);
  EXPECT_EQ(m5.z(), 33);
  EXPECT_EQ(m5.w(), 1);
}

TEST(chapter03, mat_identity) {
  auto m1 = Matrix<4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
  auto m2 = m1 * math_constants::m4_identity;
  EXPECT_TRUE(m1 == m2);
}

TEST(chapter03, mat_transpose) {
  auto m1 = Matrix<4>(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8);
  auto m2 = Matrix<4>(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8);
  // copied
  auto m3 = m1.Transposed();
  EXPECT_TRUE(m1 != m2);
  // only view
  EXPECT_TRUE(m1.Eigen().transpose() == m2.Eigen());
  EXPECT_TRUE(m3 == m2);
}

TEST(chapter03, mat_inverse) {
  auto m1 = Matrix<4>(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);
  auto m2 = m1.Inversed();
  // checks
  EXPECT_TRUE(equal(m2.Eigen()(0, 0), 0.21805));
  EXPECT_TRUE(equal(m2.Eigen()(0, 2), 0.24060));
  EXPECT_TRUE(equal(m1.Eigen().inverse()(1, 1), -1.45677));
}

TEST(chapter03, mat_inverse2) {
  auto m1 = Matrix<4>(3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1);
  auto m2 = Matrix<4>(8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5);
  auto m3 = m1 * m2;
  auto m4 = m3 * m2.Inversed();
  EXPECT_TRUE(equal(m1.Eigen()(0, 0), m4.Eigen()(0, 0)));
}