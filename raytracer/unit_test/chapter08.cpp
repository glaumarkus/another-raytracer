#include "imgui/image_buffer.hpp"
#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "math/mat.hpp"
#include "raytrace/camera.hpp"
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

TEST(chapter08, test_adjusted_lighting) {
  auto eye = Vector(0, 0, -1);
  auto normal = Vector(0, 0, -1);
  auto light = std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  PhongReflectionShadowModel model;
  auto color = model.GetLightingColor(Material(), lights, Point(0, 0, 1), eye,
                                      normal, 1.0);
  EXPECT_TRUE(equalc(color, Color(0.1, 0.1, 0.1)));
}

TEST(chapter08, test_shadow_1) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto shadow = world->IsShadow(Point(0, 10, 0));
  EXPECT_EQ(shadow, 0.0);
}

TEST(chapter08, test_shadow_2) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto shadow = world->IsShadow(Point(10, -10, 10));
  EXPECT_EQ(shadow, 1.0);
}

TEST(chapter08, test_shadow_3) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto shadow = world->IsShadow(Point(-20, 20, -20));
  EXPECT_EQ(shadow, 0.0);
}

TEST(chapter08, test_shadow_4) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto shadow = world->IsShadow(Point(-2, 2, -2));
  EXPECT_EQ(shadow, 0.0);
}

TEST(chapter08, shade_hit_1) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter08.yaml");
  auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  auto intersections = world->Intersect(r);
  IntersectionData id{
      .t = 14,
      .obj = world->GetObjects()[1].get(),
  };
  PhongReflectionShadowModel model;
  auto comps = PrepareComputations(id, r);
  auto color = world->ShadeHit(comps, &model);
  EXPECT_TRUE(equalc(color, Color(0.1, 0.1, 0.1)));
}

TEST(chapter08, over_point) {

  auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.Transform(math_constants::TranslationMatrix(0, 0, 1));
  IntersectionData id{
      .t = 5,
      .obj = &s,
  };

  auto comps = PrepareComputations(id, r);
  EXPECT_TRUE(comps.GetOverPoint().z() < comps.GetPoint().z());
}