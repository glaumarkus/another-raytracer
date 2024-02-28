#include "math/constants.hpp"
#include "primitives/object.hpp"
#include "math/ray.hpp"
#include <gtest/gtest.h>

TEST(chapter05, ray_position) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  auto p1 = r.Position(1);
  EXPECT_TRUE(equal(p1.x(), 3));
}

TEST(chapter05, ray_sphere_intersection) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  auto intersections = s.GetIntersections(r);
  EXPECT_TRUE(equal(intersections.Get()[0].t, -6.0));
  EXPECT_TRUE(equal(intersections.Get()[1].t, -4.0));
}

TEST(chapter05, ray_sphere_hits) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  auto intersections = s.GetIntersections(r);
  EXPECT_TRUE(equal(intersections.Get()[0].t, -6.0));
  EXPECT_TRUE(equal(intersections.Get()[1].t, -4.0));
}

TEST(chapter05, apply_ray_translation) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  auto m = math_constants::TranslationMatrix(3, 4, 5);
  auto r2 = r.Transform(m);
  EXPECT_EQ(r2.GetOrigin().Eigen(), Point(4, 6, 8).Eigen());
  EXPECT_EQ(r2.GetDirection().Eigen(), Vector(0, 1, 0).Eigen());
}

TEST(chapter05, apply_ray_scale) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  auto m = math_constants::ScaleMatrix(2, 3, 4);
  auto r2 = r.Transform(m);
  EXPECT_EQ(r2.GetOrigin().Eigen(), Point(2, 6, 12).Eigen());
  EXPECT_EQ(r2.GetDirection().Eigen(), Vector(0, 3, 0).Eigen());
}

TEST(chapter05, apply_sphere_transformation) {
  Sphere s;
  EXPECT_EQ(s.GetTransformation(), math_constants::m4_identity);
  s.Transform(math_constants::TranslationMatrix(2, 3, 4));
  EXPECT_EQ(s.GetTransformation(), math_constants::TranslationMatrix(2, 3, 4));
}

TEST(chapter05, scaled_sphere_intersection) {
  Sphere s;
  s.Transform(math_constants::ScaleMatrix(2, 2, 2));
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto intersections = s.GetIntersections(r);
  EXPECT_EQ(2, intersections.Get().size());
  EXPECT_EQ(intersections.Get()[0].t, 3);
  EXPECT_EQ(intersections.Get()[1].t, 7);
}