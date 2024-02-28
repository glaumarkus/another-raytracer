#include "imgui/image_data.hpp"
#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "math/mat.hpp"
#include "primitives/plane.hpp"
#include "raytrace/camera.hpp"
#include <gtest/gtest.h>

TEST(chapter09, plane_normal) {
  auto p = Plane();
  auto n1 = p.GetNormalAtPoint(Point(0, 0, 0));
  auto n2 = p.GetNormalAtPoint(Point(10, 0, -10));
  auto n3 = p.GetNormalAtPoint(Point(-5, 0, 150));
  EXPECT_TRUE(equalv(n1, Vector(0, 1, 0)));
  EXPECT_TRUE(equalv(n2, Vector(0, 1, 0)));
  EXPECT_TRUE(equalv(n3, Vector(0, 1, 0)));
}

TEST(chapter09, plane_intersect_1) {
  auto p = Plane();
  auto r = Ray(Point(0, 10, 0), Vector(0, 0, 1));
  auto intersections = p.GetIntersections(r);
  EXPECT_TRUE(intersections.Get().empty());
}

TEST(chapter09, plane_intersect_2) {
  auto p = Plane();
  auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
  auto intersections = p.GetIntersections(r);
  EXPECT_TRUE(intersections.Get().empty());
}

TEST(chapter09, plane_intersect_3) {
  auto p = Plane();
  auto r = Ray(Point(0, 1, 0), Vector(0, -1, 0));
  auto intersections = p.GetIntersections(r);
  EXPECT_EQ(intersections.Get().size(), 1);
  EXPECT_TRUE(equal(intersections.Hit().value().t, 1.0));
}

TEST(chapter09, plane_intersect_4) {
  auto p = Plane();
  auto r = Ray(Point(0, -1, 0), Vector(0, 1, 0));
  auto intersections = p.GetIntersections(r);
  EXPECT_EQ(intersections.Get().size(), 1);
  EXPECT_TRUE(equal(intersections.Hit().value().t, 1.0));
}