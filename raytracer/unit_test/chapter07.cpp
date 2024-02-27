#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "utility/logger.hpp"
#include "utility/world_parser.hpp"
#include <gtest/gtest.h>
#include <iostream>

auto equalc = [](Color lhs, Color rhs) {
  bool result = false;
  if (std::abs(lhs.r() - rhs.r()) < kEpsilon &&
      std::abs(lhs.g() - rhs.g()) < kEpsilon &&
      std::abs(lhs.b() - rhs.b()) < kEpsilon) {
    result = true;
  }
  return result;
};

TEST(chapter07, load_world_file) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  EXPECT_NE(world, nullptr);
  EXPECT_EQ(world->GetLights().size(), 1);
  EXPECT_EQ(world->GetObjects().size(), 2);
}

TEST(chapter07, intersect_world) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto intersections = world->Intersect(r);
  EXPECT_EQ(intersections.Get().size(), 4);
  EXPECT_EQ(intersections.Get()[0].t, 4.0);
  EXPECT_EQ(intersections.Get()[1].t, 4.5);
  EXPECT_EQ(intersections.Get()[2].t, 5.5);
  EXPECT_EQ(intersections.Get()[3].t, 6);
}

TEST(chapter07, prepare_computations) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  auto intersections = s.GetIntersections(r);
  auto hit = intersections.Hit();
  if (!hit)
    FAIL();
  PrepareComputations p(hit.value(), r);
  EXPECT_EQ(p.GetObject(), &s);
  EXPECT_EQ(p.GetPoint(), Point(0, 0, -1));
  EXPECT_FALSE(p.IsInside());
  EXPECT_EQ(p.GetNormal(), Vector(0, 0, -1));
  EXPECT_EQ(p.GetEye(), Vector(0, 0, -1));
}

TEST(chapter07, prepare_computations_inside) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  auto intersections = s.GetIntersections(r);
  auto hit = intersections.Hit();
  if (!hit)
    FAIL();
  PrepareComputations p(hit.value(), r);
  EXPECT_EQ(p.GetObject(), &s);
  EXPECT_TRUE(equalv(p.GetPoint(), Point(0, 0, 1)));
  EXPECT_TRUE(p.IsInside());
  EXPECT_TRUE(equalv(p.GetNormal(), Vector(0, 0, -1)));
  EXPECT_TRUE(equalv(p.GetEye(), Vector(0, 0, -1)));
}

TEST(chapter07, shade_hit) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  IntersectionData id{
      .t = 4,
      .obj = world->GetObjects()[0].get(),
  };
  PhongReflectionModel model;
  auto comps = PrepareComputations(id, r);
  auto color = world->ShadeHit(comps, &model);
  std::cout << color.Eigen() << "\n";
  EXPECT_TRUE(equalc(color, Color(0.38066, 0.47583, 0.2855)));
}

TEST(chapter07, shade_hit_2) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
  IntersectionData id{
      .t = 0.5,
      .obj = world->GetObjects()[1].get(),
  };
  PhongReflectionModel model;
  auto comps = PrepareComputations(id, r);
  auto color = world->ShadeHit(comps, &model);
  std::cout << color.Eigen() << "\n";
  EXPECT_TRUE(equalc(color, Color(0.90498)));
}
